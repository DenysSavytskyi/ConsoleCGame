//
// Created by User on 06.10.2026.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Adventurer.h"
#include "Profession.h"
#include "../Controllers/DialogController.h"

static Adventurer *adventurer = NULL;

Adventurer* getAdventurer() {
    return adventurer;
}

Adventurer* newAdventurer(char *name, Profession profession, int hpMax, int damage, int money, int xp, int x, int y) {
    if (adventurer == NULL) {
        adventurer = malloc(sizeof(*adventurer));
    }
    if (adventurer == NULL) {
        return NULL;
    }

    strncpy(adventurer->name, name, sizeof(adventurer->name) - 1);
    adventurer->name[sizeof(adventurer->name) - 1] = '\0';
    adventurer->profession = profession;
    adventurer->hpMax = hpMax;
    adventurer->hp = hpMax;
    adventurer->damage = damage;
    adventurer->money = money;
    adventurer->level = 1;
    adventurer->xp = xp;
    adventurer->x = x;
    adventurer->y = y;
    return adventurer;
}

Adventurer* createAdventurer() {
    char name[50];
    printLeft("Welcome to the world of adventure!", 1);
    printLeft("What's your name stranger?", 1);
    printRightInput("I... My name is... ", name, sizeof(name), 1);
    while (true){
        printLeft("And what's your profession?\n1. Fighter\n2. Mage\n3. Thief\n4. Bard\n5. Cleric\n", 6);
        int professionChoice;
        printRightInput("I'm a... ", (char*)&professionChoice, sizeof(professionChoice), 1);
        switch (professionChoice) {
            case 49:
                return newAdventurer(name, FIGHTER, 10, 10, 0, 0, 0, 0);
            case 50:
                return newAdventurer(name, MAGE, 70, 7, 0, 50, 0, 0);
            case 51:
                return newAdventurer(name, THIEF, 80, 8, 100, 0, 0, 0);
            case 52:
                return newAdventurer(name, BARD, 90, 6, 0, 0, 0, 0);
            case 53:
                return newAdventurer(name, CLERIC, 110, 9, 0, 0, 0, 0);
            default:
                printLeft("It seems like there is no such profession.", 1);
        }
    }

}
