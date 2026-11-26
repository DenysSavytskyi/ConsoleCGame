#include "ShopService.h"

static Market market;

static char getAndCheckShopInput();
static int checkPossibleInputShop(char *possibleInputs);

void newShop() {
    for (int i = 0; i < SHOP_SIZE; i++) {
        market.items[i] = generateRandomItem();
    }
}

ItemAndType* getShopItem(int itemIndex) {
    if (itemIndex < 0 || itemIndex >= SHOP_SIZE) {
        return NULL;
    }
    return &market.items[itemIndex];
}

static void buyItem(int itemIndex) {
    ItemAndType* shopItem = getShopItem(itemIndex);
    if (shopItem == NULL || shopItem->type == ITEM_NULL || shopItem->type == QUEST_ITEM) {
        return;
    }
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
                } else {
                    sellItem(getShopIndex() - SHOP_SIZE);
                }
                break;
            default:
                break;
        }
        input = getAndCheckShopInput();
    }
    return MAP_STATE;
}

static char getAndCheckShopInput() {
    while (1) {
        clearConsole();
        printShop();
        char possibleInputs[7]; // [w][a][s][d] to navigate inventory and shop, [x] to quit, [e] to sell/buy and terminator
        int inputCount = checkPossibleInputShop(possibleInputs);
        possibleInputs[inputCount] = '\0';
        int shopRows = (SHOP_SIZE + ITEMS_IN_ROW - 1) / ITEMS_IN_ROW;
        int inventoryRows = (INVENTORY_SIZE + ITEMS_IN_ROW - 1) / ITEMS_IN_ROW;
        printInputOptions(SHOP_ITEM_BOX_Y * (shopRows + inventoryRows) + SHOP_PAD + 1,
                          "Possible input:\n", possibleInputs, inputCount);
        char input = getInputChar();
        if (checkInput(possibleInputs, input)) {
            return input;
        }
    }
}

static int checkPossibleInputShop(char *possibleInputs) {
    int count = 0;
    int index = getShopIndex();
    int totalItems = SHOP_SIZE + INVENTORY_SIZE;
    if (index >= ITEMS_IN_ROW) {
        possibleInputs[count++] = 'w';
    }
    if (index % ITEMS_IN_ROW != 0) {
        possibleInputs[count++] = 'a';
    }
    if (index + ITEMS_IN_ROW < totalItems) {
        possibleInputs[count++] = 's';
    }
    if (index % ITEMS_IN_ROW != ITEMS_IN_ROW - 1) {
        possibleInputs[count++] = 'd';
    }
    ItemAndType* item = index < SHOP_SIZE
        ? getShopItem(index)
        : getItem(index - SHOP_SIZE);
    if (item != NULL && item->type != ITEM_NULL && item->type != QUEST_ITEM) {
        possibleInputs[count++] = 'e';
    }
    possibleInputs[count++] = 'x';
    return count;
}

