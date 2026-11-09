//
// Created by User on 17.10.2026.
//

#ifndef JAC_ENEMY_H
#define JAC_ENEMY_H
#include <stdbool.h>
#include "Ability.h"
#include "../Services/MapService.h"
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
