#ifndef INVENTORY_SERVICE_H
#define INVENTORY_SERVICE_H
#include "../Modules/State.h"
#include "../Modules/Adventurer.h"
#include <ncurses.h>
#include "MapService.h"
#pragma once

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
    DEFENCE,
    EXPERIENCE,
} PotionType;

typedef enum ArmorPart {
    HELMET,
    CHESTPLATE,
    LEGGINGS,
    BOOTS,
} ArmorPart;

typedef struct Potion {
    PotionType type;
    int amount;
} Potion;

typedef struct Weapon {
    int damage;
} Weapon;

typedef struct Armor {
    ArmorPart part;
    int defense;
} Armor;

typedef struct QuestItem {
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
void dropItem(int index);
int getTotalDefense();
void equip(int index);
ItemAndType* getItem(int index);
int getItemCount(ItemType type);
Potion* getPotion(int index);
void usePotion(const Potion *potion);

#endif
