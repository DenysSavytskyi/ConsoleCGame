#ifndef INVENTORY_CONTROLLER_H
#define INVENTORY_CONTROLLER_H
#include "Controller.h"
#include "../Services/InventoryService.h"
#include "../Services/Service.h"
#pragma once

void setCurrentIndex(int index);
int getCurrentIndex();
void printAdventurerAndStats();
void printInventory();
void printInventoryService();
char getAndCheckInventoryInput();

#endif
