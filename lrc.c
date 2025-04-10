#include <stdio.h>
#include <string.h>
#include <conio.h>

void calculateLRC(char data[][9], int rows, char *lrc) {
    int colSum[8];
    int row, col;

    // Initialize column sum to 0
    for (col = 0; col < 8; col++) {
        colSum[col] = 0;
    }

    // XOR each column
    for (col = 0; col < 8; col++) {
        for (row = 0; row < rows; row++) {
            colSum[col] ^= (data[row][col] - '0'); // XOR bits column-wise
        }
        lrc[col] = colSum[col] + '0'; // Convert to char
    }
    lrc[8] = '\0'; // Null-terminate
}

void main() {
    clrscr();

    char data[4][9] = {
        "11001101",
        "10101010",
        "11110000",
        "00001111"
    };
    char lrc[9];
    int i;

    calculateLRC(data, 4, lrc);

    printf("Input Data Blocks:\n");
    for (i = 0; i < 4; i++) {
        printf("%s\n", data[i]);
    }

    printf("LRC: %s\n", lrc);

    getch(); // Wait for key press
}
