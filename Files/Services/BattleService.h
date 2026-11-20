#ifndef BATTLE_SERVICE_H
#define BATTLE_SERVICE_H
#include "../Modules/State.h"
#include "InventoryService.h"
#include "../Controllers/BattleController.h"
#include "../Modules/Adventurer.h"
#include "MapService.h"
#include "../Controllers/EndController.h"
#include "../Modules/EnemyEntity.h"
#pragma once

State battleService();
State battle();
int checkPossibleMovesBattle(char *possibleInputs);

#endif
