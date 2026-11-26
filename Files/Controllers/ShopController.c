#include "ShopController.h"
#include "../Services/ShopService.h"

static int shopIndex = 0;

void setShopIndex(int index) {
    int maxIndex = SHOP_SIZE + INVENTORY_SIZE - 1;
    if (index < 0) {
        shopIndex = 0;
    } else if (index > maxIndex) {
        shopIndex = maxIndex;
    } else {
        shopIndex = index;
    }
}

int getShopIndex() {
    return shopIndex;
}

static void printShopItemBox(WINDOW* derWin, ItemAndType* itemAndType, bool isSelected, const char* action) {
    int y = getmaxy(derWin);
    printItemBoxForInventory(derWin, itemAndType, isSelected, true);
    printOnlyHorizontalLine(derWin, y - 3);
    wrefresh(derWin);
    mvwprintw(derWin, y - 2, 1, " %s: %d", action, getItemPrice(itemAndType));
}

static void printInventoryForShop(WINDOW* win, int itemBoxY, int itemBoxX, int inventorySize) {
    int selectedIndex = getShopIndex() >= SHOP_SIZE
        ? getShopIndex() - SHOP_SIZE
        : -1;
    printInventory(win, itemBoxY, itemBoxX, inventorySize, selectedIndex, true);

    for (int i = 0; i < inventorySize; i++) {
        int y = (i / ITEMS_IN_ROW) * itemBoxY;
        int x = (i % ITEMS_IN_ROW) * itemBoxX;
        WINDOW* derWin = derwin(win, itemBoxY, itemBoxX, y, x);
        ItemAndType* item = getItem(i);
        if (derWin != NULL && item != NULL) {
            mvwprintw(derWin, itemBoxY - 2, 1, " Sell: %d", getItemPrice(item));
            delwin(derWin);
        }
    }
    wrefresh(win);
}

void printShop() {
    int shopRows = (SHOP_SIZE + ITEMS_IN_ROW - 1) / ITEMS_IN_ROW;
    int inventoryRows = (INVENTORY_SIZE + ITEMS_IN_ROW - 1) / ITEMS_IN_ROW;
    int shopHeight = SHOP_ITEM_BOX_Y * shopRows;
    int inventoryHeight = SHOP_ITEM_BOX_Y * inventoryRows;
    int inventoryY = shopHeight + SHOP_PAD;
    WINDOW* shopWin = newwin(shopHeight, SHOP_ITEM_BOX_X * ITEMS_IN_ROW, 0, 0);
    if (shopWin == NULL) {
        return;
    }

    for (int i = 0; i < SHOP_SIZE; i++) {
        int y = (i / ITEMS_IN_ROW) * SHOP_ITEM_BOX_Y;
        int x = (i % ITEMS_IN_ROW) * SHOP_ITEM_BOX_X;
        WINDOW* derWin = derwin(shopWin, SHOP_ITEM_BOX_Y, SHOP_ITEM_BOX_X, y, x);
        ItemAndType* item = getShopItem(i);
        if (derWin != NULL && item != NULL) {
            printShopItemBox(derWin, item, i == getShopIndex(), "Buy");
            wrefresh(derWin);
            delwin(derWin);
        }
    }
    wrefresh(shopWin);

    WINDOW* inventoryWin = newwin(inventoryHeight, SHOP_ITEM_BOX_X * ITEMS_IN_ROW, inventoryY, 0);
    if (inventoryWin != NULL) {
        printInventoryForShop(inventoryWin, SHOP_ITEM_BOX_Y, SHOP_ITEM_BOX_X, INVENTORY_SIZE);
        delwin(inventoryWin);
    }
    delwin(shopWin);

}
