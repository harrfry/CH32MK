#include <stdbool.h>
#include "usb.h"
#include "config.h"
#include "split.h"

static bool is_side_master = false;
static bool is_side_left = false;

uint8_t local_row_offset = 0;
uint8_t local_col_offset = 0;
uint8_t remote_row_offset = 0;
uint8_t remote_col_offset = 0;

bool is_master(void) {
    return is_side_master;
}

bool is_left(void) {
    return is_side_left;
}

void update_split_master(void) {
    if(tud_connected()) {
        is_side_master = true;
        return;
    }
}

void split_side_init(void) {
    update_split_master();

    if(!is_side_master) {
        local_row_offset = 0;
        local_col_offset = 0;
        remote_col_offset = 0;
        remote_row_offset = 0;
    } else if(is_side_left) {
        local_row_offset = 0;
        local_col_offset = 0;
        remote_row_offset = ROW_OFFSET;
        remote_col_offset = COL_OFFSET;
    } else {
        local_row_offset = ROW_OFFSET;
        local_col_offset = COL_OFFSET;
        remote_row_offset = 0;
        remote_col_offset = 0;
    }
}

