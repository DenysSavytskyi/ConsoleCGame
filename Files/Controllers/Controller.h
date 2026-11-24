#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#include <ncurses.h>
#pragma once

void sleep_ms(int milliseconds);
void clearConsole();
void setCursor(int x, int y);
void clearLine();
int getCursorX();
int getCursorY();
int getMaxCursorY();
void resetAllControllers();
void putDelayedCharAt(char c, int x, int y, int charDelay);
void putCharAt(char c, int x, int y);
void putChar(char c);
void putDelayedChar(char c, int charDelay);
void initializeController();
void waitForInput();
void printHorizontalLine(WINDOW *win, int y);
void printLeftAndRightTees(WINDOW *win, int y);
void printOnlyHorizontalLine(WINDOW *win, int y);
void printVerticalLine(WINDOW *win, int x);
void printCross(WINDOW *win, int y, int x);


#endif //GAME_CONTROLLER_H
