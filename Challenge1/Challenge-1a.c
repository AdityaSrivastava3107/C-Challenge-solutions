#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

int countZeroDataIndexes(data_packet_t packet) {
    int count = 0;
    for (int i = 0; i < packet.data_length; i++) {
        if (packet.data[i] == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    data_packet_t packet;
    // Initialize the packet with some values
    packet.id = 1;
    packet.data_length = 5;
    packet.data[0] = 0;
    packet.data[1] = 0;
    packet.data[2] = 1;
    packet.data[3] = 0;
    packet.data[4] = 0;
    packet.crc = 1234;

    int zeroCount = countZeroDataIndexes(packet);
    printf("Number of data indexes filled with 0's: %d\n", zeroCount);

    return 0;
}
