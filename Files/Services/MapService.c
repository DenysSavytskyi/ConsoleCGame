//
// Created by User on 17.10.2026.
//

#include "MapService.h"
#include <stdio.h>
#include <stdbool.h>
#include "../Controllers/Controller.h"
#include "../Controllers/MapController.h"
#include "../Modules/Adventurer.h"
#include "../Modules/Quest.h"
#include "EndService.h"

Map map;

Map* getMap() {
    return &map;
}

Map* generateMap () {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            map.map[i][j] = (i == 0 || j == 0 || i == MAP_HEIGHT - 1 || j == MAP_WIDTH - 1)
                ? Wall : Empty;
        }
    }
    for (int i = 2; i < MAP_HEIGHT - 2; i += 2) map.map[i][5] = Wall;
    map.map[1][3] = NPC;
    map.map[2][10] = Shop;
    map.map[8][18] = EnemyCell;
    map.map[4][14] = EnemyCell;
    map.map[9][20] = EnemyCell;
    map.map[9][3] = QuestBoard;
    map.map[1][MAP_WIDTH - 2] = Portal;
    return &map;
}

static void movePlayer(Adventurer *player, char command) {
    if (command == 'a') player->x--;
    if (command == 'd') player->x++;
    if (command == 'w') player->y--;
    if (command == 's') player->y++;
}

State mapService() {
    Adventurer *player = getAdventurer();
    if (!player) return DIALOG_STATE;
    if (map.map[0][0] == Empty) generateMap();
    while (true) {
        clearConsole();
        printMap(&map, player);
        printf("\nHP %d/%d | Level %d | Gold %d | XP %d\n",
               player->hp, player->hpMax, player->level, player->money, player->xp);
        printf("WASD move | I inventory | Q quests | E interact | X exit\n");
        char command = readCommand("> ", "wasdqiex");
        if (command == 'i') return INVENTORY_STATE;
        if (command == 'q') return QUEST_STATE;
        if (command == 'x') return END_STATE;
        if (command == 'e') {
            Cell cell = map.map[player->y][player->x];
            if (cell == EnemyCell) return BATTLE_STATE;
            if (cell == Shop) return SHOP_STATE;
            if (cell == NPC || cell == QuestBoard) return DIALOG_STATE;
            if (cell == Portal) {
                if (player->quests[0].claimed && player->quests[1].claimed) {
                    player->quests[2].active = 1;
                    player->quests[2].progress = 1;
                    player->quests[2].completed = 1;
                    claimQuest(&player->quests[2], &player->money, &player->xp);
                    setEnding(GOOD_ENDING);
                    return END_STATE;
                }
                printf("The portal is sealed. Complete every quest first.\n");
                waitForEnter();
            }
            continue;
        }
        int oldX = player->x;
        int oldY = player->y;
        movePlayer(player, command);
        if (map.map[player->y][player->x] == Wall) {
            player->x = oldX;
            player->y = oldY;
        }
    }
}