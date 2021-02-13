#pragma systemFile
#ifndef SERIAL_SOURCE
#define SERIAL_SOURCE

typedef struct _packet {
  char data[PACKET_SIZE];
} Packet;


void configurePort() {
	// Configure serial port for user use
	configureSerialPort(SERIAL_PORT, uartUserControl);
	setBaudRate(SERIAL_PORT, baudRate115200);
}

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
}

#endif
