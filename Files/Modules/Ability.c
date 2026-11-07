//
// Created by User on 17.10.2026.
//

#include "Ability.h"
#define MIN_MONEY_FOR_STEAL 10
#define MAX_MONEY_FOR_STEAL 30
static int smokeTime = 0;
static bool isBlock = false;

bool isSmokeActive() {
    if (smokeTime==0) {
        return 1;
    }
    smokeTime--;
    if (getRandom(0, 1)) {
        return 0;
    }
    return 1;
}

bool isBlockActive() {
    return isBlock;
}

void smoke() {
    smokeTime = 3;
}

void block() {
    isBlock = true;
}

