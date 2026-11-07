#include "BattleService.h"

#include "MapService.h"

State battleService() {
    while (getAdventurer()->hp > 0) {
        State state = battle();
        if (state != BATTLE_STATE) {
            return state;
        }
        //TODO if enemy is dead, return MAP_STATE and reward player with money, xp and probably an item
    }
    return END_STATE;
}

State battle() {
    char option = getAndCheckBattleInput();
    if (getBattleState() == OPTIONS) {
        switch (option) {
            case '0':
                //TODO Attack
                return BATTLE_STATE;
            case '1':
                setBattleState(POTIONS);
                //TODO to output potion list
                return BATTLE_STATE;
            case '2':
                setBattleState(ABILITIES);
                //TODO to output ability list
                return BATTLE_STATE;
            case '3':
                //TODO Run Away
                return MAP_STATE;
            default:
                printw("Invalid option. Please try again.\n");
        }
    } else if (getBattleState() == POTIONS) {
        //TODO Handle potion usage
        setBattleState(OPTIONS);
        return BATTLE_STATE;
    } else if (getBattleState() == ABILITIES) {
        //TODO Handle ability usage
        setBattleState(OPTIONS);
        return BATTLE_STATE;
    }
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
