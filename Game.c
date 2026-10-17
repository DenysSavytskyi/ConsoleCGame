//
// Created by User on 13.10.2026.
//
#pragma once
#include "stdlib.h"
#include "stdio.h"
#include "Files/Adventurer.h"
#include "Files/Controllers/MapController.h"
#include "Files/Map.h"

int main() {
    printf("Welcome to the game!\n");
    Adventurer *adventurer = createAdventurer();
    bool cont = true;
    MapController mapController;
    mapController.map = generateMap();
    while (cont) {
        char input = move();
        if (input == 'w') {
            getAdventurer()->y--;
        } else if (input == 'a') {
            getAdventurer()->x--;
        } else if (input == 's') {
            getAdventurer()->y++;
        } else if (input == 'd') {
            getAdventurer()->x++;
        }
    }
}