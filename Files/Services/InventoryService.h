#ifndef INVENTORY_SERVICE_H
#define INVENTORY_SERVICE_H
#include "../Modules/State.h"
#include "../Modules/ItemTypes.h"
#pragma once

#define INVENTORY_SIZE 10

typedef struct Inventory {
    ItemAndType items[INVENTORY_SIZE];
} Inventory;

State inventoryService();
int checkPossibleMovesInventory(char *possibleInputs);
void newInventory();
int addItem(ItemAndType itemAndType); /* returns 1 if ok and 0 if no space */
void dropItem(int index);
int getTotalDefense();
int getWeaponDamage();
void equip(int index);
ItemAndType* getItem(int index);
void deleteItem(int index);
int getItemCount(ItemType type);
Potion* getPotion(int index);
void usePotion(int index);

#endif
