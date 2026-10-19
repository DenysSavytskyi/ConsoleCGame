#ifndef DIALOG_CONTROLLER_H
#define DIALOG_CONTROLLER_H
#pragma once
#include <stdio.h>

void sleep_ms(int milliseconds);

void setCursor(int x, int y);
void clearLine();
void printTyped(const char *text, int delay_ms, int lineOfText, int startX);
void drawEmptyLeftFrame(int numberOfLines);
void drawEmptyRightFrame(int numberOfLines);
void printLeft(const char *text, int numberOfLines);
void printRight(const char *text, int numberOfLines);
void printRightInput(const char *text, char *buffer, int buffer_size, int numberOfLines);
void resetDialog();

#endif
