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

int main() {
    State currentState = DIALOG_STATE;
    while (currentState != END_STATE) {
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
            case SAVE_LOAD_STATE:
                currentState = saveLoadService();
                break;
            case SHOP_STATE:
                currentState = shopService();
                break;
            default:
                printf("Unknown error occurred. Exiting the game.\n");
                currentState = END_STATE;
        }
    }
    endService();
    getchar();
    return 0;
}