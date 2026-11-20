#ifndef JAC_ABILITY_H
#define JAC_ABILITY_H
#include "../Services/Service.h"
#include <stdbool.h>
#pragma once

typedef enum Ability {
    BLOCK,
    FIREBALL,
    STEAL,
    SMOKE_BOMB,
    CLONE
} Ability;

void block();
int fireball();
void steal();
void smoke();
void clone(bool isActive);
bool isBlockActive();
bool isSmokeActive();
bool isCloneActive();

#endif //JAC_ABILITY_H
