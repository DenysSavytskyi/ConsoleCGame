//
// Created by User on 17.10.2026.
//

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
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


#endif //GAME_CONTROLLER_H
