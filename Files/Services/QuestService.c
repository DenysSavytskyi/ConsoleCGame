#include "QuestService.h"
#include <stdio.h>
#include "../Controllers/Controller.h"
#include "../Modules/Adventurer.h"
#include "../Modules/Quest.h"

State questService() {
    Adventurer *player = getAdventurer();
    if (!player) return DIALOG_STATE;
    clearConsole();
    printQuests(player->quests);
    printf("\nVisit the captain at N to accept quests and claim rewards.\n");
    waitForEnter();
    return MAP_STATE;
}
