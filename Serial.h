#pragma systemFile
#ifndef SERIAL_HEADER
#define SERIAL_HEADER

#define SERIAL_PORT UART1
#define NO_PACKET 0xFF			//255
#define HEADER_PACKET 0xFE	//254
#define PACKET_SIZE 4				// # of packets after head

// Data Packet indexes
#define AXISX 0
#define AXISY 1
#define BUTTON1 2
#define BUTTON2 3


typedef struct _packet {
  short data[PACKET_SIZE];
} Packet;


/**
 * Configures the UART serial port specified in SERIAL_PORT for input.
*/
void configurePort() {
	// Configure serial port for user use
	configureSerialPort(SERIAL_PORT, uartUserControl);
	setBaudRate(SERIAL_PORT, baudRate115200);
}

/**
 * Updates a packet struct with the latest packet.
*/
void updatePacket(Packet* packet) {
	int count = 0;

	// Only exit if an entire packet is received.
	bool startReceiving = false;
	while(count < PACKET_SIZE) {
		char dataByte = getChar(SERIAL_PORT);

		// Reset count and start receiving if header byte arrives
		if(dataByte == HEADER_PACKET) {
			count = 0;
			startReceiving = true;
		}

		// Record the data that comes in
		else if(dataByte != NO_PACKET && startReceiving) {
			packet->data[count] = dataByte;
			count++;
		}
	}

	packet->data[AXISX] = packet->data[AXISX] - 126; // Sign Axes
	packet->data[AXISY] = packet->data[AXISY] - 126;
}

#endif
