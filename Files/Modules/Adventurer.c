#include "Adventurer.h"
#include "EnemyEntity.h"
#include "../Services/MapService.h"
#include "../Services/InventoryService.h"
#include "../Controllers/DialogController.h"
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

void checkStrengthPotionTime() {
    if (strengthPotionTime > 0) {
        strengthPotionTime--;
    }
    if (strengthPotionTime == 0 && strengthPotionDamage > 0) {
        setDamage(getAdventurer()->damage - strengthPotionDamage);
        strengthPotionDamage = 0;
    }
}

static int checkDefencePotionTime() {
    if (defencePotionTime > 0) {
        defencePotionTime--;
        return defencePotionDefence;
    }
    return 0;
}

void setLastPotionDamage(int damage) {
    strengthPotionDamage = damage;
}

int getLastPotionDamage() {
    return strengthPotionDamage;
}

void setLastPotionDefence(int defence) {
    defencePotionDefence = defence;
}

void setHp(int hp) {
    if (hp<0) {
        adventurer->hp = 0;
        return;
    }
    adventurer->hp = hp>adventurer->hpMax?adventurer->hpMax:hp;
}

void setDamage(int damage) {
    if (damage<0) {
        adventurer->damage = 0;
        return;
    }
    adventurer->damage = damage;
}

void setMoney(int money) {
    adventurer->money = money;
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
    int damageMultiplier = 100 - getTotalDefense() - checkDefencePotionTime();
    if (damageMultiplier < 0 ){
        damageMultiplier = 0;
    }
    if (damageMultiplier > 100) {
        damageMultiplier = 100;
    }
    adventurer->hp-=(int)(getEnemyDamage(getMap()->currentRoom)*(damageMultiplier*1./100));
}

int getAbilityCount() {
    return adventurer->abilityCount;
}

static void addAbility(const Ability *ability) {
    adventurer->abilityCount++;
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
    int moneyReward = getRandom((int)(enemyMaxHp*1./10), (int)(enemyMaxHp*1./5));
    int xpReward = getRandom((int)(enemyMaxHp*1./5), (int)(enemyMaxHp*1./3));
    setMoney(getAdventurer()->money + moneyReward);
    setXp(getAdventurer()->xp + xpReward);
}

Adventurer* getAdventurer() {
    return adventurer;
}

static Adventurer* newAdventurer(char *name, Profession profession, Ability ability, int hpMax, int damage, int money, int xp, int x, int y) {
    adventurer = malloc(sizeof(*adventurer));

    strncpy(adventurer->name, name, sizeof(adventurer->name) - 1);
    adventurer->name[sizeof(adventurer->name) - 1] = '\0';
    adventurer->profession = profession;
    newInventory();
    adventurer->abilities = NULL;
    adventurer->abilityCount = 0;
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
    bool showProfessionError = false;
    while (true){
        if (showProfessionError) {
            resetDialog();
            printLeft("It seems like there is no such profession.", 1);
            showProfessionError = false;
        }
        printLeft("And what's your profession?\n1. Fighter\n2. Mage\n3. Thief\n4. Bard\n5. Cleric\n", 6);
        char professionChoice[4];
        printRightInput("I'm a... ", professionChoice, sizeof(professionChoice), 1);
        switch (professionChoice[0]) {
            case '1':
                return newAdventurer(name, FIGHTER, BLOCK,  100, 10, 0, 0, 0, 0);
            case '2':
                return newAdventurer(name, MAGE, FIREBALL, 70, 7, 0, 50, 0, 0);
            case '3':
                return newAdventurer(name, THIEF, STEAL, 80, 8, 20, 0, 0, 0);
            case '4':
                return newAdventurer(name, BARD, SMOKE_BOMB, 90, 6, 0, 0, 0, 0);
            case '5':
                return newAdventurer(name, CLERIC, CLONE, 110, 9, 0, 0, 0, 0);
            default:
                showProfessionError = true;
        }
    }

}
