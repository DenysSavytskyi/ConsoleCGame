//
// Created by User on 06.10.2026.
//

#ifndef JAC_ADVENTURER_H
#define JAC_ADVENTURER_H
#pragma once
#include "../Services/InventoryService.h"
#include "Profession.h"
#include <stdbool.h>
#include "Ability.h"

typedef struct Adventurer {
    char name[50];
    Profession profession;
    Ability *abilities;
    int abilityCount;
    int hpMax;
    int hp;
    int damage;
    int money;
    int level;
    int xp;
    int x;
    int y;
} Adventurer;

void setPotionTime(int time);
int getPotionTime();
void checkPotionTime();
void setHp(int hp);
void setDamage(int damage);
void setMoney(int money);
void setLevel(int level);
void setXp(int xp);
void setX(int x);
void setY(int y);
int getAbilityCount();
void addAbility(Ability *ability);

Adventurer* newAdventurer(char *name, Profession profession, Ability ability, int hpMax, int damage, int money, int xp, int x, int y);
Adventurer* getAdventurer();
Adventurer* createAdventurer();

#endif
