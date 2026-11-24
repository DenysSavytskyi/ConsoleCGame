#include "BattleService.h"
#include "../Modules/Adventurer.h"
#include "../Modules/EnemyEntity.h"
#include "MapService.h"
#include "../Controllers/EndController.h"
#include "../Controllers/BattleController.h"
#include "InventoryService.h"

State battleService() {
    while (getAdventurer()->hp > 0) {
        State state = battle();
        if (state != BATTLE_STATE) {
            return state;
        }
    }
    setEndState(GAME_OVER);
    return END_STATE;
}

static int calculateDamage() {
    if (isCloneActive()) {
        return (int)(getAdventurer()->damage * 1.5);
    }
    return getAdventurer()->damage;
}

State battle() {
    char option = getAndCheckBattleInput();
    if (getBattleState() == OPTIONS) {
        switch (option) {
            case '0':
                int result = attackEnemy(getMap()->currentRoom, calculateDamage());
                if (result == -1) {
                    return END_STATE;
                }
                if (result) {
                    return MAP_STATE;
                }
                checkStrengthPotionTime();
                break;
            case '1':
                setBattleState(POTIONS);
                return BATTLE_STATE;
            case '2':
                setBattleState(ABILITIES);
                return BATTLE_STATE;
            case '3':
                return MAP_STATE;
            case 'i':
                return INVENTORY_STATE;
            default:
                return BATTLE_STATE;
        }
    } else if (getBattleState() == POTIONS) {
        usePotion(option - '0');
        checkStrengthPotionTime();
        setBattleState(OPTIONS);
    } else if (getBattleState() == ABILITIES) {
        int result = useAbility(option - '0');
        if (result == -1) {
            return END_STATE;
        }
        if (result > 0) {
            result = attackEnemy(getMap()->currentRoom, result);
            if (result == -1) {
                return END_STATE;
            }
            if (result) {
                return MAP_STATE;
            }
        }
        checkStrengthPotionTime();
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
        if (getItemCount(POTION) > 0) {
            possibleInputs[count++] = '1';
        }
        possibleInputs[count++] = '2';
        possibleInputs[count++] = '3';
    }
    possibleInputs[count++] = 'i';
    return count;
}
