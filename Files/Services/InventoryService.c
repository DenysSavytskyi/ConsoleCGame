#include "InventoryService.h"
#pragma once

static Inventory* inventory = NULL;
static Weapon weapon;
static Armor helmet;
static Armor chestplate;
static Armor leggings;
static Armor boots;
static ItemAndType* newItemAndType = NULL;

State inventoryService() {
    return END_STATE;
}

void newInventory() {
    inventory = malloc(sizeof(Inventory));
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        inventory->items[i].type = ITEM_NULL;
    }
    weapon.damage = 0;
    helmet.defense = 0;
    chestplate.defense = 0;
    leggings.defense = 0;
    boots.defense = 0;
}

void setNewItemAndType(ItemAndType* itemAndType) {
    newItemAndType = itemAndType;
}

ItemAndType* getNewItemAndType() {
    return newItemAndType;
}

int addItem(ItemAndType* itemAndType) {
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (inventory->items[i].type == ITEM_NULL) {
            inventory->items[i] = *itemAndType;
            return 1;
        }
    }
    if (newItemAndType == NULL || newItemAndType->type == ITEM_NULL) {
        newItemAndType = itemAndType;
        return 1;
    }
    return 0;
}

void dropItem(int index) {
    if (index < 0 || index > INVENTORY_SIZE - 1) {
        return;
    }
    if (getCurrentRoomCell(getAdventurer()->y, getAdventurer()->x) != Empty) {
        return;
    }

    inventory->items[index].type = ITEM_NULL;
}

int getTotalDefense() {
    int totalDefence = 0;
    if (helmet.defense > 0) {
        totalDefence += helmet.defense;
    }
    if (chestplate.defense > 0) {
        totalDefence += chestplate.defense;
    }
    if (leggings.defense > 0) {
        totalDefence += leggings.defense;
    }
    if (boots.defense > 0) {
        totalDefence += boots.defense;
    }
    return totalDefence;
}

void equip(int index) {
    ItemAndType* itemAndType = getItem(index);
    ItemAndType tempItem;
    if (itemAndType->type == WEAPON) {
        if (weapon.damage > 0) {
            tempItem.type = WEAPON;
            tempItem.item.weapon = weapon;
            weapon = itemAndType->item.weapon;
            addItem(&tempItem);
        } else {
            weapon = itemAndType->item.weapon;
        }
    } else if (itemAndType->type == ARMOR) {
        switch (itemAndType->item.armor.part) {
            case HELMET:
                if (helmet.defense > 0) {
                    tempItem.type = ARMOR;
                    tempItem.item.armor = helmet;
                    helmet = itemAndType->item.armor;
                    addItem(&tempItem);
                } else {
                    helmet = itemAndType->item.armor;
                }
                break;
            case CHESTPLATE:
                if (chestplate.defense > 0) {
                    tempItem.type = ARMOR;
                    tempItem.item.armor = chestplate;
                    chestplate = itemAndType->item.armor;
                    addItem(&tempItem);
                } else {
                    chestplate = itemAndType->item.armor;
                }
                break;
            case LEGGINGS:
                if (leggings.defense > 0) {
                    tempItem.type = ARMOR;
                    tempItem.item.armor = leggings;
                    leggings = itemAndType->item.armor;
                    addItem(&tempItem);
                } else {
                    leggings = itemAndType->item.armor;
                }
                break;
            case BOOTS:
                if (boots.defense > 0) {
                    tempItem.type = ARMOR;
                    tempItem.item.armor = boots;
                    boots = itemAndType->item.armor;
                    addItem(&tempItem);
                } else {
                    boots = itemAndType->item.armor;
                }
                break;
        }
    }
}

ItemAndType* getItem(int index) {
    if (index < 0 || index > INVENTORY_SIZE - 1) {
        return NULL;
    }
    return &inventory->items[index];
}

int getItemCount(ItemType type) {
    int count = 0;
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (getItem(i)->type == type) {
            count++;
        }
    }
    return count;
}

Potion* getPotion(int index) {
    int count = 0;
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (getItem(i)->type == POTION) {
            if (index == count) {
                return &getItem(i)->item.potion;
            }
            count++;
        }
    }
    return NULL;
}

void usePotion(const Potion *potion) {
    if (potion == NULL) {
        return;
    }
    switch (potion->type) {
        case HEALTH:
            setHp(getAdventurer()->hp + potion->amount);
            if (getAdventurer()->hp > getAdventurer()->hpMax) {
                setHp(getAdventurer()->hpMax);
            }
            break;
        case STRENGTH:
            setDamage(getAdventurer()->damage + potion->amount);
            setStrengthPotionTime(3);
            break;
        case DEFENCE:
            setDefencePotionTime(3);
            break;
        case EXPERIENCE:
            setXp(getAdventurer()->xp + potion->amount);
            break;
        default:
            break;
    }
}
