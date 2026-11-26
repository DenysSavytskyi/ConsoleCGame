#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#include <ncurses.h>
#pragma once

void sleep_ms(int milliseconds);
void clearConsole();
void setCursor(int x, int y);
void resetAllControllers();
void printInputOptions(int y, const char *title, const char *possibleInputs, int inputCount);
char getInputChar();
void initializeController();
void printLeftAndRightTees(WINDOW *win, int y);
void printOnlyHorizontalLine(WINDOW *win, int y);
void printVerticalLine(WINDOW *win, int x);
void printCross(WINDOW *win, int y, int x);


#endif //GAME_CONTROLLER_H
