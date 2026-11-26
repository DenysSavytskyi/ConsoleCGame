#ifndef INVENTORY_CONTROLLER_H
#define INVENTORY_CONTROLLER_H
#include "Controller.h"
#include "../Services/InventoryService.h"
#include "../Services/Service.h"
#include "../Modules/Adventurer.h"
#include "../Modules/Profession.h"
#pragma once
#define ITEMS_IN_ROW 5

void setCurrentIndex(int index);
int getCurrentIndex();
void printAdventurerAndStats();
void printItemStats(WINDOW* derWin, ItemAndType* itemAndType);
void printItemBoxForInventory(WINDOW* derWin, ItemAndType* itemAndType, bool isSelected, bool additionalLine);
void printInventory(WINDOW* win, int itemBoxY, int itemBoxX, int inventorySize, int currentIndex, bool additionalLine);
void printInventoryService();
char getAndCheckInventoryInput();

#endif
