#ifndef JAC_ENEMY_H
#define JAC_ENEMY_H
#include <stddef.h>
#include <stdlib.h>
#include "Adventurer.h"
#include "../Services/Service.h"
#include "../Services/MapService.h"
#include <stdbool.h>
#pragma once

typedef enum EnemyType {
    GOBLIN,
    ORC,
    TROLL,
    SKELETON,
    ZOMBIE,
    VAMPIRE,
    WITCH,
    DEMON
} EnemyType;

typedef struct EnemyEntity {
    EnemyType type;
    int hp;
    int maxHp;
    int roomIndex;
    bool isBoss;
} EnemyEntity;

void generateEnemy(int roomIndex, bool isBoss);
int getEnemiesCount();
int getEnemyDamage(int roomIndex);
int attackEnemy(int roomIndex, int damage);
int getEnemyHp(int roomIndex);
int getEnemyMaxHp(int roomIndex);
void freeEnemies();

#endif //JAC_ENEMY_H
