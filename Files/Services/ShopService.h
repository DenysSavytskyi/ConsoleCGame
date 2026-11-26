#ifndef SHOP_SERVICE_H
#define SHOP_SERVICE_H
#include <ncurses.h>
#include "../Controllers/ShopController.h"
#include "InventoryService.h"
#include "Service.h"
#include "../Modules/State.h"
#pragma once

typedef struct Market {
    ItemAndType items[5];
} Market;


void newShop();
ItemAndType* getShopItem(int itemIndex);
State shopService();

#endif
