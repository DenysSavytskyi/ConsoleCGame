#ifndef GAME_ITEM_TYPES_H
#define GAME_ITEM_TYPES_H

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

#endif
