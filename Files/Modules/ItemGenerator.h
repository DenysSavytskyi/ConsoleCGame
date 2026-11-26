#ifndef GAME_ITEMGENERATOR_H
#define GAME_ITEMGENERATOR_H
#include "ItemTypes.h"
#include "../Services/MapService.h"
#pragma once

ItemAndType generateTreasure(); //returns ItemAndType with Type ITEM_NULL if returns money and ItemAndType if returns item
ItemAndType generateRandomItem();
int getItemPrice(ItemAndType* itemAndType);

#endif //GAME_ITEMGENERATOR_H
