//
// Created by User on 13.10.2026.
//
#pragma once

#include "../Map.h"
#include "../Adventurer.h"
#ifndef JAC_MAPCONTROLLER_H
#define JAC_MAPCONTROLLER_H

#include "MapController.h"

typedef struct MapController {
    Map *map;
} MapController;

void clearConsole();
void printMap(Map *map, Adventurer *adventurer);
int checkPossibleMoves(char *possibleInputs, Adventurer *adventurer, Map *map);
bool checkInput(char *possibleInputs, int inputCount, char input);
char move();

#endif //JAC_MAPCONTROLLER_H
