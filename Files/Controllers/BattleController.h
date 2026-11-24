#ifndef BATTLE_CONTROLLER_H
#define BATTLE_CONTROLLER_H
#include <ncurses.h>
#include "Controller.h"
#include "../Services/Service.h"
#pragma once


typedef enum BattleState {
    POTIONS,
    ABILITIES,
    OPTIONS
} BattleState;
//TODO delete POTIONS and implement using InventoryService

BattleState getBattleState();
void setBattleState(BattleState newState);
char getAndCheckBattleInput();
void printBattle();


#endif
