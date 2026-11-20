#ifndef END_CONTROLLER_H
#define END_CONTROLLER_H
#include <ncurses.h>
#pragma once

typedef enum EndState {
    UNKNOWN_ERROR,
    GAME_OVER,
    VICTORY
} EndState;

void setEndState(EndState state);
void printEnd();

#endif
