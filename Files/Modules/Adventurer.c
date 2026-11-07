//
// Created by User on 06.10.2026.
//
#include "stdlib.h"
#include "string.h"
#include "ncurses.h"
#include "Adventurer.h"
#include "Profession.h"
#include "../Controllers/DialogController.h"

static Adventurer *adventurer = NULL;
static int potionTime = 0;
static int lastPotionDamage = 0;

void setPotionTime(int time) {
    potionTime = time;
}

int getPotionTime() {
    return potionTime;
}

void checkPotionTime() {
    if (potionTime > 0) {
        potionTime--;
    } else if (lastPotionDamage > 0) {
    } else if (potionTime == 0) {
        setDamage(getAdventurer()->damage - lastPotionDamage);
        lastPotionDamage = 0;
    }
}

void setHp(int hp) {
    adventurer->hp = hp;
}

void setDamage(int damage) {
    adventurer->damage = damage;
}

void setMoney(int money) {
    adventurer->money = money;
}

void setLevel(int level) {
    adventurer->level = level;
}

void setXp(int xp) {
    adventurer->xp = xp;
    adventurer->level += adventurer->xp/100;
    adventurer->xp %= 100;
}

void setX(int x) {
    adventurer->x = x;
}

void setY(int y) {
    adventurer->y = y;
}


int getAbilityCount() {
    return adventurer->abilityCount;
}

void addAbility(Ability *ability) {
    if (adventurer->abilities == NULL) {
        adventurer->abilities = malloc(sizeof(Ability));
        adventurer->abilityCount = 1;
        adventurer->abilities[0] = *ability;
        return;
    }
    int abilitiesCount = getAbilityCount();
    adventurer->abilityCount = abilitiesCount + 1;
    adventurer->abilities = realloc(adventurer->abilities, sizeof(Ability) * abilitiesCount);
    adventurer->abilities[abilitiesCount - 1] = *ability;
}

Adventurer* getAdventurer() {
    return adventurer;
}

Adventurer* newAdventurer(char *name, Profession profession, Ability ability, int hpMax, int damage, int money, int xp, int x, int y) {
    adventurer = malloc(sizeof(*adventurer));

    strncpy(adventurer->name, name, sizeof(adventurer->name) - 1);
    adventurer->name[sizeof(adventurer->name) - 1] = '\0';
    adventurer->profession = profession;
    newInventory();
    adventurer->abilities = NULL;
    addAbility(&ability);
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
        char professionChoice[4];
        printRightInput("I'm a... ", professionChoice, sizeof(professionChoice), 1);
        switch (professionChoice[0]) {
            case '1':
                return newAdventurer(name, FIGHTER, BLOCK,  100, 10, 0, 0, 0, 0);
            case '2':
                return newAdventurer(name, MAGE, FIREBALL, 70, 7, 0, 50, 0, 0);
            case '3':
                return newAdventurer(name, THIEF, STEAL, 80, 8, 100, 0, 0, 0);
            case '4':
                return newAdventurer(name, BARD, SMOKE_BOMB, 90, 6, 0, 0, 0, 0);
            case '5':
                return newAdventurer(name, CLERIC, CLONE, 110, 9, 0, 0, 0, 0);
            default:
                printLeft("It seems like there is no such profession.", 1);
        }
    }

}
