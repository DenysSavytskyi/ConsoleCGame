//
// Created by User on 17.10.2026.
//

#include "MapService.h"
#include <stdio.h>
#include <stdlib.h>

static int level = 0;
static Map *map = nullptr;
static RoomType *minimap = nullptr;
void initMap() {
    map = malloc(sizeof(Map));
    map->roomsCount = getRandom(MIN_ROOMS_COUNT, MAX_ROOMS_COUNT);
    map->currentRoom = 0;
    map->rooms = malloc(map->roomsCount * sizeof(Room));
    initRooms(map->roomsCount);
}

Cell getCurrentRoomCell(int row, int column) {
    return getRoomCell(map->currentRoom, row, column);
}

void setCurrentRoomCell(int row, int column, Cell cell) {
    setRoomCell(map->currentRoom, row, column, cell);
}

Cell getRoomCell(int roomIndex, int row, int column) {
    return map->rooms[roomIndex].roomMap[row][column];
}

void setRoomCell(int roomIndex, int row, int column, Cell cell) {
    map->rooms[roomIndex].roomMap[row][column] = cell;
}

void initRooms(int roomsCount) {
    RoomType possibleTypes[] = {TreasureRoom, EnemyRoom, EnemyRoom, EnemyRoom, EnemyRoom, ShopRoom, NPCRoom};
    initRoom(0, StartRoom);
    initRoom(roomsCount-1, BossRoom);
    for (int i = 1; i < roomsCount-1; i++) {
        int rand = getRandom(0, 6);
        while (possibleTypes[rand] == NullRoom) {
            rand = getRandom(0, 6);
        }
        initRoom(i, possibleTypes[rand]);
        possibleTypes[rand] = NullRoom;
    }
    connectRooms(roomsCount);
}

