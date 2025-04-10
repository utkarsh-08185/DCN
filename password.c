#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

#define MIN_PASSWORD_LENGTH 8
#define PASSWORD_EXPIRY_DAYS 30
#define MAX_HISTORY 5

// Structure to store user password and history
struct User {
    char current_password[100];
    char password_history[MAX_HISTORY][100];
    time_t last_changed;
};

// Function to check password length
int checkPasswordLength(char password[]) {
    return strlen(password) >= MIN_PASSWORD_LENGTH;
}

// Function to check password complexity
int checkPasswordComplexity(char password[]) {
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    int i;
    for (i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) has_upper = 1;
        if (islower(password[i])) has_lower = 1;
        if (isdigit(password[i])) has_digit = 1;
        if (ispunct(password[i])) has_special = 1;
    }
    return has_upper && has_lower && has_digit && has_special;
}

// Check if password is in history
int checkPasswordHistory(char password[], struct User *user) {
    int i;
    for (i = 0; i < MAX_HISTORY; i++) {
        if (strcmp(password, user->password_history[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Update password history
void updatePasswordHistory(struct User *user, char new_password[]) {
    int i;
    for (i = MAX_HISTORY - 1; i > 0; i--) {
        strcpy(user->password_history[i], user->password_history[i - 1]);
    }
    strcpy(user->password_history[0], new_password);
}

// Check if password expired
int isPasswordExpired(struct User *user) {
    time_t now = time(NULL);
    double seconds = difftime(now, user->last_changed);
    return (seconds / (60 * 60 * 24)) > PASSWORD_EXPIRY_DAYS;
}

// Set new password
int setPassword(struct User *user, char new_password[]) {
    if (!checkPasswordLength(new_password)) {
        printf("Error: Password must be at least %d characters long.\n", MIN_PASSWORD_LENGTH);
        return 0;
    }
    if (!checkPasswordComplexity(new_password)) {
        printf("Error: Must contain upper, lower, digit, and special character.\n");
        return 0;
    }
    if (checkPasswordHistory(new_password, user)) {
        printf("Error: You cannot reuse previous passwords.\n");
        return 0;
    }

    updatePasswordHistory(user, new_password);
    strcpy(user->current_password, new_password);
    user->last_changed = time(NULL);
    printf("Password successfully changed.\n");
    return 1;
}

// Authenticate user
int authenticateUser(struct User *user, char password[]) {
    if (strcmp(user->current_password, password) == 0) {
        printf("Authentication successful.\n");
        return 1;
    } else {
        printf("Authentication failed.\n");
        return 0;
    }
}

void main() {
    clrscr();
    struct User user = {0};
    char password[100], new_password[100];

    printf("Set your initial password:\n");
    while (1) {
        printf("Enter password: ");
        scanf("%s", password);
        if (setPassword(&user, password)) break;
    }

    if (isPasswordExpired(&user)) {
        printf("Your password has expired. Please change it.\n");
    }

    printf("Authenticate with your password:\n");
    printf("Enter password: ");
    scanf("%s", password);
    authenticateUser(&user, password);

    printf("\nChange your password:\n");
    while (1) {
        printf("Enter new password: ");
        scanf("%s", new_password);
        if (setPassword(&user, new_password)) break;
    }

    getch();
}
