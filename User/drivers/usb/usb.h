#pragma once

#include "usb_descriptors.h"
#include "tusb.h"

void init_usb_clocks(void);

void init_usb(void);

void add_to_keyboard_report(uint8_t keycode);

void remove_from_keyboard_report(uint8_t keycode);

void add_modifier_to_report(uint8_t mod_mask);

void remove_modifier_from_report(uint8_t mod_mask);

void send_reports_to_host(void);
