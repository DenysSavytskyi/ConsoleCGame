#include "ShopService.h"
#include <stdio.h>
#include "../Controllers/Controller.h"
#include "../Modules/Adventurer.h"
#include "InventoryService.h"

State shopService() {
    Adventurer *player = getAdventurer();
    if (!player) return DIALOG_STATE;
    while (1) {
        clearConsole();
        printf("+----------------------- SHOP -------------------------+\n");
        printf("Gold: %d\n", player->money);
        printf("1. Healing potion (+25 HP) - 25 gold\n");
        printf("2. Iron sword (+4 damage) - 100 gold\n");
        printf("3. Leather armor (+3 defense) - 80 gold\n");
        printf("4. Leave shop\n");
        int choice = readNumber("> ", 1, 4);
        if (choice == 4) return MAP_STATE;
        int price = choice == 1 ? 25 : (choice == 2 ? 100 : 80);
        if (player->money < price) {
            printf("Not enough gold.\n");
        } else {
            player->money -= price;
            if (choice == 1) addPotion(player->inventory, "Healing potion", HEALTH, 25);
            if (choice == 2) {
                addWeapon(player->inventory, "Iron sword", 4);
                player->damage += 4;
            }
            if (choice == 3) addArmor(player->inventory, "Leather armor", 3);
            printf("Purchase complete.\n");
        }
        waitForEnter();
    }
}
