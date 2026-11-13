#include "split.h"
#include "ch32v20x.h"
#include "config.h"
#include <stdbool.h>

volatile key_packet_t rx_buffer[SPLIT_BUFFER_SIZE] = {0};
volatile key_packet_t tx_packet = {0};
static uint16_t rx_read_ptr = 0;
static key_packet_t tx_ring_buffer[SPLIT_BUFFER_SIZE] = {0};
static uint8_t tx_head = 0;
static uint8_t tx_tail = 0;

#ifndef ROW_OFFSET
#define ROW_OFFSET 0
#endif
#ifndef COL_OFFSET
#define COL_OFFSET 0
#endif


void split_transport_init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    DMA_InitTypeDef DMA_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    // Enable Clocks
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

#ifdef TRANSPORT_USART2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    // USART2 Pins: PA2 (TX), PA3 (RX)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // USART Configuration
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);

    // NVIC for IDLE Line Interrupt
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // --- DMA TX (Channel 7) ---
    DMA_DeInit(DMA1_Channel7);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DATAR);
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)(&tx_packet);
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize         = sizeof(key_packet_t);
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Disable; // Fixed: Disabled for single struct pointer!
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel7, &DMA_InitStructure);

    // --- DMA RX (Channel 6 - Circular) ---
    DMA_DeInit(DMA1_Channel6);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DATAR);
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)rx_buffer;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = SPLIT_BUFFER_SIZE * sizeof(key_packet_t);
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable; // Enabled for ring buffer
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel6, &DMA_InitStructure);

    USART_DMACmd(USART2, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE);
    DMA_Cmd(DMA1_Channel6, ENABLE);
    
    //USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
    USART_Cmd(USART2, ENABLE);

#elif defined(TRANSPORT_USART1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // USART1 Pins: PA9 (TX), PA10 (RX)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // USART Configuration
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);

    // NVIC for IDLE Line Interrupt
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // --- DMA TX (Channel 4) ---
    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DATAR);
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)(&tx_packet);
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize         = sizeof(key_packet_t);
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Disable; // Fixed: Disabled for single struct pointer!
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);

    // --- DMA RX (Channel 5 - Circular) ---
    DMA_DeInit(DMA1_Channel5);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DATAR);
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)rx_buffer;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = SPLIT_BUFFER_SIZE * sizeof(key_packet_t);
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable; // Enabled for ring buffer
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);

    USART_DMACmd(USART1, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE);
    DMA_Cmd(DMA1_Channel5, ENABLE);
    
    //USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    USART_Cmd(USART1, ENABLE);
#endif
}

uint16_t usart_rx_available(void) {
    #ifdef TRANSPORT_USART2
    uint16_t current_byte_idx = (SPLIT_BUFFER_SIZE * sizeof(key_packet_t)) - DMA_GetCurrDataCounter(DMA1_Channel6);
    uint16_t rx_write_ptr = current_byte_idx / sizeof(key_packet_t);
    if(rx_write_ptr >= rx_read_ptr) {
        return rx_write_ptr + rx_read_ptr;
    } else {
        return (SPLIT_BUFFER_SIZE - rx_read_ptr) + rx_write_ptr;
    }
    #endif
}

key_packet_t usart_rx_read(void) {
    if(usart_rx_available() == 0) return (key_packet_t){.row = 0, .col = 0, .state = 3, .checksum = 0};
    key_packet_t packet = rx_buffer[rx_read_ptr];

    rx_read_ptr = (rx_read_ptr + 1) % SPLIT_BUFFER_SIZE;

    return packet;
}

void usart_tx_send(uint8_t row, uint8_t col, uint8_t state) {
    uint8_t next_head = (tx_head + 1) % SPLIT_BUFFER_SIZE;
    if(next_head == tx_tail) {
        return;
    }

    tx_ring_buffer[tx_head].state = state;
    tx_ring_buffer[tx_head].row = row;
    tx_ring_buffer[tx_head].col = col;
    tx_ring_buffer[tx_head].checksum = state ^ row ^ col;
    tx_head = next_head;
}

void process_tx_queue(void) {
    #ifdef TRANSPORT_USART2
    if(DMA_GetCurrDataCounter(DMA1_Channel7) == 0 && (USART2->STATR & USART_FLAG_TC)) {
        if(tx_head != tx_tail) {
            DMA_Cmd(DMA1_Channel7, DISABLE);
            tx_packet = tx_ring_buffer[tx_tail];
            tx_tail = (tx_tail + 1) % SPLIT_BUFFER_SIZE;

            DMA_SetCurrDataCounter(DMA1_Channel7, sizeof(key_packet_t));
            DMA1_Channel7->MADDR = (uint32_t)&tx_packet;
            DMA_Cmd(DMA1_Channel7, ENABLE);
        }
    }
    #endif
}

void split_housekeeping_task(volatile bool matrix_debounced[MATRIX_ROWS][MATRIX_COLS], bool is_master) {
    if(is_master) {
        key_packet_t packet = usart_rx_read();
        if(packet.state == 3) return;
        uint8_t checksum = packet.row ^ packet.col ^ packet.state;
        if(packet.checksum == checksum) {
            matrix_debounced[packet.row + ROW_OFFSET][packet.col + COL_OFFSET] = (packet.state == 1);
        }

    } else {
        process_tx_queue();
    }
}