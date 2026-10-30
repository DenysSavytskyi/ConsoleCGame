#include "BattleService.h"
#include <stdio.h>
#include <string.h>
#include "../Controllers/Controller.h"
#include "../Modules/Adventurer.h"
#include "../Modules/Enemy.h"
#include "../Modules/Quest.h"
#include "InventoryService.h"
#include "MapService.h"
#include "EndService.h"

State battleService() {
    Adventurer *player = getAdventurer();
    if (!player) return DIALOG_STATE;
    Enemy enemy = {"Goblin scout", 35 + player->level * 5, 7 + player->level, FIREBALL, player->x, player->y};
    clearConsole();
    printf("A %s blocks your path!\n", enemy.name);
    while (enemy.hp > 0 && player->hp > 0) {
        printf("\n%s HP: %d | Your HP: %d/%d\n", enemy.name, enemy.hp, player->hp, player->hpMax);
        printf("A attack | P potion | R run\n");
        char command = readCommand("> ", "apr");
        if (command == 'a') {
            int damage = player->damage + player->level;
            enemy.hp -= damage;
            printf("You strike for %d damage.\n", damage);
        } else if (command == 'p') {
            if (!useHealthPotion(player->inventory, &player->hp, player->hpMax))
                printf("No health potion available.\n");
            else
                printf("You drink a potion.\n");
        } else {
            printf("You escape back to the road.\n");
            waitForEnter();
            return MAP_STATE;
        }
        if (enemy.hp > 0) {
            player->hp -= enemy.damage;
            printf("The goblin hits you for %d damage.\n", enemy.damage);
        }
    }
    if (player->hp <= 0) {
        player->hp = 0;
        setEnding(BAD_ENDING);
        return END_STATE;
    }
    player->money += 35;
    addExperience(player, 45);
    updateKillQuests(player->quests);
    updateCollectQuest(player->quests, 1);
    getMap()->map[player->y][player->x] = Empty;
    printf("\nVictory! You found 35 gold and a quest coin.\n");
    waitForEnter();
    return MAP_STATE;
}
