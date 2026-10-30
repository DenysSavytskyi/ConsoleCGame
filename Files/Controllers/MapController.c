//
// Created by User on 13.10.2026.
//

#include "MapController.h"
#include <stdlib.h>
#include <stdio.h>
#include "../Services/MapService.h"
#include "../Modules/Adventurer.h"
#include "Controller.h"

void printMap(Map *map, Adventurer *adventurer) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == adventurer->y && j == adventurer->x) {
                printf("A");
            } else {
                printf("%c", map->map[i][j]);
            }
        }
        printf("\n");
    }
}

int checkPossibleMoves(char *possibleInputs, Adventurer *adventurer, Map *map) {
    int count = 0;

    if (adventurer->x-1 >= 0 && map->map[adventurer->y][adventurer->x-1] != Wall) {
        possibleInputs[count++] = 'a';
    }
    if (adventurer->y-1 >= 0 && map->map[adventurer->y-1][adventurer->x] != Wall) {
        possibleInputs[count++] = 'w';
    }
    if (adventurer->x+1 < MAP_WIDTH && map->map[adventurer->y][adventurer->x+1] != Wall) {
        possibleInputs[count++] = 'd';
    }
    if (adventurer->y+1 < MAP_HEIGHT && map->map[adventurer->y+1][adventurer->x] != Wall) {
        possibleInputs[count++] = 's';
    }
    return count;
}

bool checkInput(char *possibleInputs, int inputCount, char input) {
    for (int i = 0; i < inputCount; i++) {
        if (input == possibleInputs[i]) {
            return true;
        }
    }
    return false;
}

char getAndCheckInput() {
    while (true) {
        clearConsole();
        printMap(getMap(), getAdventurer());
        char possibleInputs[4];
        int inputCount = checkPossibleMoves(possibleInputs, getAdventurer(), getMap());
        printf("Possible moves:\n");
        for (int i = 0; i < inputCount; i++) {
            printf("%c ", possibleInputs[i]);
        }
        printf("\n");
        printf("Enter your move: ");
        char input = readCommand("Move (WASD): ", "wasd");
        if (checkInput(possibleInputs, inputCount, input)) {
            return input;
        }
    }
}

