#ifndef JAC_ENEMY_H
#define JAC_ENEMY_H
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Services/Service.h"
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
int getEnemyDamage(int roomIndex);
int attackEnemy(int roomIndex, int damage);
int getEnemyHp(int roomIndex);
int getEnemyMaxHp(int roomIndex);
void freeEnemies();

#endif //JAC_ENEMY_H
