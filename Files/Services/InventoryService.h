#ifndef INVENTORY_SERVICE_H
#define INVENTORY_SERVICE_H
#include "../Modules/State.h"
#include "../Modules/ItemTypes.h"
#include <ncurses.h>
#pragma once

#define INVENTORY_SIZE 10

typedef struct Inventory {
    ItemAndType items[INVENTORY_SIZE];
} Inventory;

State inventoryService();
void newInventory();
void setNewItemAndType(ItemAndType *itemAndType);
ItemAndType* getNewItemAndType();
int addItem(ItemAndType *itemAndType); /* returns 1 if ok and 0 if no space */
void dropItem(int index);
int getTotalDefense();
void equip(int index);
ItemAndType* getItem(int index);
int getItemCount(ItemType type);
Potion* getPotion(int index);
void usePotion(const Potion *potion);

#endif
