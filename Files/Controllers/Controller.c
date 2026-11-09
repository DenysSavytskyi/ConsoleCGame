//
// Created by User on 17.10.2026.
//

#include "Controller.h"
#include <stdlib.h>
#include <ncurses.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

static int cursorX = 1;
static int cursorY = 1;
static int maxCursorY = 1;

void initializeController() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_BLACK, COLOR_WHITE);
    }
    keypad(stdscr, FALSE);
}

void clearConsole() {
    erase();
    cursorX = 1;
    cursorY = 1;
    maxCursorY = 1;
    setCursor(cursorX, cursorY);
    refresh();
}

void sleep_ms(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void setCursor(int x, int y) {
    move(y - 1, x - 1);
    cursorX = x;
    cursorY = y;
    if (cursorY > maxCursorY) maxCursorY = cursorY;
}

void clearLine() {
    clrtoeol();
    cursorX = 1;
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
    addch((unsigned char)c);
    cursorX++;
    sleep_ms(charDelay);
    refresh();
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

void waitForInput() {
    getch();
}
