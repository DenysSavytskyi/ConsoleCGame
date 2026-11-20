#include "Adventurer.h"
#include "EnemyEntity.h"
#include "../Services/MapService.h"
#include "../Services/InventoryService.h"
#include "../Controllers/DialogController.h"
#pragma once

static Adventurer *adventurer = NULL;
static int strengthPotionTime = 0;
static int defencePotionTime = 0;
static int strengthPotionDamage = 0;
static int defencePotionDefence = 0;

void setStrengthPotionTime(int time) {
    strengthPotionTime = time;
}

void setDefencePotionTime(int time) {
    defencePotionTime = time;
}

int getStrengthPotionTime() {
    return strengthPotionTime;
}

int getDefencePotionTime() {
    return defencePotionTime;
}

void checkStrengthPotionTime() {
    if (strengthPotionTime > 0) {
        strengthPotionTime--;
    } else if (strengthPotionDamage > 0) {
    } else if (strengthPotionTime == 0) {
        setDamage(getAdventurer()->damage - strengthPotionDamage);
        strengthPotionDamage = 0;
    }
}

int checkDefencePotionTime() {
    if (defencePotionTime > 0) {
        defencePotionTime--;
        return defencePotionDefence;
    }
    if (defencePotionDefence > 0) {
    } else if (defencePotionTime == 0) {
        defencePotionDefence = 0;
    }
    return 0;
}

void setLastPotionDamage(int damage) {
    strengthPotionDamage = damage;
}

void setHp(int hp) {
    adventurer->hp = hp;
}

void setDamage(int damage) {
    adventurer->damage = damage;
}

void setMoney(int money) {
    adventurer->money = money;
}

void setLevel(int level) {
    adventurer->level = level;
}

void setXp(int xp) {
    adventurer->xp = xp;
    adventurer->level += adventurer->xp/100;
    adventurer->hpMax += adventurer->xp/100*5;
    adventurer->hp += adventurer->xp/100*5;
    adventurer->xp %= 100;
}

void setX(int x) {
    adventurer->x = x;
}

void setY(int y) {
    adventurer->y = y;
}

void attackAdventurer() {
    if (isCloneActive()) {
        if (getRandom(0, 1)) {
            clone(false);
            return;
        }
    }
    if (isSmokeActive()) {
        return;
    }
    if (isBlockActive()) {
        return;
    }
    adventurer->hp-=(int)(getEnemyDamage(getMap()->currentRoom)*((getTotalDefense() + checkDefencePotionTime())*1./100));
}

int getAbilityCount() {
    return adventurer->abilityCount;
}

void addAbility(const Ability *ability) {
    if (adventurer->abilities == NULL) {
        adventurer->abilities = malloc(sizeof(Ability));
        adventurer->abilityCount = 1;
        adventurer->abilities[0] = *ability;
        return;
    }
    int abilitiesCount = getAbilityCount();
    adventurer->abilityCount = abilitiesCount + 1;
    adventurer->abilities = realloc(adventurer->abilities, sizeof(Ability) * adventurer->abilityCount);
    adventurer->abilities[adventurer->abilityCount - 1] = *ability;
}

// returns 0 if the ability was used successfully, -1 if error occurred or >0 if its damage
int useAbility(int index) {
    if (index < 0 || index >= getAbilityCount()) {
        return -1;
    }
    Ability ability = adventurer->abilities[index];
    switch (ability) {
        case FIREBALL:
            return fireball();
        case STEAL:
            steal();
            return 0;
        case SMOKE_BOMB:
            smoke();
            return 0;
        case CLONE:
            clone(true);
            return 0;
        case BLOCK:
            block();
            return 0;
        default:
            return -1;
    }
}

void getRewards(int enemyMaxHp) {
    int moneyReward = getRandom(enemyMaxHp-10, enemyMaxHp);
    int xpReward = getRandom(enemyMaxHp-10, enemyMaxHp);
    setMoney(getAdventurer()->money + moneyReward);
    setXp(getAdventurer()->xp + xpReward);
}

Adventurer* getAdventurer() {
    return adventurer;
}

Adventurer* newAdventurer(char *name, Profession profession, Ability ability, int hpMax, int damage, int money, int xp, int x, int y) {
    adventurer = malloc(sizeof(*adventurer));

    strncpy(adventurer->name, name, sizeof(adventurer->name) - 1);
    adventurer->name[sizeof(adventurer->name) - 1] = '\0';
    adventurer->profession = profession;
    newInventory();
    adventurer->abilities = NULL;
    addAbility(&ability);
    adventurer->hpMax = hpMax;
    adventurer->hp = hpMax;
    adventurer->damage = damage;
    adventurer->money = money;
    adventurer->level = 1;
    adventurer->xp = xp;
    adventurer->x = x;
    adventurer->y = y;
    return adventurer;
}

Adventurer* createAdventurer() {
    char name[50];
    printLeft("Welcome to the world of adventure!", 1);
    printLeft("What's your name stranger?", 1);
    printRightInput("I... My name is... ", name, sizeof(name), 1);
    while (true){
        printLeft("And what's your profession?\n1. Fighter\n2. Mage\n3. Thief\n4. Bard\n5. Cleric\n", 6);
        char professionChoice[4];
        printRightInput("I'm a... ", professionChoice, sizeof(professionChoice), 1);
        switch (professionChoice[0]) {
            case '1':
                return newAdventurer(name, FIGHTER, BLOCK,  100, 10, 0, 0, 0, 0);
            case '2':
                return newAdventurer(name, MAGE, FIREBALL, 70, 7, 0, 50, 0, 0);
            case '3':
                return newAdventurer(name, THIEF, STEAL, 80, 8, 100, 0, 0, 0);
            case '4':
                return newAdventurer(name, BARD, SMOKE_BOMB, 90, 6, 0, 0, 0, 0);
            case '5':
                return newAdventurer(name, CLERIC, CLONE, 110, 9, 0, 0, 0, 0);
            default:
                printLeft("It seems like there is no such profession.", 1);
        }
    }

}
