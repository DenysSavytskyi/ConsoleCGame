//
// Created by User on 06.10.2026.
//

#include "stdio.h"
#include "Adventurer.h"
#include "Profession.h"

Adventurer adventurer;

Adventurer* getAdventurer() {
    return &adventurer;
};

void printStats(Adventurer *adventurer) {
    printf("Name: %s\n", adventurer->name);
    switch (adventurer->profession) {
        case FIGHTER:
            printf("Profession: Fighter\n");
            break;
        case MAGE:
            printf("Profession: Mage\n");
            break;
        case THIEF:
            printf("Profession: Thief\n");
            break;
        case BARD:
            printf("Profession: Bard\n");
            break;
        case CLERIC:
            printf("Profession: Cleric\n");
            break;
    }
    printf("HP: %d/%d\n", adventurer->hp, adventurer->hpMax);
}

Adventurer* newAdventurer(char *name, Profession profession, int hpMax, int damage, int money, int xp, int x, int y) {
    Adventurer adventurer;
    adventurer.name[50] = *name;
    adventurer.profession = profession;
    adventurer.hpMax = hpMax;
    adventurer.hp = hpMax;
    adventurer.damage = damage;
    adventurer.money = money;
    adventurer.level = 1;
    adventurer.xp = xp;
    adventurer.x = x;
    adventurer.y = y;
    return &adventurer;
}

Adventurer* createAdventurer() {
    Adventurer *adventurer;
    printf("Please enter your name(only lowercase or uppercase letters): ");
    char name[50];
    scanf("%[A-Za-z]s", name);
    while (true){
        printf("Please choose your profession:\n");
        printf("1. Fighter\n");
        printf("2. Mage\n");
        printf("3. Thief\n");
        printf("4. Bard\n");
        printf("5. Cleric\n");
        int professionChoice;
        scanf("%d", &professionChoice);
        switch (professionChoice) {
            case 1:
                adventurer = newAdventurer(name, FIGHTER, 10, 10, 0, 0, 0, 0);
                return adventurer;
            case 2:
                adventurer = newAdventurer(name, MAGE, 70, 7, 0, 50, 0, 0);
                return adventurer;
            case 3:
                adventurer = newAdventurer(name, THIEF, 80, 8, 100, 0, 0, 0);
                return adventurer;
            case 4:
                adventurer = newAdventurer(name, BARD, 90, 6, 0, 0, 0, 0);
                return adventurer;
            case 5:
                adventurer = newAdventurer(name, CLERIC, 110, 9, 0, 0, 0, 0);
                return adventurer;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

}
