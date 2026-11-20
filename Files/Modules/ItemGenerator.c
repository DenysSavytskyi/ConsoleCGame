#define MIN_MONEY 30
#define MAX_MONEY 50
#include "ItemGenerator.h"
#pragma once

ItemAndType generateTreasure() {
    if (getRandom(0,1)) {
        setMoney(getAdventurer()->money + getRandom(MIN_MONEY, MAX_MONEY));
        ItemAndType itemAndType;
        itemAndType.type = ITEM_NULL;
        return itemAndType;
    }

    return generateRandomItem();
}

ItemAndType generateRandomItem() {
    ItemAndType itemAndType;
    itemAndType.type = (ItemType)getRandom(0, 3);
    switch (itemAndType.type) {
        case POTION:
            itemAndType.item.potion.type = (PotionType)getRandom(0, 2);
            itemAndType.item.potion.amount = getRandom(10, 30);
            break;
        case WEAPON:
            itemAndType.item.weapon.damage = getRandom(1, 10);
            break;
        case ARMOR:
            itemAndType.item.armor.defense = getRandom(5, 15);
            break;
        default:
            break;
    }
    return itemAndType;
}

ItemAndType generateQuestItem() {
    ItemAndType itemAndType;
    itemAndType.type = QUEST_ITEM;
    return itemAndType;
}