void initRoom(int roomIndex, RoomType type) {
    map->rooms[roomIndex].type = type;
    map->rooms[roomIndex].roomSize = getRandom(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
    generateMap(roomIndex, type, map->rooms[roomIndex].roomSize);
}

void generateMap(int roomIndex, RoomType roomType, int roomSize) {
    Cell element = Empty;
    switch (roomType) {
        case StartRoom:
            setX(roomSize / 2);
            setY(roomSize / 2);
            element = Empty;
            break;
        case TreasureRoom:
            element = Treasure;
            break;
        case EnemyRoom:
            element = Enemy;
            break;
        case ShopRoom:
            element = Shop;
            break;
        case NPCRoom:
            element = NPC;
            break;
        case BossRoom:
            element = Enemy;
            break;
        default:
            element = Empty;
    }
    map->rooms[roomIndex].roomMap = malloc(roomSize * sizeof(Cell*));
    for (int i = 0; i < roomSize; i++) {
        map->rooms[roomIndex].roomMap[i] = malloc(roomSize * sizeof(Cell));
    }

    for (int y = 0; y < roomSize; y++) {
        for (int x = 0; x < roomSize; x++) {
            if (y == 0 || y == roomSize - 1 || x == 0 || x == roomSize - 1) {
                setRoomCell(roomIndex, y, x, Wall);
            } else {
                setRoomCell(roomIndex, y, x, Empty);
            }
        }
    }
    int randomWallsCount = getRandom(1, roomSize - 3);
    for (int i = 0; i < randomWallsCount; i++) {
        int x = getRandom(1, roomSize - 2);
        int y = getRandom(1, roomSize - 2);
        while (
            roomIndex == 0 && x == getAdventurer()->x || y == getAdventurer()->y ||
            getRoomCell(roomIndex, y, x) != Empty ||
            getRoomCell(roomIndex, y+1, x) != Empty ||
            getRoomCell(roomIndex, y, x+1) != Empty ||
            getRoomCell(roomIndex, y-1, x) != Empty ||
            getRoomCell(roomIndex, y, x-1) != Empty
            ) {
            x = getRandom(1, roomSize - 2);
            y = getRandom(1, roomSize - 2);
        }
        setRoomCell(roomIndex, y, x, Wall);
    }

    setRoomCell(roomIndex, getRandom(2, roomSize-2), getRandom(2, roomSize-2), element);
}
void setDoors(int firstRoom, int secondRoom) {
    int firstRoomSize = map->rooms[firstRoom].roomSize;
    int secondRoomSize = map->rooms[secondRoom].roomSize;
    if (firstRoom + 1 == secondRoom) {
        setRoomCell(firstRoom, firstRoomSize / 2, firstRoomSize-2, Door);
        setRoomCell(secondRoom, secondRoomSize / 2, 1, Door);
    } else if (firstRoom - 1 == secondRoom) {
        setRoomCell(firstRoom, firstRoomSize / 2, 1, Door);
        setRoomCell(secondRoom, secondRoomSize / 2, secondRoomSize-2, Door);
    } else if (firstRoom + 3 == secondRoom) {
        setRoomCell(firstRoom, firstRoomSize-2, firstRoomSize / 2, Door);
        setRoomCell(secondRoom, 1, secondRoomSize / 2, Door);
    } else if (firstRoom - 3 == secondRoom) {
        setRoomCell(firstRoom, 1, firstRoomSize / 2, Door);
        setRoomCell(secondRoom, secondRoomSize-2, secondRoomSize / 2, Door);
    }
}
void connectRooms(int roomsCount) {
    RoomType *graph = malloc(roomsCount * sizeof(RoomType));
    bool *isVisited = malloc(roomsCount * sizeof(bool));
    for (int i = 0; i < roomsCount; i++) {
        graph[i] = map->rooms[i].type;
        isVisited[i] = false;
    }
    isVisited[1] = true;
    setDoors(0, 1);
    setDoors(roomsCount-1, roomsCount-2);
    for (int i = 2; i < roomsCount-1; i++) {
        int randomIndex;
        while (true) {
            randomIndex = getRandom(2, roomsCount-2);
        if (isVisited[randomIndex]) {
            continue;
        }
        if (randomIndex-3 >= 0 && isVisited[randomIndex-3]) {
            setDoors(randomIndex, randomIndex-3);
            break;
        }
        if (randomIndex+3 <= roomsCount-1 && isVisited[randomIndex+3]) {
            setDoors(randomIndex, randomIndex+3);
            break;
        }
        if (randomIndex%3!=2 && randomIndex+1 <= roomsCount-1 && isVisited[randomIndex+1]) {
            setDoors(randomIndex, randomIndex+1);
            break;
        }
        if (randomIndex%3!=0 && randomIndex-1 >= 0 && isVisited[randomIndex-1]) {
            setDoors(randomIndex, randomIndex-1);
            break;
        }
        }
        isVisited[randomIndex] = true;
    }
    minimap = graph;
    free(isVisited);
}

void nextRoom() {
    if (getAdventurer()->x == 1 && getAdventurer()->y == getCurrentRoom()->roomSize / 2) {
        map->currentRoom -= 1;
        getAdventurer()->y = getCurrentRoom()->roomSize / 2;
        getAdventurer()->x = getCurrentRoom()->roomSize - 2;
    } else if (getAdventurer()->x == getCurrentRoom()->roomSize-2 && getAdventurer()->y == getCurrentRoom()->roomSize / 2) {
        map->currentRoom += 1;
        getAdventurer()->y = getCurrentRoom()->roomSize / 2;
        getAdventurer()->x = 1;
    } else if (getAdventurer()->y == 1 && getAdventurer()->x == getCurrentRoom()->roomSize / 2) {
        map->currentRoom -= 3;
        getAdventurer()->y = getCurrentRoom()->roomSize - 2;
        getAdventurer()->x = getCurrentRoom()->roomSize / 2;
    } else if (getAdventurer()->y == getCurrentRoom()->roomSize-2 && getAdventurer()->x == getCurrentRoom()->roomSize / 2) {
        map->currentRoom += 3;
        getAdventurer()->y = 1;
        getAdventurer()->x = getCurrentRoom()->roomSize / 2;
    }
}

Room* getRoom(int roomIndex) {
    if (roomIndex < 0 || roomIndex >= map->roomsCount) {
        return nullptr;
    }
    return &map->rooms[roomIndex];
}

Room* getCurrentRoom() {
    return getRoom(map->currentRoom);
}

Map* getMap() {
    return map;
}

RoomType* getMinimap() {
    return minimap;
}

Cell** getRoomMap(int roomIndex) {
    Room *room = getRoom(roomIndex);
    if (room == nullptr) {
        return nullptr;
    }
    return room->roomMap;
}

Cell** getCurrentRoomMap() {
    return getRoomMap(map->currentRoom);
}

State mapService() {
    State state = MAP_STATE;
    if (!getMap()) {
        completeMap();
    }
    while (state == MAP_STATE) {
        state = move();
    }
    return state;
}

State move() {
    char input = getAndCheckMapInput();
    if (getCurrentRoomCell(getAdventurer()->y, getAdventurer()->x) == Enemy)
        return BATTLE_STATE;
    switch (input) {
        case 'w':
            setY(getAdventurer()->y-1);
            return MAP_STATE;
        case 'a':
            setX(getAdventurer()->x-1);
            return MAP_STATE;
        case 's':
            setY(getAdventurer()->y+1);
            return MAP_STATE;
        case 'd':
            setX(getAdventurer()->x+1);
            return MAP_STATE;
        case 'e':
            switch (getCurrentRoomCell(getAdventurer()->y, getAdventurer()->x)) {
                case Stuff:
                    return INVENTORY_STATE;
                case Treasure:
                    return INVENTORY_STATE;
                case Shop:
                    return SHOP_STATE;
                case NPC:
                    return DIALOG_STATE;
                case Portal:
                    completeMap();
                    return MAP_STATE;
                case Door:
                    nextRoom();
                    return MAP_STATE;
                default:
                    return MAP_STATE;
            }
            break;
        case 'i':
            return INVENTORY_STATE;
        default:
    }
}

int checkPossibleMovesMap(char *possibleInputs) {
    int count = 0;
    if (getAdventurer()->x-1 >= 0 && getCurrentRoomCell(getAdventurer()->y, getAdventurer()->x-1) != Wall) {
        possibleInputs[count++] = 'a';
    }
    if (getAdventurer()->y-1 >= 0 && getCurrentRoomCell(getAdventurer()->y-1, getAdventurer()->x) != Wall) {
        possibleInputs[count++] = 'w';
    }
    if (getAdventurer()->x+1 < getCurrentRoom()->roomSize  && getCurrentRoomCell(getAdventurer()->y, getAdventurer()->x+1) != Wall) {
        possibleInputs[count++] = 'd';
    }
    if (getAdventurer()->y+1 < getCurrentRoom()->roomSize && getCurrentRoomCell(getAdventurer()->y+1, getAdventurer()->x) != Wall) {
        possibleInputs[count++] = 's';
    }
    possibleInputs[count++] = 'e';
    possibleInputs[count++] = 'i';
    return count;
}

void completeMap() {
    map = nullptr;
    level++;
    initMap();
}