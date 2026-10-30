//
// Created by User on 17.10.2026.
//

#ifndef JAC_MAP_H
#define JAC_MAP_H
#pragma once
#include "../State.h"

typedef enum Cell {
    Empty = ' ',
    Wall = '#',
    Stuff = 'I',
    Treasure = '$',
    EnemyCell = 'E',
    Door = 'D',
    Player = 'A',
    NPC = 'N',
    Shop = 'S',
    Portal = 'P',
    QuestBoard = '?'
} Cell;

#define MAP_HEIGHT 12
#define MAP_WIDTH 24

typedef struct Map {
    Cell map[MAP_HEIGHT][MAP_WIDTH];
} Map;

State mapService();
Map* getMap();
Map* generateMap();


#endif //JAC_MAP_H
