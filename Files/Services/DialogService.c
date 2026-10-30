#include "DialogService.h"

#include <stdio.h>

#include "../Modules/Adventurer.h"
#include "../Modules/Quest.h"
#include "../Controllers/Controller.h"
#include "MapService.h"
#include <stdlib.h>


State dialogService() {
    if (!getAdventurer()) {
        createAdventurer();
        if (!getAdventurer()) {
            printLeft("The character could not be created.", 1);
        }
        generateMap();
        return MAP_STATE;
    }
    Adventurer *player = getAdventurer();
    clearConsole();
    printf("+------------------------ NPC -------------------------+\n");
    printf("Captain Mira: The road is dangerous, but you can make it safe.\n\n");
    if (!player->quests[0].active) {
        player->quests[0].active = 1;
        printf("Quest accepted: %s\n", player->quests[0].title);
    }
    if (player->quests[0].completed && !player->quests[0].claimed) {
        claimQuest(&player->quests[0], &player->money, &player->xp);
        addExperience(player, 0);
        printf("Captain Mira rewards you for clearing the road.\n");
    }
    if (player->quests[0].claimed && !player->quests[1].active) {
        player->quests[1].active = 1;
        printf("New quest: %s\n", player->quests[1].title);
    }
    if (player->quests[1].completed && !player->quests[1].claimed) {
        claimQuest(&player->quests[1], &player->money, &player->xp);
        addExperience(player, 0);
        printf("Captain Mira rewards your collection of coins.\n");
    }
    if (player->quests[1].claimed && !player->quests[2].active) {
        player->quests[2].active = 1;
        printf("New quest: %s\n", player->quests[2].title);
    }
    printf("\nPress Enter to return to the map.");
    waitForEnter();
    return MAP_STATE;
}
