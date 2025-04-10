#include <stdio.h>
#include <string.h>
#include <conio.h>

// Function to simulate the sender
void sender(char messages[][100], int num_messages, char frames[][100]) {
    int i, length;
    for (i = 0; i < num_messages; i++) {
        length = strlen(messages[i]);      // Calculate the message length
        frames[i][0] = (char)length;        // First byte is the length
        strcpy(frames[i] + 1, messages[i]); // Copy message after length
    }
}

// Function to simulate the receiver
void receiver(char frames[][100], int num_frames) {
    int i, length;
    for (i = 0; i < num_frames; i++) {
        length = (int)frames[i][0]; // Read length
        printf("Frame %d (Length: %d): %.*s\n", i + 1, length, length, frames[i] + 1);
    }
}

void main() {
    clrscr();

    char messages[3][100] = {"Hello", "World", "Character Count Protocol"};
    int num_messages = 3;
    char frames[10][100]; // Array to store frames

    // Step 1: Sender creates frames
    sender(messages, num_messages, frames);

    // Step 2: Receiver processes frames
    printf("Receiver Output:\n");
    receiver(frames, num_messages);

    getch();
}
