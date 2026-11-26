#ifndef SHOP_CONTROLLER_H
#define SHOP_CONTROLLER_H
#include <ncurses.h>
#include "Controller.h"
#include "InventoryController.h"
#include "../Modules/ItemGenerator.h"
#pragma once

#define SHOP_PAD 5
#define SHOP_ITEM_BOX_Y 8
#define SHOP_ITEM_BOX_X 20
#define SHOP_SIZE 5

void setShopIndex(int index);
int getShopIndex();
void printShop();

#endif
