//
// Created by User on 17.10.2026.
//

#ifndef JAC_MAP_H
#define JAC_MAP_H
#pragma once
#include <stdbool.h>
#include "Service.h"
#include "../Modules/State.h"
#include "../Modules/Adventurer.h"
#include "../Controllers/MapController.h"
#include "../Modules/EnemyEntity.h"

#define MIN_ROOM_SIZE 15
#define MAX_ROOM_SIZE 25
#define MIN_ROOMS_COUNT 6
#define MAX_ROOMS_COUNT 9

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
void setCurrentRoomCell(int row, int column, Cell cell);
Cell getRoomCell(int roomIndex, int row, int column);
void setRoomCell(int roomIndex, int row, int column, Cell cell);
void initRooms(int roomsCount);
void initRoom(int roomIndex, RoomType type);
void initMap();
void setDoors(int firstRoom, int secondRoom);
void connectRooms(int roomsCount);
void nextRoom();
State mapService();
Map* getMap();
RoomType* getMinimap();
Cell** getRoomMap(int roomIndex);
Cell** getCurrentRoomMap();
void generateMap(int RoomIndex, RoomType type, int roomSize);
Room* getRoom(int roomIndex);
Room* getCurrentRoom();
bool areRoomsConnected(int firstRoom, int secondRoom);
State mapMove();
int checkPossibleMovesMap(char *possibleInputs);
void removeEnemyFromMap(bool isBoss);
void completeMap();

#endif //JAC_MAP_H
