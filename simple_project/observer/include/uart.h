#pragma once

#include <stdint.h>

// Register definitions (offsets from base)
#define UARTDR    0x000
#define UARTRSR   0x004
#define UARTFR    0x018
#define UARTILPR  0x020
#define UARTIBRD  0x024
#define UARTFBRD  0x028
#define UARTLCR_H 0x02C
#define UARTCR    0x030
#define UARTIFLS  0x034
#define UARTIMSC  0x038
#define UARTRIS   0x03C
#define UARTMIS   0x040
#define UARTICR   0x044
#define UARTDMACR 0x048

// Flag Register (UARTFR) bits
#define CTS  0x001
#define DSR  0x002
#define DCD  0x004
#define BUSY 0x008
#define RXFE 0x010
#define TXFF 0x020
#define RXFF 0x040
#define TXFE 0x080
#define RI   0x100

// Control Register (UARTCR) bits
#define UARTEN  0x001
#define SIREN   0x002
#define SIRLP   0x004
#define LBE     0x080
#define TXE     0x100
#define RXE     0x200
#define DTR     0x400
#define RTS     0x800
#define OUT1    0x1000
#define OUT2    0x2000
#define RTSEN   0x4000
#define CTSEN   0x8000

// Line Control Register (UARTLCR_H) bits
#define BRK  0x01
#define PEN  0x02
#define EPS  0x04
#define STP2 0x08
#define FEN  0x10
#define WLEN_5 0x00
#define WLEN_6 0x20
#define WLEN_7 0x40
#define WLEN_8 0x60
#define SPS   0x80

// UART base address
#define UART_BASE 0x40004400

// Memory-mapped register access
#define REG(addr) *((volatile uint32_t *)(UART_BASE + (addr)))

// Initialize UART
void uart_init(uint32_t uart_clk, uint32_t baud_rate);

// Check if transmit FIFO is full
int uart_tx_fifo_full(void);

// Check if receive FIFO is empty
int uart_rx_fifo_empty(void);

// Transmit a character
void uart_putc(char c);

// Receive a character
char uart_getc(void);

// Transmit a string
void uart_puts(const char *str);

// Set FIFO trigger levels
void uart_set_fifo_levels(uint8_t rx_level, uint8_t tx_level);

// Enable hardware flow control
void uart_enable_flow_control(void);

// Disable hardware flow control
void uart_disable_flow_control(void);

// Enable interrupts
void uart_enable_interrupts(uint16_t mask);

// Disable interrupts
void uart_disable_interrupts(uint16_t mask);

// Get raw interrupt status
uint16_t uart_get_raw_interrupts(void);

// Clear interrupts
void uart_clear_interrupts(uint16_t mask);
