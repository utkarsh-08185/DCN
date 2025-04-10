#include <stdio.h>
#include <string.h>
#include <conio.h>

// XOR operation function
void xorOperation(char dividend[], char divisor[], int length) {
    int i;
    for (i = 0; i < length; i++) {
	dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
    }
}

// CRC Calculation
void calculateCRC(char data[], char generator[], char crc[]) {
    int dataLen, genLen, i , j;
    char dividend[100], temp[100];

    dataLen = strlen(data);
    genLen = strlen(generator);

    // Copy data to dividend and append zeros
    strcpy(dividend, data);
    for (i = 0; i < genLen - 1; i++) {
	dividend[dataLen + i] = '0';
    }
    dividend[dataLen + genLen - 1] = '\0';

    // Copy initial part to temp
    for (i = 0; i < genLen; i++) {
	temp[i] = dividend[i];
    }
    temp[genLen] = '\0';

    for (i = 0; i < dataLen; i++) {
	if (temp[0] == '1') {
	    xorOperation(temp, generator, genLen);
	}

	// Left shift temp by 1 manually
	for (j = 0; j < genLen - 1; j++) {
	    temp[j] = temp[j + 1];
	}
	temp[genLen - 1] = dividend[i + genLen];
    }

    // Copy the CRC part
    for (i = 0; i < genLen - 1; i++) {
	crc[i] = temp[i];
    }
    crc[genLen - 1] = '\0';
}

// CRC validation at receiver side
int validateCRC(char data[], char generator[]) {
    int dataLen, genLen, i, j;
    char temp[100];

    dataLen = strlen(data);
    genLen = strlen(generator);

    // Copy initial part
    for (i = 0; i < genLen; i++) {
	temp[i] = data[i];
    }
    temp[genLen] = '\0';

    for (i = 0; i < dataLen - genLen + 1; i++) {
	if (temp[0] == '1') {
	    xorOperation(temp, generator, genLen);
	}

	// Left shift manually
	for (j = 0; j < genLen - 1; j++) {
	    temp[j] = temp[j + 1];
	}
	temp[genLen - 1] = data[i + genLen];
    }

    // Check if remainder is all zeros
    for (i = 0; i < genLen - 1; i++) {
	if (temp[i] != '0') {
	    return 0; // Error detected
	}
    }
    return 1; // No error
}

void main() {
    char data[100], generator[100], transmittedData[100], crc[100];

    printf("Enter the data bits: ");
    scanf("%s", data);

    printf("Enter the generator polynomial: ");
    scanf("%s", generator);

    calculateCRC(data, generator, crc);

    strcpy(transmittedData, data);
    strcat(transmittedData, crc);

    printf("Transmitted Data (Data + CRC): %s\n", transmittedData);

    if (validateCRC(transmittedData, generator)) {
	printf("CRC Check Passed: No Errors Detected.\n");
    } else {
	printf("CRC Check Failed: Errors Detected.\n");
    }
    getch();
}
