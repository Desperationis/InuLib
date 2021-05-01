#include "Serial.h"
#include <string.h>

void serial_init() {
  usartInit(uart1, 9600, SERIAL_DATABITS_8 | SERIAL_STOPBITS_1);
}

void serial_write(const char* string) {
  size_t len = strlen(string);

  // One for extra char, one for trailing zero
  char *str2 = malloc(len + 1 + 1);

  strcpy(str2, string);
  str2[len] = '\n';
  str2[len + 1] = '\0';

  fprint(str2, uart1);
  free(str2);
}
