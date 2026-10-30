//
// Created by User on 17.10.2026.
//

#include "Controller.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

static int cursorX = 1;
static int cursorY = 1;
static int maxCursorY = 1;

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    cursorX = 1;
    cursorY = 1;
    maxCursorY = 1;
    setCursor(cursorX, cursorY);
    fflush(stdout);
}

void sleep_ms(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void setCursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
    cursorX = x;
    cursorY = y;
    if (cursorY > maxCursorY) maxCursorY = cursorY;
    fflush(stdout);
}

void clearLine() {
    printf("\033[2K");
    cursorX = 1;
    fflush(stdout);
}

int getCursorX() {
    return cursorX;
}

int getCursorY() {
    return cursorY;
}
int getMaxCursorY() {
    return maxCursorY;
}

void resetAllControllers() {
    clearConsole();
    setCursor(1, 1);
    cursorX = 1;
    cursorY = 1;
    maxCursorY = 1;
}

void putDelayedCharAt(char c, int x, int y, int charDelay) {
    setCursor(x, y);
    putchar(c);
    cursorX++;
    sleep_ms(charDelay);
    fflush(stdout);
}

void putCharAt(char c, int x, int y) {
    putDelayedCharAt(c, x, y, 0);
}

void putChar(char c) {
    putDelayedCharAt(c, cursorX, cursorY, 0);
}

void putDelayedChar(char c, int charDelay) {
    putDelayedCharAt(c, cursorX, cursorY, charDelay);
}
