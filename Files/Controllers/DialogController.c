#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Controller.h"

#if defined(_WIN32)
    #include <windows.h>
    void sleep_ms(int milliseconds) {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>
    void sleep_ms(int milliseconds) {
        usleep(milliseconds * 1000);
    }
#endif

#define FRAME_WIDTH 50

int currentLine = 0;

void setCursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
}

void clearLine() {
    printf("\033[2K");
    fflush(stdout);
}

void printTyped(const char *text, int delay_ms, int lineOfText, int startX) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            lineOfText++;
            setCursor(startX, lineOfText);
        } else {
            putchar(text[i]);
            fflush(stdout);
            sleep_ms(delay_ms);
        }
    }
}

void drawEmptyLeftFrame(int numberOfLines) {
    currentLine++;
    setCursor(0, currentLine);
    printf("  %c", 218);
    for (int i = 0; i < FRAME_WIDTH - 2; i++) printf("%c", 196);
    printf("%c\n", 191);
    currentLine++;

    for (int i = 0; i < numberOfLines; i++) {
        if (i==0) {
            printf("%c%c%c", 196,196, 180);
        } else {
            printf("  %c", 179);
        }
        for (int j = 0; j < FRAME_WIDTH - 2; j++) printf(" ");
        printf("%c\n", 179);
        currentLine++;
    }

    printf("  %c", 192);
    for (int i = 0; i < FRAME_WIDTH - 2; i++) printf("%c", 196);
    printf("%c\n", 217);
    currentLine++;
    fflush(stdout);
}

void drawEmptyRightFrame(int numberOfLines) {
    currentLine++;
    setCursor(0, currentLine);
    printf("          %c", 218);
    for (int i = 0; i < FRAME_WIDTH - 2; i++) printf("%c", 196);
    printf("%c\n", 191);
    currentLine++;

    for (int i = 0; i < numberOfLines; i++) {
        printf("          %c", 179);
        for (int j = 0; j < FRAME_WIDTH - 2; j++) printf(" ");
        if (i==0)
            printf("%c%c%c\n", 195, 196, 196);
        else
            printf("%c\n", 179);
        currentLine++;
    }

    printf("          %c", 192);
    for (int i = 0; i < FRAME_WIDTH - 2; i++) printf("%c", 196);
    printf("%c\n", 217);
    currentLine++;
    fflush(stdout);
}

void printLeft(const char *text, int numberOfLines) {
    drawEmptyLeftFrame(numberOfLines);
    setCursor(5, currentLine - numberOfLines - 1);
    printTyped(text, 50, currentLine - numberOfLines - 1, 5);
    sleep_ms(500);
}

void printRight(const char *text, int numberOfLines) {
    drawEmptyRightFrame(numberOfLines);
    setCursor(15, currentLine - numberOfLines - 1);
    printTyped(text, 50, currentLine - numberOfLines - 1, 15);
    sleep_ms(500);
}

void printRightInput(const char *text, char *buffer, int buffer_size, int numberOfLines) {
    drawEmptyRightFrame(numberOfLines + 1);
    setCursor(15, currentLine - numberOfLines - 2);
    printTyped(text, 50, currentLine - numberOfLines - 2, 15);

    setCursor(15, currentLine - numberOfLines - 1);
    printf("> ");
    fflush(stdout);

    if (fgets(buffer, buffer_size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
    }
}

void resetDialog() {
    clearConsole();
    currentLine = 0;
}
