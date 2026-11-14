#include "process_keymap.h"
#include "keycodes.h"
#include "usb.h"
#include "events.h"
#include "layers.h"
#include "layer_tap.h"
#include "mod_tap.h"
#include "mouse.h"


void process_keyboard_queue(void) {
    if(queue_is_empty()) return;

    key_event_t *oldest = queue_peek_oldest();
    uint8_t keycode_action = (oldest->keycode >> 12);
    uint8_t action_info = ((oldest->keycode >> 8) & 0x0F);
    uint8_t keycode = (uint8_t)(oldest->keycode);

    switch(keycode_action) {
        case ACT_NORMAL:
            if(oldest->type == EVENT_PRESS) {
                add_to_keyboard_report(keycode);
            } else {
                remove_from_keyboard_report(keycode);
            }
            queue_pop_oldest();
            break;
        case ACT_MODIFIER:
            if(oldest->type == EVENT_PRESS) {
                add_modifier_to_report(keycode);
            } else {
                remove_modifier_from_report(keycode);
            }
            queue_pop_oldest();
            break;
        case ACT_LAYER_MO:
            if(oldest->type == EVENT_PRESS) {
                layer_on(action_info);
            } else {
                layer_off(action_info);
            }
            queue_pop_oldest();
            break;
        case ACT_LAYER_TG:
            if(oldest->type == EVENT_PRESS) {
                layer_toggle(action_info);
            }
            queue_pop_oldest();
            break;
        case ACT_LAYER_TAP:
            handle_layer_tap(oldest);
            break;
        case ACT_MOD_TAP:
            handle_mod_tap(oldest);
            break;
        case ACT_MOUSE_BUTTON:
            handle_mouse_button(oldest);
            break;
        case ACT_MOUSE_MOVEMENT:
            queue_pop_oldest();
            break;
        case ACT_MOD_AND_KEYCODE:
            if(oldest->type == EVENT_PRESS) {
                add_modifier_to_report(get_mod_mask(action_info));
                add_to_keyboard_report(keycode);
            } else {
                remove_modifier_from_report(get_mod_mask(action_info));
                remove_from_keyboard_report(keycode);
            }
            queue_pop_oldest();
            break;
        case ACT_MACRO:
            queue_pop_oldest();
            break;


        default:
            break;
    }
}