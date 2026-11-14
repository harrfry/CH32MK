#pragma once

#include "events.h"

void handle_mouse_button(key_event_t *oldest);
void handle_mouse_movement(key_event_t *oldest);
void mouse_housekeeping_task(void);