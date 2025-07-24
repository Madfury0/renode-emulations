#include "uart.h"

void uart_init(uint32_t uart_clk, uint32_t baud_rate) {
    // Disable UART
    REG(UARTCR) &= ~(UARTEN | TXE | RXE);
    
    // Clear pending interrupts
    REG(UARTICR) = 0x7FF;
    
    // Set baud rate
    float divisor = (float)uart_clk / (16.0f * baud_rate);
    uint32_t ibrd = (uint32_t)divisor;
    uint32_t fbrd = (uint32_t)((divisor - ibrd) * 64 + 0.5f);
/*
    int divisor = (int)uart_clk / (16 * baud_rate);
    uint32_t ibrd = (uint32_t)divisor;
    uint32_t fbrd = (uint32_t)((divisor - ibrd) * 64 + 1);
  */  
    REG(UARTIBRD) = ibrd;
    REG(UARTFBRD) = fbrd;
    
    // Set line control: 8N1, FIFO enabled
    REG(UARTLCR_H) = WLEN_8 | FEN;
    
    // Enable UART, TX, and RX
    REG(UARTCR) |= UARTEN | TXE | RXE;
}

// Check if transmit FIFO is full
int uart_tx_fifo_full(void) {
    return (REG(UARTFR) & TXFF);
}

// Check if receive FIFO is empty
int uart_rx_fifo_empty(void) {
    return (REG(UARTFR) & RXFE);
}

// Transmit a character
void uart_putc(char c) {
    // Wait until there's space in the transmit FIFO
    while (uart_tx_fifo_full()) {}
    
    // Write character to data register
    REG(UARTDR) = c;
}

// Receive a character
char uart_getc(void) {
    // Wait until data is available
    while (uart_rx_fifo_empty()) {}
    
    // Read character from data register
    return (char)(REG(UARTDR) & 0xFF);
}

// Transmit a string
void uart_puts(const char *str) {
    while (*str) {
        uart_putc(*str++);
    }
}

// Set FIFO trigger levels
void uart_set_fifo_levels(uint8_t rx_level, uint8_t tx_level) {
    // Levels: 0=1/8, 1=1/4, 2=1/2, 3=3/4, 4=7/8
    uint32_t levels = (tx_level << 3) | (rx_level << 0);
    REG(UARTIFLS) = levels & 0x3F;
}

// Enable hardware flow control
void uart_enable_flow_control(void) {
    REG(UARTCR) |= RTSEN | CTSEN;
}

// Disable hardware flow control
void uart_disable_flow_control(void) {
    REG(UARTCR) &= ~(RTSEN | CTSEN);
}

// Enable interrupts
void uart_enable_interrupts(uint16_t mask) {
    REG(UARTIMSC) |= mask;
}

// Disable interrupts
void uart_disable_interrupts(uint16_t mask) {
    REG(UARTIMSC) &= ~mask;
}

// Get raw interrupt status
uint16_t uart_get_raw_interrupts(void) {
    return REG(UARTRIS) & 0x7FF;
}

// Clear interrupts
void uart_clear_interrupts(uint16_t mask) {
    REG(UARTICR) = mask;
}
