#include "Serial.h"
#include <string.h>
#include "Types.h"

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

void serial_get_packet(packet_t* packet, ubyte num_data_packets) {
    packet->data_arr = malloc(sizeof(ubyte) * num_data_packets);
    packet->data_num = num_data_packets;
    int count = 0;

    // Exit once entire packet is received
    bool startReceiving = false;
    while(count < num_data_packets) {
        int data = fgetc(uart1);

        // Reset count and start receiving if header byte arrives; This is crucial
        // for synchronization.
        if(data == HEADER_VALUE) {
            count = 0;
            startReceiving = true;
        }

        // Record the data that comes in
        else if(data != NO_PACKET && startReceiving) {
            packet->data_arr[count] = (ubyte)data;
            count++;
        }
    }
}

void serial_free_packet(packet_t* packet) {
    free(packet->data_arr);
    packet->data_arr = NULL;
    packet->data_num = 0;
}
