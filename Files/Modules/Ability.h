//
// Created by User on 17.10.2026.
//

#ifndef JAC_ABILITY_H
#define JAC_ABILITY_H
#pragma once

#include "../Services/Service.h"

typedef enum Ability {
    BLOCK,
    FIREBALL,
    STEAL,
    SMOKE_BOMB,
    CLONE
} Ability;


void block();
void fireball();
void steal();
void smoke();
void clone(bool isActive);
bool isBlockActive();
bool isSmokeActive();
bool isCloneActive();




#endif //JAC_ABILITY_H
