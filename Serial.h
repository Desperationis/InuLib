#pragma systemFile
#ifndef SERIAL_HEADER
#define SERIAL_HEADER

#define SERIAL_PORT UART1
#define NO_PACKET 0xFF			//255
#define HEADER_PACKET 0xFE	//254
#define PACKET_SIZE 4

// Packet indexes
#define AXISX 0
#define AXISY 1
#define BUTTON1 2
#define BUTTON2 3


/**
 * Holds information and data about a packet.
 *
*/
typedef struct Packet;


/**
 * Configures the UART serial port specified in SERIAL_PORT for input.
*/
void configurePort();

/**
 * Updates a packet struct with the latest packet.
*/
void updatePacket(Packet* packet);

#include "Serial.c"
#endif
