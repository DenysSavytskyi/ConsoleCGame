#ifndef INVENTORY_SERVICE_H
#define INVENTORY_SERVICE_H
#pragma once
#include "../Modules/Adventurer.h"
#include <stddef.h>
#include "../Modules/State.h"
#define INVENTORY_SIZE 10

typedef enum ItemType {
    POTION,
    WEAPON,
    ARMOR,
    QUEST_ITEM,
    ITEM_NULL
} ItemType;

typedef enum PotionType {
    HEALTH,
    STRENGTH,
    EXPERIENCE,
} PotionType;

typedef struct Potion {
    char name[50];
    PotionType type;
    int amount;
} Potion;

typedef struct Weapon {
    char name[50];
    int damage;
} Weapon;

typedef struct Armor {
    char name[50];
    int defense;
} Armor;

typedef struct QuestItem {
    char name[50];
} QuestItem;

typedef union Item {
    Potion potion;
    Weapon weapon;
    Armor armor;
    QuestItem questItem;
} Item;

typedef struct ItemAndType {
    Item item;
    ItemType type;
} ItemAndType;

typedef struct Inventory {
    ItemAndType items[INVENTORY_SIZE];
} Inventory;

State inventoryService();
void newInventory();
void setNewItemAndType(ItemAndType *itemAndType);
ItemAndType* getNewItemAndType();
int addItem(ItemAndType *itemAndType); /* returns 1 if ok and 0 if no space */
ItemAndType* getItem(int index);
int getItemCount(ItemType type);
Potion* getPotion(int index);
void usePotion(Potion *potion);

#endif
