//
// Created by User on 06.10.2026.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdbool.h>
#include "Adventurer.h"
#include "Profession.h"
#include "../Controllers/DialogController.h"
#include "../Controllers/Controller.h"

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
    adventurer->inventory = createInventory();
    initializeQuests(adventurer->quests);
    return adventurer;
}

Adventurer* createAdventurer() {
    char name[50];
    printLeft("Welcome to the world of adventure!", 1);
    printLeft("What's your name stranger?", 1);
    readInput("I... My name is... ", name, sizeof(name));
    while (true){
        printLeft("And what's your profession?\n1. Fighter\n2. Mage\n3. Thief\n4. Bard\n5. Cleric\n", 6);
        int professionChoice = readNumber("I'm a... ", 1, 5);
        switch (professionChoice) {
            case 1:
                return newAdventurer(name, FIGHTER, 10, 10, 0, 0, 1, 1);
            case 2:
                return newAdventurer(name, MAGE, 70, 7, 0, 50, 1, 1);
            case 3:
                return newAdventurer(name, THIEF, 80, 8, 100, 0, 1, 1);
            case 4:
                return newAdventurer(name, BARD, 90, 6, 0, 0, 1, 1);
            case 5:
                return newAdventurer(name, CLERIC, 110, 9, 0, 0, 1, 1);
            default:
                printLeft("It seems like there is no such profession.", 1);
        }

    }
}

void resetAdventurer() {
    if (adventurer) {
        free(adventurer->inventory);
        free(adventurer);
        adventurer = NULL;
    }
}

void addExperience(Adventurer *player, int amount) {
    if (!player) return;
    player->xp += amount;
    while (player->xp >= player->level * 100) {
        player->xp -= player->level * 100;
        player->level++;
        player->hpMax += 10;
        player->damage += 2;
        player->hp = player->hpMax;
        printf("Level up! You are now level %d.\n", player->level);
    }
}
