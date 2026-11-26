//
// Created by User on 06.10.2026.
//

#ifndef JAC_ADVENTURER_H
#define JAC_ADVENTURER_H
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Profession.h"
#include "Ability.h"
#pragma once

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

void setStrengthPotionTime(int time);
void setDefencePotionTime(int time);
void checkStrengthPotionTime();
void setLastPotionDamage(int damage);
int getLastPotionDamage();
void setLastPotionDefence(int defence);
void setHp(int hp);
void setDamage(int damage);
void setMoney(int money);
void setXp(int xp);
void setX(int x);
void setY(int y);
void attackAdventurer();
int getAbilityCount();
int useAbility(int index);
void getRewards(int enemyMaxHp);

Adventurer* getAdventurer();
Adventurer* createAdventurer();

#endif
