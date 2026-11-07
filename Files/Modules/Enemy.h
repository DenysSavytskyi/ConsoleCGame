//
// Created by User on 17.10.2026.
//

#ifndef JAC_ENEMY_H
#define JAC_ENEMY_H
#include <stdbool.h>
#include "Ability.h"
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

typedef struct Enemy {
    EnemyType type;
    int hp;
    int roomIndex;
} Enemy;


#endif //JAC_ENEMY_H
