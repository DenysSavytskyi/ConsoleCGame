#include "ShopService.h"

static Market market;

void newShop() {
    for (int i = 0; i < SHOP_SIZE; i++) {
        market.items[i] = generateRandomItem();
    }
}

ItemAndType* getShopItem(int itemIndex) {
    return &market.items[itemIndex];
}

void buyItem(int itemIndex) {
    ItemAndType* shopItem = getShopItem(itemIndex);
    int price = getItemPrice(shopItem);
    if (getAdventurer()->money >= price) {
        if (addItem(*shopItem)) {
            getAdventurer()->money -= price;
            shopItem->type = ITEM_NULL;
        }
    }
}

State shopService() {
    char input = getAndCheckShopInput();
    while (input != 'x') {
        switch (input) {
            case 'w':
                setShopIndex(getShopIndex() - ITEMS_IN_ROW);
                break;
            case 'a':
                setShopIndex(getShopIndex() - 1);
                break;
            case 's':
                setShopIndex(getShopIndex() + ITEMS_IN_ROW);
                break;
            case 'd':
                setShopIndex(getShopIndex() + 1);
                break;
            case 'e':
                if (getShopIndex() < SHOP_SIZE) {
                    buyItem(getShopIndex());
                } else
                    sellItem(getCurrentIndex()-5);
            default:
                break;
        }
        input = getAndCheckShopInput();
    }
    return MAP_STATE;
}

char getAndCheckShopInput() {
    while (1) {
        clearConsole();
        printShop();
        char possibleInputs[7]; // [w][a][s][d] to navigate inventory and shop, [x] to quit, [e] to sell/buy and terminator
        int inputCount = checkPossibleInputShop(possibleInputs);
        possibleInputs[inputCount] = '\0';
        mvprintw(SHOP_ITEM_BOX_Y * (INVENTORY_SIZE/ITEMS_IN_ROW + SHOP_SIZE/ITEMS_IN_ROW) + SHOP_PAD + 1, 0, "Possible input:\n");
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

int checkPossibleInputShop(char *possibleInputs) {
    int count = 0;
    if (getShopIndex()>=10) {
        possibleInputs[count++] = 'w';
    }
    if (getShopIndex()%5!=0) {
        possibleInputs[count++] = 'a';
    }
    if (getShopIndex()<5) {
        possibleInputs[count++] = 's';
    }
    if (getShopIndex()%5!=4) {
        possibleInputs[count++] = 'd';
    }
    ItemAndType* item = getShopIndex()<5?getShopItem(getShopIndex()):getItem(getCurrentIndex());
    if (item->type != ITEM_NULL && item->type != QUEST_ITEM) {
        possibleInputs[count++] = 'e';
    }
    possibleInputs[count++] = 'x';
    return count;
}

