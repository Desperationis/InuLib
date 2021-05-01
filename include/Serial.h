#ifndef SERIAL_H
#define SERIAL_H

#include <API.h>

/*
  NOTE: On your Raspberry Pi, make extra sure you turn on serial communication
  and disable the log in screen. This can be done if you type "sudo raspi-config"
  in the terminal and go to Interfaces > Serial. In there, MAKE SURE you disable
  the login shell and turn on the serial port, then reboot.

  The reason this must be done is because the Raspberry Pi automatically
  switches off UART ports, so you need to turn them on. Sometimes, it will be
  on automatically, but a login screen will appear if you try to access it.
  This login screen must be turned off in order for this module to send input
  to the Raspberry Pi.
*/


/*
  Initializes uart1 for 8 data bits and 1 stop bit at 9600 Baud; Call this
  before anything else.
*/
void serial_init();

/*
  Sends an unformatted string to uart1; Used for debugging. A \n character is
  automatically inserted at the end before being sent off to the RPI, allowing
  it to know when the string ends.
*/
void serial_write(const char* string);


#endif SERIAL_H
