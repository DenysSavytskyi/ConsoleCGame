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
    Enemy = 'E',
    Door = 'D',
    Player = 'A',
    NPC = 'N',
    Shop = 'S',
    Portal = 'P'
} Cell;

typedef struct Map {
    Cell map[20][20];
} Map;

State mapService();
Map* getMap();
Map* generateMap();


#endif //JAC_MAP_H
