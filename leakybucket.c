#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_BUCKET_SIZE 10
#define LEAK_RATE 1

int bucket_size = 0;

void simulateIncomingData() {
    int data_arrival = rand() % 3 + 1;
    int overflow;

    printf("Incoming data: %d packets\n", data_arrival);

    if (bucket_size + data_arrival <= MAX_BUCKET_SIZE) {
        bucket_size += data_arrival;
        printf("Data added. Current bucket size: %d packets\n", bucket_size);
    } else {
        overflow = (bucket_size + data_arrival) - MAX_BUCKET_SIZE;
        bucket_size = MAX_BUCKET_SIZE;
        printf("Bucket overflow! %d packets discarded. Bucket at max capacity: %d\n", overflow, bucket_size);
    }
}

void leakData() {
    if (bucket_size > 0) {
        bucket_size -= LEAK_RATE;
        if (bucket_size < 0) bucket_size = 0;
        printf("Data leaked: %d packet(s). Current bucket size: %d\n", LEAK_RATE, bucket_size);
    }
}

void main() {
    clrscr();
    printf("Leaky Bucket Simulation\n");
    printf("Press any key to simulate 1 second (ESC to exit)\n");

    while (1) {
        simulateIncomingData();
        leakData();

        if (getch() == 27) break; // ESC to exit
    }
}
