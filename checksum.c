#include <stdio.h>
#include <conio.h>

// Function to calculate checksum
unsigned int calculateChecksum(int data[], int n) {
    unsigned int sum = 0;
    int i;

    // Add all data blocks
    for (i = 0; i < n; i++) {
        sum += data[i];
    }

    // Calculate the 1's complement of the sum
    return ~sum;
}

void main() {
    clrscr(); // Clear screen

    int data[] = {0x1234, 0x5678, 0x9ABC, 0xDEF0}; // Example 16-bit blocks
    int n = sizeof(data) / sizeof(data[0]);
    int i;
    unsigned int checksum;

    // Calculate checksum
    checksum = calculateChecksum(data, n);

    // Print input data blocks
    printf("Input Data Blocks:\n");
    for (i = 0; i < n; i++) {
        printf("0x%X\n", data[i]);
    }

    // Print calculated checksum
    printf("Checksum: 0x%X\n", checksum);

    getch(); // Wait for key press
}
