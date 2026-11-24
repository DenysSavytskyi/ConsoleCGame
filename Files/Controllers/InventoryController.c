#include "InventoryController.h"

#define INFO_Y 13
#define INFO_X 27
#define ITEM_BOX_Y 6
#define ITEM_BOX_X 14

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
    printCross(infoWin, 2, INFO_X / 2);
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
        }

        ItemAndType* itemAndType = getItem(i);
        char* itemType = "Empty";
        switch (itemAndType->type){
            case POTION:
                itemType = "Potion";
                break;
            case WEAPON:
                itemType = "Weapon";
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
        char possibleInputs[9]; // [w][a][s][d] to navigate inventory, [q] to quit, [e] to equip, [f] to use, [x] to drop and terminator
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
