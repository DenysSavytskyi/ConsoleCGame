//
// Created by User on 06.10.2026.
//

#include "../Services/InventoryService.h"
#include "Profession.h"

#ifndef JAC_ADVENTURER_H
#define JAC_ADVENTURER_H
#pragma once

typedef struct Adventurer {
    char name[50];
    Profession profession;
    Inventory *inventory;
    int hpMax;
    int hp;
    int damage;
    int money;
    int level;
    int xp;
    int x;
    int y;
} Adventurer;

Adventurer* newAdventurer(char *name, Profession profession, int hpMax, int damage, int money, int xp, int x, int y);
Adventurer* getAdventurer();
void printStats(Adventurer *adventurer);
Adventurer* createAdventurer();

#endif //JAC_ADVENTURER_H
