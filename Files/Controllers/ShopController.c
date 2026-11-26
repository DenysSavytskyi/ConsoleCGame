#include "ShopController.h"

static int shopIndex = 0;

void setShopIndex(int index) {
    shopIndex = index;
}

int getShopIndex() {
    return shopIndex;
}

static void printItemBoxForShop(WINDOW* derWin, ItemAndType* itemAndType, int index, bool isShop) {
    int y = getmaxy(derWin);
    if ((isShop?index:index+5) == getShopIndex()) {
        wattron(derWin, COLOR_PAIR(6));
        box(derWin, 0, 0);
        wattroff(derWin, COLOR_PAIR(6));
    } else {
        box(derWin, 0, 0);
        printLeftAndRightTees(derWin, 2);
        printLeftAndRightTees(derWin, y-3);
    }
    printOnlyHorizontalLine(derWin, 2);
    printOnlyHorizontalLine(derWin, y-3);
    printItemStats(derWin, itemAndType);
    if (isShop)
        mvwprintw(derWin, y-2, 1, " Buy: %d", getItemPrice(itemAndType));
    else
        mvwprintw(derWin, y-2, 1, " Sell: %d", getItemPrice(itemAndType));
}

static void printInventoryForShop(WINDOW* win, int itemBoxY, int itemBoxX, int inventorySize) {
    for (int i = 0; i < inventorySize; i++) {
        int y = (i / ITEMS_IN_ROW) * itemBoxY;
        int x = (i % ITEMS_IN_ROW) * itemBoxX;
        WINDOW* derWin = derwin(win, itemBoxY, itemBoxX, y, x);
        printItemBoxForShop(derWin, getItem(i), i, false);
        delwin(derWin);
    }
    wrefresh(win);
}

void printShop() {
    WINDOW* shopWin = newwin(SHOP_ITEM_BOX_Y * (SHOP_SIZE/ITEMS_IN_ROW), SHOP_ITEM_BOX_X * ITEMS_IN_ROW, 0, 0);
    for (int i = 0; i < SHOP_SIZE; i++) {
        int y = (i / ITEMS_IN_ROW) * SHOP_ITEM_BOX_Y;
        int x = (i % ITEMS_IN_ROW) * SHOP_ITEM_BOX_X;
        WINDOW* derWin = derwin(shopWin, SHOP_ITEM_BOX_Y, SHOP_ITEM_BOX_X, y, x);
        printItemBoxForShop(derWin, getShopItem(i), i, true);
        wrefresh(derWin);
        delwin(derWin);
    }
    wrefresh(shopWin);
    WINDOW* inventoryWin = newwin(SHOP_ITEM_BOX_Y*(INVENTORY_SIZE/ITEMS_IN_ROW), SHOP_ITEM_BOX_X * ITEMS_IN_ROW, SHOP_ITEM_BOX_Y * (SHOP_SIZE/ITEMS_IN_ROW)+SHOP_PAD, 0);
    printInventoryForShop(inventoryWin, SHOP_ITEM_BOX_Y, SHOP_ITEM_BOX_X, INVENTORY_SIZE);
}
