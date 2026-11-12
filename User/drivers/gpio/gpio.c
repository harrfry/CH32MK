#include "pins.h"
#include "config.h"

void GPIO_EnableClock(GPIO_TypeDef* PORT) {
    if (PORT == GPIOA)      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if (PORT == GPIOB) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    else if (PORT == GPIOC) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    else if (PORT == GPIOD) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
}

#if defined(COL2ROW) || defined(ROW2COL)

void init_matrix_pins(const pin_t *row_pins, const pin_t *col_pins) {
    #ifdef COL2ROW

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  
    for (uint8_t i = 0; i < MATRIX_ROWS_PER_HALF; i++) {
    

    GPIO_EnableClock(row_pins[i].PORT);
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.GPIO_Pin = row_pins[i].PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    
    // 3. Write it into the configuration register space
    GPIO_Init(row_pins[i].PORT, &GPIO_InitStructure);
    GPIO_ResetBits(row_pins[i].PORT, row_pins[i].PIN);
    }
    for (uint8_t i = 0; i < MATRIX_COLS_PER_HALF; i++) {
        GPIO_EnableClock(col_pins[i].PORT);
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        
        GPIO_InitStructure.GPIO_Pin = col_pins[i].PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    
        // 3. Write it into the configuration register space
        GPIO_Init(col_pins[i].PORT, &GPIO_InitStructure);
        GPIO_ResetBits(col_pins[i].PORT, col_pins[i].PIN);
    }
    #endif
    #ifdef ROW2COL
    for (uint8_t i = 0; i < MATRIX_ROWS_PER_HALF; i++) {
    

    GPIO_EnableClock(row_pins[i].PORT);
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // 2. Configure PB2 as a standard 50MHz Push-Pull output
    GPIO_InitStructure.GPIO_Pin = row_pins[i].PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    // 3. Write it into the configuration register space
    GPIO_Init(row_pins[i].PORT, &GPIO_InitStructure);
    GPIO_ResetBits(row_pins[i].PORT, row_pins[i].PIN);
    }
    for (uint8_t i = 0; i < MATRIX_COLS_PER_HALF; i++) {
        GPIO_EnableClock(col_pins[i].PORT);
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        
        GPIO_InitStructure.GPIO_Pin = col_pins[i].PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    
        // 3. Write it into the configuration register space
        GPIO_Init(col_pins[i].PORT, &GPIO_InitStructure);
        GPIO_ResetBits(col_pins[i].PORT, col_pins[i].PIN);
    }
    #endif
}

#endif

#ifdef DIRECT_PIN
void init_direct_pins(const pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS]) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            if (direct_pins[r][c].PORT == NULL) continue; // Skip unused spaces
            
            GPIO_EnableClock(direct_pins[r][c].PORT);
            GPIO_InitTypeDef GPIO_InitStructure = {0};

            GPIO_InitStructure.GPIO_Pin = direct_pins[r][c].PIN;
            
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
            GPIO_Init(direct_pins[r][c].PORT, &GPIO_InitStructure);
            GPIO_WriteBit(direct_pins[r][c].PORT, direct_pins[r][c].PIN, Bit_RESET);
        }
    }
}
#endif

#ifdef CAPS_LOCK_LED
const pin_t caps_lock_led = CAPS_LOCK_LED;
void init_caps_led() {
    GPIO_EnableClock(caps_lock_led.PORT);
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = caps_lock_led.PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(caps_lock_led.PORT, &GPIO_InitStructure);
}

void caps_led_on() {
    GPIO_WriteBit(caps_lock_led.PORT, caps_lock_led.PIN, Bit_SET);
}

void caps_led_off() {
    GPIO_WriteBit(caps_lock_led.PORT, caps_lock_led.PIN, Bit_RESET);
}
#endif

