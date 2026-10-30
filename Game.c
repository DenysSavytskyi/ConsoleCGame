//
// Created by User on 13.10.2026.
//
#include "stdlib.h"
#include "stdio.h"
#include "Files/State.h"
#include "Files/Controllers/DialogController.h"
#include "Files/Services/BattleService.h"
#include "Files/Services/DialogService.h"
#include "Files/Services/EndService.h"
#include "Files/Services/InventoryService.h"
#include "Files/Services/MapService.h"
#include "Files/Services/SaveLoadService.h"
#include "Files/Services/ShopService.h"
#include "Files/Services/QuestService.h"

int main() {
    State currentState = DIALOG_STATE;
    while (1) {
        switch (currentState) {
            case BATTLE_STATE:
                currentState = battleService();
                break;
            case DIALOG_STATE:
                currentState = dialogService();
                break;
            case INVENTORY_STATE:
                currentState = inventoryService();
                break;
            case MAP_STATE:
                currentState = mapService();
                break;
            case QUEST_STATE:
                currentState = questService();
                break;
            case SAVE_LOAD_STATE:
                currentState = saveLoadService();
                break;
            case SHOP_STATE:
                currentState = shopService();
                break;
            default:
                printf("Unknown error occurred. Exiting the game.\n");
                return 1;
        }
        if (currentState == END_STATE) {
            currentState = endService();
            if (currentState == END_STATE) break;
        }
    }
    return 0;
}