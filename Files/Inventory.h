//
// Created by User on 17.10.2026.
//

#ifndef JAC_INVENTORY_H
#define JAC_INVENTORY_H
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

typedef struct Inventory {
    Item items[10];
    int itemCount;
} Inventory;
#endif //JAC_INVENTORY_H
