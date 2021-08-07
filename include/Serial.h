/** @file Serial.h
 * @brief Provide functions for reading and writing to UART.
 *
 * Provide functions for reading and writing to UART. This can be used to
 * control the robot and get sensor data with a Raspberry Pi or other
 * microcontroller.
 */


#ifndef SERIAL_H
#define SERIAL_H

/**
 * Value of a fgetc of "no packet received" when casted to a int.
*/
#define NO_PACKET -1

/**
 * Header attached to the start of every incoming packet used to signify the
 * start of a new packet, e.x.
 *
 * Packet 1 + 2: 255 234 43 0 4 255 230 43 0
 *
 * In this example, there are two distinct packets. When converted to packet_t,
 * one struct will contain 234 43 0 and another 230 43 0.
*/
#define HEADER_VALUE 255

#include <API.h>
#include "Types.h"

/*
  NOTE: On your Raspberry Pi, make extra sure you turn on serial communication
  and disable the log in screen. This can be done if you type "sudo
  raspi-config" in the terminal and go to Interfaces > Serial. In there, MAKE
  SURE you disable the login shell and turn on the serial port, then reboot.

  The reason this must be done is because the Raspberry Pi automatically
  switches off UART ports, so you need to turn them on. Sometimes, it will be
  on automatically, but a login screen will appear if you try to access it.
  This login screen must be turned off in order for this module to send input
  to the Raspberry Pi.
*/

/**
 * Struct that holds serial packet info of any length. The first element is
 * guaranteed to never be HEADER_VALUE. All data stored must be a unsigned
 * byte.
*/
typedef struct _packet {
  ubyte* data_arr;
  ubyte data_num;
} packet_t;

/**
 * Initialize uart1 for 8 data bits and 1 stop bit at 9600 Baud; Call this
 * before anything else.
*/
void serial_init();

/**
 * Send an unformatted string to uart1; Used for debugging. A \n character is
 * automatically inserted at the end before being sent off to the RPI, allowing
 * it to know when the string ends.
 *
 * @param string Unformatted string you want to send.
*/
void serial_write(const char* string);

/**
 * Loads the latest received packet to a pointer; This halts the current thread
 * until an entire packet is received. The data received is dynamically
 * allocated and must be freed using serial_destroy_packet before getting any
 * more.
 *
 * @see #serial_free_packet(packet_t* packet)
 * @param packet Pointer to the packet you want to overwrite.
 * @param num_data_packets Number of data packets you want to receive before
 * freeing program control.
*/
void serial_get_packet(packet_t* packet, ubyte num_data_packets);

/**
 * Frees the allocated data of a packet.
 *
 * @see #serial_get_packet(packet_t* packet, ubyte num_data_packets)
 * @param packet Pointer to the packet you want to free.
*/
void serial_free_packet(packet_t* packet);


#endif
