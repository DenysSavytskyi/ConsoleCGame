//
// Created by User on 17.10.2026.
//

#ifndef INVENTORY_SERVICE_H
#define INVENTORY_SERVICE_H
#pragma once

#include "../State.h"
typedef enum PotionType {
    HEALTH,
    STRENGTH,
    EXPERIENCE,
} PotionType;

typedef enum ItemType {
    POTION_ITEM,
    WEAPON_ITEM,
    ARMOR_ITEM,
    QUEST_ITEM
} ItemType;

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

typedef struct InventoryService {
    Item items[10];
    ItemType types[10];
    int itemCount;
} Inventory;

State inventoryService();
Inventory *createInventory();
void addPotion(Inventory *inventory, const char *name, PotionType type, int amount);
void addWeapon(Inventory *inventory, const char *name, int damage);
void addArmor(Inventory *inventory, const char *name, int defense);
int useHealthPotion(Inventory *inventory, int *hp, int hpMax);
void printInventory(const Inventory *inventory);

#endif
