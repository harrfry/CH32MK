#include "keycodes.h"
#include "events.h"
#include "usb.h"
#include "systick.h"
#include "stdio.h"

int8_t mouse_x_dir = 0;
int8_t mouse_y_dir = 0;
int8_t mouse_vert_dir = 0;
int8_t mouse_hori_dir = 0;
uint32_t mouse_movement_start_time = 0;

void handle_mouse_button(key_event_t *oldest) {
    uint8_t button_mask = (uint8_t)(oldest->keycode);

    if(oldest->type == EVENT_PRESS) {
        add_mouse_button_to_mouse_report(button_mask);
    } else {
        remove_mouse_button_from_mouse_report(button_mask);
    }
    queue_pop_oldest();
}

void handle_mouse_movement(key_event_t *oldest) {
    uint8_t action = (oldest->keycode & 0x0FFF);
    int8_t x = 0;
    int8_t y = 0;
    int8_t vert = 0;
    int8_t hori = 0;
    switch(action) {
        case LEFT:
            x = -1;
            break;
        case RIGHT:
            x = 1;
            break;
        case UP:
            y = -1;
            break;
        case DOWN:
            y = 1;
            break;
        case SCROLL_UP:
            vert = 1;
            break;
        case SCROLL_DOWN:
            vert = -1;
            break;
        case SCROLL_LEFT:
            hori = -1;
            break;
        case SCROLL_RIGHT:
            hori = 1;
            break;
        default:
            return;
    };

    int8_t modifier = (oldest->type == EVENT_PRESS) ? 1 : -1;
    mouse_x_dir += (x * modifier);
    mouse_y_dir += (y * modifier);
    mouse_vert_dir += (vert * modifier);
    mouse_hori_dir += (hori * modifier);
    /*no need to clamp to +1 or -1 as all press events must
     have an equivalent release event... eventually, in theory
     ... this was a lie... it should be clamped... it is now clamped.
    */
    queue_pop_oldest();
    return;
}

#ifndef MOUSE_STARTING_VELOCITY
#define MOUSE_STARTING_VELOCITY 1
#endif
#ifndef MOUSE_PEAK_VELOCITY
#define MOUSE_PEAK_VELOCITY 10
#endif
#ifndef TIME_TO_PEAK_VELOCITY_MS
#define TIME_TO_PEAK_VELOCITY_MS 1000
#endif

static int16_t x_remainder = 0;
static int16_t y_remainder = 0;
static int16_t vert_remainder = 0;
static int16_t hori_remainder = 0;


void mouse_housekeeping_task(void) {

    if(mouse_x_dir > 1) mouse_x_dir = 1;
    if(mouse_x_dir < -1) mouse_x_dir = -1;
    if(mouse_y_dir > 1) mouse_y_dir = 1;
    if(mouse_y_dir < -1) mouse_y_dir = -1;

    if(mouse_vert_dir > 1) mouse_vert_dir = 1;
    if(mouse_vert_dir < -1) mouse_vert_dir = -1;
    if(mouse_hori_dir > 1) mouse_hori_dir = 1;
    if(mouse_hori_dir < -1) mouse_hori_dir = -1;

    if(mouse_x_dir == 0 && mouse_y_dir == 0 && mouse_vert_dir == 0 && mouse_hori_dir == 0) {
        mouse_movement_start_time = 0;
        x_remainder = 0;
        y_remainder = 0;
        return;
    }

    uint32_t current_time = sys_ticks_ms;
    if(mouse_movement_start_time == 0) {
        mouse_movement_start_time = current_time;
    }

    uint32_t elapsed = current_time - mouse_movement_start_time;

    int32_t current_velocity;
    if(elapsed >= TIME_TO_PEAK_VELOCITY_MS) {
        current_velocity = MOUSE_PEAK_VELOCITY;
    } else {
        int32_t velocity_range = MOUSE_PEAK_VELOCITY - MOUSE_STARTING_VELOCITY;
        current_velocity = MOUSE_STARTING_VELOCITY + (int32_t)(elapsed * velocity_range) / TIME_TO_PEAK_VELOCITY_MS;
    }

    int32_t raw_x = (mouse_x_dir * current_velocity) + x_remainder;
    int32_t raw_y = (mouse_y_dir * current_velocity) + y_remainder;
    int32_t raw_vert = (mouse_vert_dir * current_velocity) + vert_remainder;
    int32_t raw_hori = (mouse_hori_dir * current_velocity) + vert_remainder;

    int8_t final_x = (int8_t)(raw_x / 4);
    int8_t final_y = (int8_t)(raw_y / 4);

    int8_t final_vert = (int8_t)(raw_vert / 64);
    int8_t final_hori = (int8_t)(raw_hori / 64); 

    x_remainder = raw_x % 4;
    y_remainder = raw_y % 4;
    vert_remainder = raw_vert % 64;
    hori_remainder = raw_hori % 64;

    add_mouse_movement_to_report(final_x, final_y, final_vert, final_hori);
    return;
}