//
// Created by User on 17.10.2026.
//

#include "Controller.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    fflush(stdout);
}

void readInput(const char *prompt, char *buffer, int bufferSize) {
    do {
        printf("%s", prompt);
        fflush(stdout);
        if (fgets(buffer, bufferSize, stdin) == NULL) {
            buffer[0] = '\0';
            return;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
    } while (buffer[0] == '\0');
}

char readCommand(const char *prompt, const char *allowed) {
    char input[32];
    while (true) {
        readInput(prompt, input, sizeof(input));
        if (strlen(input) == 1) {
            char command = (char)tolower((unsigned char)input[0]);
            if (strchr(allowed, command) != NULL) {
                return command;
            }
        }
        printf("Unknown command. Choose: %s\n", allowed);
    }
}

int readNumber(const char *prompt, int min, int max) {
    char input[32];
    char *end;
    long value;
    while (true) {
        readInput(prompt, input, sizeof(input));
        value = strtol(input, &end, 10);
        if (*end == '\0' && value >= min && value <= max) {
            return (int)value;
        }
        printf("Enter a number from %d to %d.\n", min, max);
    }
}

void waitForEnter() {
    char input[8];
    printf("\nPress Enter to continue...");
    fgets(input, sizeof(input), stdin);
}
