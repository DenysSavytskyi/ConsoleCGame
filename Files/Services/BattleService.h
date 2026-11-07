#ifndef BATTLE_SERVICE_H
#define BATTLE_SERVICE_H
#pragma once

#include "../Controllers/BattleController.h"
#include "../Modules/State.h"

State battleService();
State battle();
int checkPossibleMovesBattle(char *possibleInputs);

#endif
