#include "uart.h"

int main() {
    uart_init(4000000, 115200);
    char c = '\0';
    c = uart_getc();
    if (c != '\0'){
        uart_puts("data received\r\n");
    }
}
