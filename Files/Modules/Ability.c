#include "Ability.h"
#include "Adventurer.h"

#define MIN_MONEY_FOR_STEAL 10
#define MAX_MONEY_FOR_STEAL 30
static int smokeTime = 0;
static bool isBlock = false;
static bool isClone = false;

void block() {
    isBlock = true;
}

int fireball() {
    return getRandom((getAdventurer()->damage-5 < 0)?0:getAdventurer()->damage-5, getAdventurer()->damage+5);
}

void steal() {
    getAdventurer()->money += getRandom(MIN_MONEY_FOR_STEAL, MAX_MONEY_FOR_STEAL);
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

