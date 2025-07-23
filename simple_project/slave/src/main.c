#include "uart.h"

int main() {

    // Initialize UART at 115200 baud, 4MHz clock
    uart_init(4000000, 115200);
    uart_puts ("The quick brown fox jumped over the lazy dog.\r\n");
}
