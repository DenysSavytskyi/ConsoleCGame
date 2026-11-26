#ifndef INVENTORY_SERVICE_H
#define INVENTORY_SERVICE_H
#include "../Modules/State.h"
#include "../Modules/ItemTypes.h"
#include "../Modules/ItemGenerator.h"
#pragma once

#define INVENTORY_SIZE 10

typedef struct Inventory {
    ItemAndType items[INVENTORY_SIZE];
} Inventory;

State inventoryService();
int checkPossibleInputInventory(char *possibleInputs);
void newInventory();
int addItem(ItemAndType itemAndType); /* returns 1 if ok and 0 if no space */
void sellItem(int index);
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
