#ifndef BATTLE_CONTROLLER_H
#define BATTLE_CONTROLLER_H
#pragma once
#include <ncurses.h>
#include "Controller.h"
#include "../Services/InventoryService.h"
#include "../Services/Service.h"
#include "../Services/BattleService.h"
#include "../Modules/EnemyEntity.h"
#include "../Services/MapService.h"

typedef enum BattleState {
    POTIONS,
    ABILITIES,
    OPTIONS
} BattleState;

BattleState getBattleState();
void setBattleState(BattleState newState);
char getAndCheckBattleInput();
void printBattle();


#endif
