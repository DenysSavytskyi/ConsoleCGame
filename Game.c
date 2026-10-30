//
// Created by User on 13.10.2026.
//

#include <time.h>
#include "stdlib.h"
#include "stdio.h"
#include "Files/Controllers/Controller.h"
#include "Files/Modules/State.h"
#include "Files/Controllers/DialogController.h"
#include "Files/Services/BattleService.h"
#include "Files/Services/DialogService.h"
#include "Files/Services/EndService.h"
#include "Files/Services/InventoryService.h"
#include "Files/Services/MapService.h"
#include "Files/Services/ShopService.h"

int main() {
    srand(time(0));
    State currentState = DIALOG_STATE;
    while (currentState != END_STATE) {
        resetAllControllers();
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
            case SHOP_STATE:
                currentState = shopService();
                break;
            default:
                printf("\nUnknown error occurred. Exiting the game.\n");
                currentState = END_STATE;
        }
    }
    endService();
    getchar();
    return 0;
}