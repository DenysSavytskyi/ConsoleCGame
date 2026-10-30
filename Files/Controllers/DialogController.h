#ifndef DIALOG_CONTROLLER_H
#define DIALOG_CONTROLLER_H
#pragma once
#include <stdio.h>
#define PHRASES_DELAY_MS 5
#define CHARS_DELAY_MS 1



void printTyped(const char *text, int lineOfText, int startX);
void drawEmptyLeftFrame(int numberOfLines);
void drawEmptyRightFrame(int numberOfLines);
void printLeft(const char *text, int numberOfLines);
void printRight(const char *text, int numberOfLines);
void printRightInput(const char *text, char *buffer, int buffer_size, int numberOfLines);
void resetDialog();

#endif
