#ifndef DIALOG_CONTROLLER_H
#define DIALOG_CONTROLLER_H
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "Controller.h"
#pragma once
#define PHRASES_DELAY_MS 100
#define CHARS_DELAY_MS 10

void printLeft(const char *text, int numberOfLines);
void printRightInput(const char *text, char *buffer, int buffer_size, int numberOfLines);
void resetDialog();

#endif
