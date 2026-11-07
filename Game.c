//
// Created by User on 13.10.2026.
//

#include <ncurses.h>
#include <time.h>
#include "stdlib.h"
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
    sleep_ms(1000);
    initializeController();
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
                printw("Unknown error occurred. Exiting the game.\n");
                refresh();
                currentState = END_STATE;
        }
    }
    endService();
    endwin();
    return 0;
}