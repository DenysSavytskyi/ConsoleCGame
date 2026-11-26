#ifndef BATTLE_CONTROLLER_H
#define BATTLE_CONTROLLER_H
#include <ncurses.h>
#include "Controller.h"
#include "../Services/Service.h"
#pragma once


typedef enum BattleState {
    OPTIONS,
    ABILITIES
} BattleState;

BattleState getBattleState();
void setBattleState(BattleState newState);
char getAndCheckBattleInput();


#endif
