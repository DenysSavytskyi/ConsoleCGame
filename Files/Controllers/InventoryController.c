#include "InventoryController.h"

#define INFO_Y 11
#define CHARACTER_X 13
#define INFO_X 34
#define ITEM_BOX_Y 6
#define ITEM_BOX_X 19

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

void printAdventurerAndStats() {
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

void printInventory() {
    WINDOW* inventoryWin = newwin(ITEM_BOX_Y*(INVENTORY_SIZE/5), ITEM_BOX_X*(INVENTORY_SIZE%5), INFO_Y, 0);
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        WINDOW* derWin = derwin(inventoryWin, ITEM_BOX_Y, ITEM_BOX_X, (i/5)*ITEM_BOX_Y, (i%5)*ITEM_BOX_X);
        if (i == getCurrentIndex()) {
            wattron(derWin, COLOR_PAIR(6));
            box(derWin, 0, 0);
            wattroff(derWin, COLOR_PAIR(6));
        } else {
            box(derWin, 0, 0);
            printLeftAndRightTees(derWin, 2);
        }
        printOnlyHorizontalLine(derWin, 2);
        ItemAndType* itemAndType = getItem(i);
        char* itemType = "Empty";
        char* potionType = "NONE";
        switch (itemAndType->type){
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
        wrefresh(derWin);
    }
    wrefresh(inventoryWin);
}

void printInventoryService() {
    printAdventurerAndStats();
    printInventory();
}

char getAndCheckInventoryInput() {
    while (1) {
        clearConsole();
        printInventoryService();
        char possibleInputs[8]; // [w][a][s][d] to navigate inventory, [x] to quit, [e] to equip/use, [q] to drop and terminator
        int inputCount = checkPossibleMovesInventory(possibleInputs);
        possibleInputs[inputCount] = '\0';
        mvprintw(ITEM_BOX_Y * (INVENTORY_SIZE/5) + INFO_Y + 1, 0, "Possible moves:\n");
        for (int i = 0; i < inputCount; i++) {
            printw(" %c", possibleInputs[i]);
        }
        printw("\nEnter your move:\n");
        refresh();

        char input = (char)getch();
        while (input == ERR) {
            input = (char)getch();
        }
        if (checkInput(possibleInputs, input)) {
            return input;
        }
    }
}
