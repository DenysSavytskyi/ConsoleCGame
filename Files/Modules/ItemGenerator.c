#define MIN_MONEY 3
#define MAX_MONEY 5
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
            itemAndType.item.potion.type = (PotionType)getRandom(HEALTH, EXPERIENCE);
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
            ArmorPart armorPart = (ArmorPart)getRandom(0, 3);
            switch (armorPart) {
                case HELMET:
                    itemAndType.item.armor.part = HELMET;
                    break;
                case CHESTPLATE:
                    itemAndType.item.armor.part = CHESTPLATE;
                    break;
                case LEGGINGS:
                    itemAndType.item.armor.part = LEGGINGS;
                    break;
                case BOOTS:
                    itemAndType.item.armor.part = BOOTS;
                    break;
            }
            itemAndType.item.armor.defense = getRandom(2, 5) * getLevel();
            break;
        default:
            break;
    }
    return itemAndType;
}

int getItemPrice(ItemAndType* itemAndType) {
    switch (itemAndType->type) {
        case POTION:
            return itemAndType->item.potion.amount * 1;
        case WEAPON:
            return itemAndType->item.weapon.damage * 3;
        case ARMOR:
            return itemAndType->item.armor.defense * 2;
        default:
            return 0;
    }
}
