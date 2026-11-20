#ifndef GAME_ITEMGENERATOR_H
#define GAME_ITEMGENERATOR_H
#include "../Services/InventoryService.h"
#include "Adventurer.h"
#pragma once

ItemAndType generateTreasure(); //returns ItemAndType with Type ITEM_NULL if returns money and ItemAndType if returns item
ItemAndType generateRandomItem();
ItemAndType generateQuestItem();
#endif //GAME_ITEMGENERATOR_H
