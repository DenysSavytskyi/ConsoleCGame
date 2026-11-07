//
// Created by User on 17.10.2026.
//
#include "InventoryService.h"

static Inventory* inventory = NULL;

State inventoryService() {
    return END_STATE;
}

void newInventory() {
    inventory = malloc(sizeof(Inventory));
    for (int i=0; i<INVENTORY_SIZE; i++) {
        inventory->items[i].type = ITEM_NULL;
    }
}

ItemAndType* getItem(int index) {
    if (index < 0 || index > INVENTORY_SIZE) {
        return NULL;
    }
    return &inventory->items[index];
}

int getItemCount(ItemType type) {
    int count = 0;
    for (int i=0; i<INVENTORY_SIZE; i++) {
        if (getItem(i)->type == type) {
            count++;
        }
    }
    return count;
}

Potion* getPotion(int index) {
    int count = 0;
    for (int i=0; i<INVENTORY_SIZE; i++) {
        if (getItem(i)->type == POTION) {
            if (index == count) {
                return &getItem(i)->item.potion;
            }
            count++;
        }
    }
    return NULL;
}

void usePotion(Potion *potion) {
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
            setPotionTime(3);
            break;
        case EXPERIENCE:
            setXp(getAdventurer()->xp + potion->amount);
            break;
        default:
            break;
    }
}
