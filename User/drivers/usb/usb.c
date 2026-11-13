#include "ch32v20x.h"
#include "usb.h"
#include "events.h"
#include "keycodes.h"

uint8_t keyboard_report[HID_REPORT_KEY_LIMIT] = {0};
uint8_t modifiers_mask = 0;

int _write(int fd, char *ptr, int len) {
    (void)fd;
    if (!tud_cdc_connected()) {
        /* Host port not open ?? drop the data to avoid blocking */
        return len;
    }

    int written = 0;
    while (written < len) {
        /* Write as many bytes as the FIFO can accept right now */
        uint32_t available = tud_cdc_write_available();
        if (available == 0) {
            /* FIFO is full ?? flush what we have and wait for space */
            tud_cdc_write_flush();
            /* Run the TinyUSB task so the transfer can complete */
            tud_task();
            continue;
        }
        uint32_t to_write = (uint32_t)(len - written);
        if (to_write > available) to_write = available;
        written += (int)tud_cdc_write(ptr + written, to_write);
    }
    tud_cdc_write_flush();
    return len;
}

__attribute__((interrupt("WCH-Interrupt-fast"))) __attribute__((used)) void USB_LP_CAN1_RX0_IRQHandler(void) 
{
    tud_int_handler(0); 
}

__attribute__((interrupt("WCH-Interrupt-fast"))) __attribute__((used)) void USB_HP_CAN1_TX_IRQHandler(void) 
{
    tud_int_handler(0); 
}

void init_usb_clocks(void) {
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div2);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

void init_usb(void) {
    tusb_rhport_init_t dev_init = {.role = TUSB_ROLE_DEVICE, .speed = TUSB_SPEED_AUTO};

    tusb_init(0, &dev_init);

    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
}

// Invoked when received SET_PROTOCOL request
// protocol is either HID_PROTOCOL_BOOT (0) or HID_PROTOCOL_REPORT (1)
void tud_hid_set_protocol_cb(uint8_t instance, uint8_t protocol) {
  (void)instance;
  (void)protocol;

  // nothing to do since we use the same compatible boot report for both Boot and Report mode.
  // TODO set a indicator for user
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len) {
  (void)instance;
  (void)report;
  (void)len;

  // nothing to do
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(
    uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
  // TODO not Implemented
  (void)instance;
  (void)report_id;
  (void)report_type;
  (void)buffer;
  (void)reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(
    uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
  (void)report_id;
#ifdef CAPS_LOCK_LED
  // keyboard interface
  if (instance == ITF_NUM_KEYBOARD) {
    // Set keyboard LED e.g Capslock, Numlock etc...
    if (report_type == HID_REPORT_TYPE_OUTPUT) {
      // bufsize should be (at least) 1
      if (bufsize < 1) {
        return;
      }

      uint8_t const kbd_leds = buffer[0];

      if (kbd_leds & KEYBOARD_LED_CAPSLOCK) {
        // Capslock On: disable blink, turn led on
        caps_led_on();
      } else {
        caps_led_off();
      }
    }
  }
  #endif
}

void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {
  (void)itf;
  (void)rts;

  if (dtr) {
    // Terminal connected
  } else {
    // Terminal disconnected
  }
}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf) {
  (void)itf;
}

void add_to_keyboard_report(uint8_t keycode) {
  if(keycode == KC_NONE) return;
  for(uint8_t i = 2; i < HID_REPORT_KEY_LIMIT; i++) {
    if(keyboard_report[i] == keycode) return;
  }
  for(uint8_t i = 0; i < HID_REPORT_KEY_LIMIT; i++) {
    if(keyboard_report[i] == 0) {
      keyboard_report[i] = keycode;
      return;
    }
  }
}

void remove_from_keyboard_report(uint8_t keycode) {
  if(keycode == KC_NONE) return;
  for(uint8_t i = 0; i < HID_REPORT_KEY_LIMIT; i++) {
    if(keyboard_report[i] == keycode) {
      keyboard_report[i] = 0;
      break;
    }
  }
}

void add_modifier_to_report(uint8_t mod_mask) {
  modifiers_mask |= mod_mask;
  return;
}

void remove_modifier_from_report(uint8_t mod_mask) {
  modifiers_mask &= ~mod_mask;
  return;
}

void send_reports_to_host(void) {
  if(tud_hid_ready()) {
  tud_hid_keyboard_report(0, modifiers_mask, keyboard_report);
  }
}

