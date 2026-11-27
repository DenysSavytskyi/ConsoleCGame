#ifndef JAC_MAP_H
#define JAC_MAP_H
#include <stdbool.h>
#include <stdlib.h>
#include "../Modules/State.h"
#include "../Modules/ItemTypes.h"
#include "Service.h"
#pragma once

#define MIN_ROOM_SIZE 15
#define MAX_ROOM_SIZE 25
#define MIN_ROOMS_COUNT 6
#define MAX_ROOMS_COUNT 9

typedef struct Reward {
    int roomIndex;
    int x;
    int y;
} Reward;

typedef struct ItemAndTypeOnMap {
    ItemAndType itemAndType;
    int roomIndex;
    int x;
    int y;
} ItemAndTypeOnMap;

typedef enum RoomType {
    StartRoom = '1',
    TreasureRoom = '$',
    EnemyRoom = 'E',
    ShopRoom = 'S',
    NPCRoom = 'N',
    BossRoom = 'B',
    NullRoom = '0'
} RoomType;

typedef enum Cell {
    Empty = ' ',
    Wall = '#',
    Stuff = 'I',
    Treasure = '$',
    Enemy = 'E',
    Door = 'D',
    Player = 'A',
    NPC = 'N',
    Shop = 'S',
    Portal = 'P'
} Cell;

typedef struct Room {
    RoomType type;
    int roomSize;
    Cell **roomMap;
} Room;

typedef struct Map {
    int roomsCount;
    int currentRoom;
    Room *rooms;
    bool *connections;
} Map;

int getLevel();
Cell getCurrentRoomCell(int row, int column);
int addItemOnMap(ItemAndType item, int roomIndex, int row, int column); //returns 1 if ok and 0 if no space
int spawnQuestItem(ItemAndType item);
State mapService();
Map* getMap();
RoomType* getMinimap();
Room* getCurrentRoom();
bool areRoomsConnected(int firstRoom, int secondRoom);
int checkPossibleMovesMap(char *possibleInputs);
void removeEnemyFromMap(bool isBoss);

#endif //JAC_MAP_H
