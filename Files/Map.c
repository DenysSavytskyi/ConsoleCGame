//
// Created by User on 17.10.2026.
//

#include "Map.h"

Map map;

Map* getMap() {
    return &map;
}

Map* generateMap () {
    // Initialize the map with empty cells
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            map.map[i][j] = ' ';
        }
    }
    map.map[1][1] = '#'; // Wall
    map.map[2][2] = '$'; // Treasure
    map.map[3][3] = 'E'; // Enemy
    map.map[4][4] = 'D'; // Exit
    map.map[5][5] = 'S'; // Shop
    map.map[6][6] = 'N'; // NPC


    return &map;
}