//
// Created by User on 13.10.2026.
//

#include "MapController.h"
#include "../Services/Service.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "Controller.h"


void printRoom() {
    for (int y = 0; y < getCurrentRoom()->roomSize; y++) {
        for (int x = 0; x < getCurrentRoom()->roomSize; x++) {
            if (y == getAdventurer()->y && x == getAdventurer()->x) {
                putChar('A');
            } else {
                putChar(getCurrentRoomCell(y,x));
            }
        }
        setCursor(1, getCursorY()+1);
    }
}

void printMap() {
    printRoom();
    printMinimap();
}

void printMinimap() {
    int x = getCurrentRoom()->roomSize + 2;
    int y = 0;
    setCursor(x, y);
    printf("Minimap: ");
    y++;
    for (int i = 0; i < getMap()->roomsCount; i++) {
        if (i % 3 == 0) {
            y++;
            setCursor(x, y);
        }
        putChar(getMinimap()[i]);
    }
}

char getAndCheckMapInput() {
    while (true) {
        clearConsole();
        printMap();
        // All possible moves: W, A, S, D, E(interact), I(inventory)
        char possibleInputs[7];
        possibleInputs[6] = '\0';
        int inputCount = checkPossibleMovesMap(possibleInputs);
        setCursor(0, getCurrentRoom()->roomSize + 2);
        printf("Possible moves:\n");
        for (int i = 0; i < inputCount; i++) {
            putchar(possibleInputs[i]);
            putchar(' ');
        }
        printf("\nEnter your move: ");
        char input = (char)getch();
        if (checkInput(possibleInputs, input)) {
            return input;
        }
    }
}


