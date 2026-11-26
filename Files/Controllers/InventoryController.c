#include "InventoryController.h"

#define INFO_Y 11
#define CHARACTER_X 13
#define INFO_X 34
#define ITEM_BOX_Y 6
#define ITEM_BOX_X 20


static int currentIndex = 0;

void setCurrentIndex(int index) {
    if (index < 0) {
        currentIndex = 0;
    } else if (index >= INVENTORY_SIZE) {
        currentIndex = INVENTORY_SIZE - 1;
    } else {
        currentIndex = index;
    }
}

int getCurrentIndex() {
    return currentIndex;
}

static void printAdventurerAndStats() {
    WINDOW* infoWin = newwin(INFO_Y, INFO_X, 0, 0);
    box(infoWin, 0, 0);
    printVerticalLine(infoWin, CHARACTER_X);
    for (int i = 0; i < 9; i++) {
        mvwprintw(infoWin, 1 + i, 1, "%s", getASCII(getAdventurer()->profession, i));
    }
    WINDOW* derWin = derwin(infoWin, INFO_Y, INFO_X - CHARACTER_X, 0, CHARACTER_X);
    int line = 1;
    mvwprintw(derWin, line++, 1, "hp: %d/%d", getAdventurer()->hp, getAdventurer()->hpMax);
    mvwprintw(derWin, line++, 1, "damage: %d", getAdventurer()->damage);
    mvwprintw(derWin, line++, 1, "defense: %d%%", getTotalDefense());
    mvwprintw(derWin, line++, 1, "level: %d", getAdventurer()->level);
    mvwprintw(derWin, line++, 1, "xp: %d", getAdventurer()->xp);
    mvwprintw(derWin, line++, 1, "money: %d", getAdventurer()->money);
    wrefresh(derWin);
    wrefresh(infoWin);
}

static void printItemStats(WINDOW* derWin, ItemAndType* itemAndType) {
    char* itemType = "Empty";
    char* potionType = "NONE";
    switch (itemAndType->type) {
        case POTION:
            itemType = "Potion";
            switch (itemAndType->item.potion.type) {
                case HEALTH:
                    potionType = "Health";
                    break;
                case STRENGTH:
                    potionType = "Strength";
                    break;
                case DEFENSE:
                    potionType = "Defense";
                    break;
                case EXPERIENCE:
                    potionType = "Experience";
                    break;
            }
            mvwprintw(derWin, 3, 1, " Type: %s", potionType);
            mvwprintw(derWin, 4, 1, " Gives: %d", itemAndType->item.potion.amount);
            break;
        case WEAPON:
            itemType = "Weapon";
            mvwprintw(derWin, 3, 1, " Damage: %d", itemAndType->item.weapon.damage);
            break;
        case ARMOR:
            switch (itemAndType->item.armor.part) {
                case HELMET:
                    itemType = "Helmet";
                    break;
                case CHESTPLATE:
                    itemType = "Chestplate";
                    break;
                case LEGGINGS:
                    itemType = "Leggings";
                    break;
                case BOOTS:
                    itemType = "Boots";
                    break;
            }
            mvwprintw(derWin, 3, 1, " Defense: %d", itemAndType->item.armor.defense);
            break;
        case QUEST_ITEM:
            itemType = "Quest Item";
            break;
        case ITEM_NULL:
            itemType = "Empty";
            break;
    }
    mvwprintw(derWin, 1, 1, " %s", itemType);
}

void printItemBoxForInventory(WINDOW* derWin, ItemAndType* itemAndType, bool isSelected) {
    if (isSelected) {
        wattron(derWin, COLOR_PAIR(6));
        box(derWin, 0, 0);
        wattroff(derWin, COLOR_PAIR(6));
    } else {
        box(derWin, 0, 0);
        printLeftAndRightTees(derWin, 2);
    }
    printOnlyHorizontalLine(derWin, 2);
    printItemStats(derWin, itemAndType);
}

void printInventory(WINDOW* win, int itemBoxY, int itemBoxX, int inventorySize, int selectedIndex) {
    for (int i = 0; i < inventorySize; i++) {
        int y = (i / ITEMS_IN_ROW) * itemBoxY;
        int x = (i % ITEMS_IN_ROW) * itemBoxX;
        WINDOW* derWin = derwin(win, itemBoxY, itemBoxX, y, x);
        printItemBoxForInventory(derWin, getItem(i), i == selectedIndex);
        wrefresh(derWin);
        delwin(derWin);
    }
    wrefresh(win);
}

static void printInventoryService() {
    WINDOW* inventoryWin = newwin(ITEM_BOX_Y*(INVENTORY_SIZE/ITEMS_IN_ROW), ITEM_BOX_X * ITEMS_IN_ROW, INFO_Y, 0);
    printAdventurerAndStats();
    printInventory(inventoryWin, ITEM_BOX_Y, ITEM_BOX_X, INVENTORY_SIZE, currentIndex);
}

char getAndCheckInventoryInput() {
    while (1) {
        clearConsole();
        printInventoryService();
        char possibleInputs[8]; // [w][a][s][d] to navigate inventory, [x] to quit, [e] to equip/use, [q] to drop and terminator
        int inputCount = checkPossibleInputInventory(possibleInputs);
        possibleInputs[inputCount] = '\0';
        printInputOptions(ITEM_BOX_Y * (INVENTORY_SIZE/ITEMS_IN_ROW) + INFO_Y + 1,
                          "Possible input:\n", possibleInputs, inputCount);
        char input = getInputChar();
        if (checkInput(possibleInputs, input)) {
            return input;
        }
    }
}
