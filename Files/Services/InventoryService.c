#include "InventoryService.h"
#include "../Modules/Adventurer.h"
#include "MapService.h"
#include "../Controllers/InventoryController.h"
static Inventory* inventory = NULL;
static Weapon weapon;
static Armor helmet;
static Armor chestplate;
static Armor leggings;
static Armor boots;

static void dropItem(int index);
static void deleteItem(int index);
static void usePotion(int index);

State inventoryService() {
    char input = getAndCheckInventoryInput();
    while (input != 'x') {
        switch (input) {
            case 'w':
                setCurrentIndex(getCurrentIndex() - 5);
                break;
            case 'a':
                setCurrentIndex(getCurrentIndex() - 1);
                break;
            case 's':
                setCurrentIndex(getCurrentIndex() + 5);
                break;
            case 'd':
                setCurrentIndex(getCurrentIndex() + 1);
                break;
            case 'e':
                if (getItem(getCurrentIndex())->type == POTION)
                    usePotion(getCurrentIndex());
                else
                    equip(getCurrentIndex());
                break;
            case 'q':
                dropItem(getCurrentIndex());
                break;
        }
        input = getAndCheckInventoryInput();
    }
    return getPreviousState();
}

int checkPossibleInputInventory(char *possibleInputs) {
    int count = 0;
    if (getCurrentIndex()>=5) {
        possibleInputs[count++] = 'w';
    }
    if (getCurrentIndex()%5!=0) {
        possibleInputs[count++] = 'a';
    }
    if (getCurrentIndex()<5) {
        possibleInputs[count++] = 's';
    }
    if (getCurrentIndex()%5!=4) {
        possibleInputs[count++] = 'd';
    }
    if (getItem(getCurrentIndex())->type != ITEM_NULL &&
        getItem(getCurrentIndex())->type != QUEST_ITEM) {
        possibleInputs[count++] = 'e';
    }
    possibleInputs[count++] = 'x';
    if (getCurrentRoomCell(getAdventurer()->y, getAdventurer()->x) == Empty &&
        getItem(getCurrentIndex())->type != ITEM_NULL) {
        possibleInputs[count++] = 'q';
    }
    return count;
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

int addItem(ItemAndType itemAndType) {
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (inventory->items[i].type == ITEM_NULL) {
            inventory->items[i] = itemAndType;
            return 1;
        }
    }
    return 0;
}

void sellItem(int index) {
    if (index < 0 || index > INVENTORY_SIZE - 1) {
        return;
    }
    ItemAndType* item = getItem(index);
    if (item == NULL || item->type == ITEM_NULL || item->type == QUEST_ITEM) {
        return;
    }
    getAdventurer()->money += getItemPrice(item);
    deleteItem(index);
}

static void dropItem(int index) {
    if (index < 0 || index > INVENTORY_SIZE - 1) {
        return;
    }
    if (getCurrentRoomCell(getAdventurer()->y, getAdventurer()->x) != Empty) {
        return;
    }
    addItemOnMap(inventory->items[index], getMap()->currentRoom, getAdventurer()->y, getAdventurer()->x);
    inventory->items[index].type = ITEM_NULL;
}

static void equipArmor(Armor *equipped, ItemAndType *item, int index) {
    if (equipped->defense > 0) {
        ItemAndType oldItem;
        oldItem.type = ARMOR;
        oldItem.item.armor = *equipped;
        *equipped = item->item.armor;
        *item = oldItem;
    } else {
        *equipped = item->item.armor;
        deleteItem(index);
    }
}

int getTotalDefense() {
    return helmet.defense + chestplate.defense + leggings.defense + boots.defense;
}

int getWeaponDamage() {
    return weapon.damage;
}

void equip(int index) {
    ItemAndType* itemAndType = getItem(index);
    if (itemAndType->type == WEAPON) {
        if (weapon.damage > 0) {
            ItemAndType oldItem;
            oldItem.type = WEAPON;
            oldItem.item.weapon = weapon;
            weapon = itemAndType->item.weapon;
            *itemAndType = oldItem;
        } else {
            weapon = itemAndType->item.weapon;
            deleteItem(index);
        }
    } else if (itemAndType->type == ARMOR) {
        switch (itemAndType->item.armor.part) {
            case HELMET:
                equipArmor(&helmet, itemAndType, index);
                break;
            case CHESTPLATE:
                equipArmor(&chestplate, itemAndType, index);
                break;
            case LEGGINGS:
                equipArmor(&leggings, itemAndType, index);
                break;
            case BOOTS:
                equipArmor(&boots, itemAndType, index);
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

static void deleteItem(int index) {
    if (index < 0 || index > INVENTORY_SIZE - 1) {
        return;
    }
    inventory->items[index].type = ITEM_NULL;
}

static Potion* getPotion(int index) {
    ItemAndType *itemAndType = getItem(index);
    return itemAndType != NULL && itemAndType->type == POTION
        ? &itemAndType->item.potion
        : NULL;
}

static void usePotion(int index) {
    Potion* potion = getPotion(index);
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
            if (getLastPotionDamage() > 0) {
                setDamage(getAdventurer()->damage - getLastPotionDamage());
            }
            setDamage(getAdventurer()->damage + potion->amount);
            setLastPotionDamage(potion->amount);
            setStrengthPotionTime(3);
            break;
        case DEFENSE:
            setLastPotionDefence(potion->amount);
            setDefencePotionTime(3);
            break;
        case EXPERIENCE:
            setXp(getAdventurer()->xp + potion->amount);
            break;
    }
    deleteItem(index);
}
