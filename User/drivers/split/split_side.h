#pragma once

extern uint8_t local_row_offset;
extern uint8_t local_col_offset;
extern uint8_t remote_row_offset;
extern uint8_t remote_col_offset;

bool is_master(void);
bool is_left(void);
void update_split_master(void);
void split_side_update(void);