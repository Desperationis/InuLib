#include "Serial.h"

/*
  Initializes uart1 for 8 data bits and 1 stop bit.
*/
void serial_init() {
  usartInit(uart1, 9600, SERIAL_DATABITS_8 | SERIAL_STOPBITS_1);
}

/*
  Sends an unformatted string to uart1.
*/
void serial_write(const char* string) {
  fprint(string, uart1);
}
