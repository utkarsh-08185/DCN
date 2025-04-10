#include <stdio.h>
#include <string.h>
#include <conio.h>

// Function to calculate and append parity bits
void calculateVRC(char data[][9], int rows, char parityData[][10], int evenParity) {
    int i, j, count;
    for (i = 0; i < rows; i++) {
        count = 0;
        for (j = 0; j < 8; j++) {
            if (data[i][j] == '1') {
                count++;
            }
            parityData[i][j] = data[i][j]; // Copy data
        }
        // Even or Odd Parity
        parityData[i][8] = (evenParity) ? ((count % 2 == 0) ? '0' : '1') : ((count % 2 == 0) ? '1' : '0');
        parityData[i][9] = '\0';
    }
}

// Function to verify parity at the receiver
int verifyVRC(char parityData[][10], int rows, int evenParity) {
    int i, j, count;
    for (i = 0; i < rows; i++) {
        count = 0;
        for (j = 0; j < 9; j++) {
            if (parityData[i][j] == '1') {
                count++;
            }
        }
        if ((evenParity && count % 2 != 0) || (!evenParity && count % 2 == 0)) {
            return 0; // Parity check failed
        }
    }
    return 1; // Parity check passed
}

void main() {
    clrscr();

    char data[4][9] = {
        "11001101",
        "10101010",
        "11110000",
        "00001111"
    };
    char parityData[4][10];
    int rows = 4, i;

    // Step 1: Calculate and append even parity bits
    calculateVRC(data, rows, parityData, 1); // 1 for even parity

    printf("Data with Parity Bits (Even Parity):\n");
    for (i = 0; i < rows; i++) {
        printf("%s\n", parityData[i]);
    }

    // Step 2: Verify parity at receiver
    if (verifyVRC(parityData, rows, 1)) {
        printf("Parity Check Passed: No Errors Detected.\n");
    } else {
        printf("Parity Check Failed: Errors Detected.\n");
    }

    getch();
}
