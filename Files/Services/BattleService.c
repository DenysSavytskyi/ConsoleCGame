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
    int totalDamage = getAdventurer()->damage + getWeaponDamage();
    if (isCloneActive()) {
        return (int)(totalDamage * 1.5);
    }
    return totalDamage;
}

State battle() {
    char option = getAndCheckBattleInput();
    if (getBattleState() == OPTIONS) {
        switch (option) {
            case '1':
                int result = attackEnemy(getMap()->currentRoom, calculateDamage());
                if (result == -1) {
                    return END_STATE;
                }
                if (result) {
                    return MAP_STATE;
                }
                checkStrengthPotionTime();
                break;
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
    } else if (getBattleState() == ABILITIES) {
        int result = useAbility(option - '1');
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
    if (getBattleState() == ABILITIES) {
        for (int i = 0; i<getAbilityCount(); i++) {
            possibleInputs[count++] = (char)((int)'1' + i);
        }
    } else {
        possibleInputs[count++] = '1';
        possibleInputs[count++] = '2';
        possibleInputs[count++] = '3';
    }
    possibleInputs[count++] = 'i';
    return count;
}
