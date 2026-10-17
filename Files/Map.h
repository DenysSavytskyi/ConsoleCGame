//
// Created by User on 17.10.2026.
//

#ifndef JAC_MAP_H
#define JAC_MAP_H
typedef enum Cell {
    Empty = ' ',
    Wall = '#',
    Treasure = '$',
    Enemy = 'E',
    Exit = 'D',
    Player = 'A',
    NPC = 'N',
    SHOP = 'S',
} Cell;

typedef struct Map {
    Cell map[20][20];
} Map;

Map* getMap();
Map* generateMap();


#endif //JAC_MAP_H
