#include "BattleService.h"

#include "MapService.h"

State battleService() {
    while (getAdventurer()->hp > 0) {
        State state = battle();
        if (state != BATTLE_STATE) {
            return state;
        }
    }
    return END_STATE;
}

int calculateDamage() {
    if (isCloneActive()) {
        return getAdventurer()->damage * 1.5;
    }
    return getAdventurer()->damage;
}

State battle() {
    char option = getAndCheckBattleInput();
    checkPotionTime();
    if (getBattleState() == OPTIONS) {
        switch (option) {
            case '0':
                int result = attackEnemy(getMap()->currentRoom, calculateDamage());
                if (result == -1) {
                    printw("Unknown error occurred.\n");
                    return END_STATE;
                }
                if (result == 1) {
                    return MAP_STATE;
                }
                break;
            case '1':
                setBattleState(POTIONS);
                //TODO to output potion list
                return BATTLE_STATE;
            case '2':
                setBattleState(ABILITIES);
                return BATTLE_STATE;
            case '3':
                return MAP_STATE;
            default:
                return BATTLE_STATE;
        }
    } else if (getBattleState() == POTIONS) {
        //TODO Handle potion usage     usePotion(getPotion(option - '0'));
        setBattleState(OPTIONS);
    } else if (getBattleState() == ABILITIES) {
        //TODO Handle ability usage    useAbility(option - '0');
        setBattleState(OPTIONS);
    }
    attackAdventurer();
    return BATTLE_STATE;
}

int checkPossibleMovesBattle(char *possibleInputs) {
    int count = 0;
    if (getBattleState() == POTIONS) {
        for (int i = 0; i<getItemCount(POTION); i++) {
            possibleInputs[count++] = (char)((int)'0'+ i);
        }
    } else if (getBattleState() == ABILITIES) {
        for (int i = 0; i<getAbilityCount(); i++) {
            possibleInputs[count++] = (char)((int)'0' + i);
        }
    } else {
        possibleInputs[count++] = '0';
        if (getItemCount(POTION) > 1) {
            possibleInputs[count++] = '1';
        }
        possibleInputs[count++] = '2';
        possibleInputs[count++] = '3';
    }
    possibleInputs[count++] = 'i';
    return count;
}
