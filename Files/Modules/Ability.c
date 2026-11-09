//
// Created by User on 17.10.2026.
//

#include "Ability.h"
#define MIN_MONEY_FOR_STEAL 10
#define MAX_MONEY_FOR_STEAL 30
static int smokeTime = 0;
static bool isBlock = false;
static bool isClone = false;

void block() {
    isBlock = true;
}

void smoke() {
    smokeTime = 3;
}

void clone(bool isActive) {
    isClone = false;
}

bool isBlockActive() {
    return isBlock;
}

bool isSmokeActive() {
    if (smokeTime==0) {
        return 0;
    }
    smokeTime--;
    if (getRandom(0, 1)) {
        return 1;
    }
    return 0;
}

bool isCloneActive() {
    return isClone;
}


