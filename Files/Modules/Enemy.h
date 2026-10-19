//
// Created by User on 17.10.2026.
//

#include "Ability.h"
#ifndef JAC_ENEMY_H
#define JAC_ENEMY_H
#pragma once

typedef struct Enemy {
    char name[50];
    int hp;
    int damage;
    Ability ability;
    int x;
    int y;
} Enemy;


#endif //JAC_ENEMY_H
