//
// Created by User on 17.10.2026.
//

#include "InventoryService.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Modules/Adventurer.h"
#include "../Controllers/Controller.h"

State inventoryService() {
    Adventurer *adventurer = getAdventurer();
    if (!adventurer) return DIALOG_STATE;
    clearConsole();
    printInventory(adventurer->inventory);
    printf("1. Use health potion\n2. Back\n");
    int choice = readNumber("> ", 1, 2);
    if (choice == 1) {
        if (useHealthPotion(adventurer->inventory, &adventurer->hp, adventurer->hpMax))
            printf("You feel better. HP: %d/%d\n", adventurer->hp, adventurer->hpMax);
        else
            printf("You do not have a health potion.\n");
        waitForEnter();
    }
    return MAP_STATE;
}

Inventory *createInventory() {
    Inventory *inventory = calloc(1, sizeof(Inventory));
    if (inventory) addPotion(inventory, "Small healing potion", HEALTH, 25);
    return inventory;
}

static int addItem(Inventory *inventory, ItemType type) {
    if (!inventory || inventory->itemCount >= 10) return -1;
    int index = inventory->itemCount++;
    inventory->types[index] = type;
    return index;
}

void addPotion(Inventory *inventory, const char *name, PotionType type, int amount) {
    int index = addItem(inventory, POTION_ITEM);
    if (index < 0) return;
    strncpy(inventory->items[index].potion.name, name, 49);
    inventory->items[index].potion.type = type;
    inventory->items[index].potion.amount = amount;
}

void addWeapon(Inventory *inventory, const char *name, int damage) {
    int index = addItem(inventory, WEAPON_ITEM);
    if (index < 0) return;
    strncpy(inventory->items[index].weapon.name, name, 49);
    inventory->items[index].weapon.damage = damage;
}

void addArmor(Inventory *inventory, const char *name, int defense) {
    int index = addItem(inventory, ARMOR_ITEM);
    if (index < 0) return;
    strncpy(inventory->items[index].armor.name, name, 49);
    inventory->items[index].armor.defense = defense;
}

int useHealthPotion(Inventory *inventory, int *hp, int hpMax) {
    if (!inventory) return 0;
    for (int i = 0; i < inventory->itemCount; i++) {
        if (inventory->types[i] == POTION_ITEM &&
            inventory->items[i].potion.type == HEALTH) {
            *hp += inventory->items[i].potion.amount;
            if (*hp > hpMax) *hp = hpMax;
            for (int j = i; j < inventory->itemCount - 1; j++) {
                inventory->items[j] = inventory->items[j + 1];
                inventory->types[j] = inventory->types[j + 1];
            }
            inventory->itemCount--;
            return 1;
        }
    }
    return 0;
}

void printInventory(const Inventory *inventory) {
    printf("+---------------------- INVENTORY ----------------------+\n");
    if (!inventory || inventory->itemCount == 0) {
        printf("| Your backpack is empty.                                |\n");
    } else {
        for (int i = 0; i < inventory->itemCount; i++) {
            if (inventory->types[i] == POTION_ITEM)
                printf("| %-25s potion +%d HP              |\n",
                       inventory->items[i].potion.name, inventory->items[i].potion.amount);
            else if (inventory->types[i] == WEAPON_ITEM)
                printf("| %-25s weapon +%d damage          |\n",
                       inventory->items[i].weapon.name, inventory->items[i].weapon.damage);
            else if (inventory->types[i] == ARMOR_ITEM)
                printf("| %-25s armor +%d defense           |\n",
                       inventory->items[i].armor.name, inventory->items[i].armor.defense);
        }
    }
    printf("+--------------------------------------------------------+\n");
}
