#pragma once

#include "usb_descriptors.h"
#include "tusb.h"

typedef struct {
  uint8_t buttons;
  int8_t x;
  int8_t y;
  int8_t vert;
  int8_t hori;
} mouse_report_t;

void init_usb_clocks(void);

void init_usb(void);

void add_to_keyboard_report(uint8_t keycode);

void remove_from_keyboard_report(uint8_t keycode);

void add_modifier_to_report(uint8_t mod_mask);

void remove_modifier_from_report(uint8_t mod_mask);

uint8_t* get_modifier_ptr(void);

void send_keyboard_report_to_host(void);
void send_mouse_report_to_host(void);

void add_mouse_button_to_mouse_report(uint8_t button_mask);
void remove_mouse_button_from_mouse_report(uint8_t button_mask);

void add_mouse_movement_to_report(int8_t x, int8_t y, int8_t vert, int8_t hori);