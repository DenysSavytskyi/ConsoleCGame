#ifndef JAC_MAPCONTROLLER_H
#define JAC_MAPCONTROLLER_H
#include "../Services/Service.h"
#include <ncurses.h>
#include "../Services/MapService.h"
#include "../Modules/Adventurer.h"
#include "Controller.h"
#pragma once

void printMap();
void printRoom();
void printMinimap();
char getAndCheckMapInput();

#endif //JAC_MAPCONTROLLER_H
