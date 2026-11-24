#define MIN_MONEY 30
#define MAX_MONEY 50
#include "ItemGenerator.h"
#include "Adventurer.h"
#include "../Services/Service.h"

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
    itemAndType.type = (ItemType)getRandom(0, 2);
    switch (itemAndType.type) {
        case POTION:
            itemAndType.item.potion.type = (PotionType)getRandom(0, 2);
            switch (itemAndType.item.potion.type) {
                case HEALTH:
                    itemAndType.item.potion.amount = getRandom(5, 20) * getLevel();
                    break;
                case STRENGTH:
                    itemAndType.item.potion.amount = getRandom(1, 5) * getLevel();
                    break;
                case DEFENSE:
                    itemAndType.item.potion.amount = getRandom(1, 5) * getLevel();
                    break;
                case EXPERIENCE:
                    itemAndType.item.potion.amount = getRandom(5, 20) * getLevel();
            }
            break;
        case WEAPON:
            itemAndType.item.weapon.damage = getRandom(1, 5) * getLevel();
            break;
        case ARMOR:
            itemAndType.item.armor.defense = getRandom(2, 5) * getLevel();
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
