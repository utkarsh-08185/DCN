#include <stdio.h>
#include <conio.h>

#define MAX_BUCKET_SIZE 10
#define TOKEN_RATE 1
#define DATA_SIZE 1

int bucket_tokens = 0;
int max_bucket_size = MAX_BUCKET_SIZE;
int token_rate = TOKEN_RATE;

void generateTokens() {
    if (bucket_tokens < max_bucket_size) {
        bucket_tokens += token_rate;
        if (bucket_tokens > max_bucket_size) {
            bucket_tokens = max_bucket_size;
        }
        printf("Tokens generated: %d. Current tokens: %d\n", token_rate, bucket_tokens);
    } else {
        printf("Bucket is full. No new tokens generated.\n");
    }
}

void transmitData() {
    if (bucket_tokens >= DATA_SIZE) {
        bucket_tokens -= DATA_SIZE;
        printf("Data transmitted. Remaining tokens: %d\n", bucket_tokens);
    } else {
        printf("Insufficient tokens. Transmission paused.\n");
    }
}

void main() {
    clrscr();
    printf("Token Bucket Congestion Control Simulation\n");
    printf("Press any key to simulate 1 second (ESC to exit)\n");

    while (1) {
        generateTokens();
        transmitData();

        if (getch() == 27) break; // ESC to exit
    }
}
