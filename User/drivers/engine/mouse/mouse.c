#include "keycodes.h"
#include "events.h"
#include "usb.h"

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
            break;
            y = -1;
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

    mouse_x_dir += x;
    mouse_y_dir += y;
    mouse_vert_dir += vert;
    mouse_hori_dir += hori;
    mouse_movement_start_time = oldest->timestamp;
    queue_pop_oldest();
    return;
}

void mouse_housekeeping_task(void) {

}