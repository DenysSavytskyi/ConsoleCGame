#include "Quests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Controllers/DialogController.h"
#include "../Modules/Adventurer.h"
#include "../Modules/EnemyEntity.h"
#include "../Modules/ItemGenerator.h"
#include "../Services/InventoryService.h"
#include "../Services/MapService.h"
#include "../Services/Service.h"

typedef void (*QuestDialogueFunction)(void);
typedef int (*QuestCheckFunction)(void);
typedef int (*QuestRewardFunction)(void);

static Quest quest = {KILL_ENEMIES, 0, NOT_TAKEN};
static int rewardClaimed = 0;
static int pendingQuestItem = 0;

static void offerQuest(const char *description) {
    char choice[8];
    while (1) {
        printLeft(description, 2);
        printRight("1. Yes, I'll take this quest.\n2. I'll think about it.", 2);
        printRightInput("Your choice:", choice, sizeof(choice), 1);
        if (choice[0] == '1' || choice[0] == '2') {
            break;
        }
        resetDialog();
    }

    if (choice[0] == '1') {
        quest.status = IN_PROGRESS;
        printLeft("Thank you. I knew you'd help.", 1);
    } else {
        printLeft("All right. I'll be here\nif you change your mind.", 2);
    }
}

static void offerKillQuest(void) {
    char description[160];
    snprintf(description, sizeof(description),
        "Defeat all %d non-boss enemies.\nBring me proof for a reward.",
        quest.count);
    offerQuest(description);
}

static void offerFindItemQuest(void) {
    offerQuest("I lost a keepsake in these rooms.\nFind it and bring it back to me.");
}

static void offerMoneyQuest(void) {
    char description[160];
    snprintf(description, sizeof(description),
        "Bring me %d coins for supplies.\nI'll reward you in return.",
        quest.count);
    offerQuest(description);
}

static int checkKillQuest(void) {
    return getNonBossEnemyCount() == 0;
}

static int checkFindItemQuest(void) {
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        ItemAndType *item = getItem(i);
        if (item != NULL && item->type == QUEST_ITEM) {
            return 1;
        }
    }
    return 0;
}

static int checkMoneyQuest(void) {
    return getAdventurer()->money >= quest.count;
}

static void consumeQuestItem(void) {
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        ItemAndType *item = getItem(i);
        if (item != NULL && item->type == QUEST_ITEM) {
            item->type = ITEM_NULL;
            return;
        }
    }
}

static const char *getAbilityName(Ability ability) {
    switch (ability) {
        case BLOCK:
            return "Block";
        case FIREBALL:
            return "Fireball";
        case STEAL:
            return "Steal";
        case SMOKE_BOMB:
            return "Smoke Bomb";
        case CLONE:
            return "Clone";
    }
    return "Unknown";
}

static int chooseAbilityReward(void) {
    Ability availableAbilities[CLONE + 1];
    int availableCount = 0;
    char choices[192] = "Choose one new ability:\n";
    size_t used = strlen(choices);

    for (int ability = BLOCK; ability <= CLONE; ability++) {
        if (hasAbility((Ability)ability)) {
            continue;
        }
        availableAbilities[availableCount] = (Ability)ability;
        int written = snprintf(choices + used, sizeof(choices) - used,
            "%d. %s\n", availableCount + 1, getAbilityName((Ability)ability));
        if (written < 0 || (size_t)written >= sizeof(choices) - used) {
            return 0;
        }
        used += (size_t)written;
        availableCount++;
    }

    if (availableCount == 0) {
        printLeft("You already know every ability.", 1);
        return 1;
    }

    char choice[8];
    int numberOfLines = availableCount + 1;
    while (1) {
        printLeft(choices, numberOfLines);
        printRightInput("Choose an ability:", choice, sizeof(choice), 1);
        if (choice[0] >= '1' && choice[0] <= '0' + availableCount) {
            break;
        }
        resetDialog();
    }

    return addAbility(availableAbilities[choice[0] - '1']);
}

static int rewardKillQuest(void) {
    if (!chooseAbilityReward()) {
        printLeft("I couldn't grant that ability.\nPlease speak to me again.", 2);
        return 0;
    }
    printLeft("You earned a new ability.\nUse it well!", 2);
    return 1;
}

static int rewardFindItemQuest(void) {
    if (!rewardKillQuest()) {
        return 0;
    }
    consumeQuestItem();
    return 1;
}

static int rewardMoneyQuest(void) {
    int hasInventorySpace = 0;
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        ItemAndType *item = getItem(i);
        if (item != NULL && item->type == ITEM_NULL) {
            hasInventorySpace = 1;
            break;
        }
    }
    if (!hasInventorySpace) {
        printLeft("Your inventory is full.\nMake room and come back.", 2);
        return 0;
    }

    if (!chooseAbilityReward()) {
        printLeft("I couldn't grant that ability.\nPlease speak to me again.", 2);
        return 0;
    }

    ItemAndType rewardItem = generateRandomItem();
    if (!addItem(rewardItem)) {
        printLeft("Your inventory is full.\nMake room and come back.", 2);
        return 0;
    }
    getAdventurer()->money -= quest.count;
    printLeft("New ability and random item earned.\nThank you!", 2);
    return 1;
}

static QuestDialogueFunction questDialogues[QUESTS_COUNT] = {
    offerKillQuest,
    offerFindItemQuest,
    offerMoneyQuest
};

static QuestCheckFunction questChecks[QUESTS_COUNT] = {
    checkKillQuest,
    checkFindItemQuest,
    checkMoneyQuest
};

static QuestRewardFunction questRewards[QUESTS_COUNT] = {
    rewardKillQuest,
    rewardFindItemQuest,
    rewardMoneyQuest
};

void generateNPC(void) {
    quest.type = (QuestType)getRandom(0, QUESTS_COUNT - 1);
    quest.status = NOT_TAKEN;
    rewardClaimed = 0;
    pendingQuestItem = 0;
    switch (quest.type) {
        case KILL_ENEMIES:
            quest.count = getNonBossEnemyCount();
            break;
        case FIND_ITEM: {
            quest.count = 1;
            pendingQuestItem = 1;
            break;
        }
        case GIVE_MONEY:
            quest.count = 10 * getLevel();
            break;
        case QUESTS_COUNT:
            break;
    }
}

void resetNPCQuest(void) {
    quest.status = NOT_TAKEN;
    rewardClaimed = 0;
    pendingQuestItem = 0;
}

void spawnPendingQuestItem(void) {
    if (!pendingQuestItem) {
        return;
    }

    ItemAndType questItem = {0};
    questItem.type = QUEST_ITEM;
    if (spawnQuestItem(questItem)) {
        pendingQuestItem = 0;
    }
}

static void printWaitingLine(void) {
    static const char *lines[] = {
        "I'm still here, still waiting.",
        "How much longer will you be?",
        "Is this really so difficult?"
    };
    printLeft(lines[getRandom(0, 2)], 1);
}

void interactWithNPC(void) {
    if (quest.status == NOT_TAKEN) {
        questDialogues[quest.type]();
        return;
    }

    if (quest.status == IN_PROGRESS) {
        if (!questChecks[quest.type]()) {
            printWaitingLine();
            return;
        }
        quest.status = COMPLETED;
    }

    if (quest.status == COMPLETED && !rewardClaimed) {
        rewardClaimed = questRewards[quest.type]();
    } else if (quest.status == COMPLETED) {
        printLeft("Thank you again for your help.", 1);
    }
}
