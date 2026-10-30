#include "Quest.h"
#include <stdio.h>

void initializeQuests(Quest quests[QUEST_COUNT]) {
    quests[0] = (Quest){"A safer road", "Defeat three monsters on the road.", KILL_QUEST, 0, 3, 80, 60, 0, 0, 0};
    quests[1] = (Quest){"Old coins", "Collect five coins from defeated enemies.", COLLECT_QUEST, 0, 5, 120, 80, 0, 0, 0};
    quests[2] = (Quest){"The lost crown", "Reach the portal after completing the other quests.", STORY_QUEST, 0, 1, 250, 200, 0, 0, 0};
}

void printQuests(const Quest quests[QUEST_COUNT]) {
    printf("+-------------------- QUEST BOARD --------------------+\n");
    for (int i = 0; i < QUEST_COUNT; i++) {
        const Quest *quest = &quests[i];
        printf("%d. %-18s [%s]\n", i + 1, quest->title,
               quest->claimed ? "DONE" : (quest->active ? "ACTIVE" : "NEW"));
        printf("   %s\n", quest->description);
        printf("   Progress: %d/%d | Reward: %d gold, %d XP\n",
               quest->progress, quest->required, quest->rewardMoney, quest->rewardXp);
    }
    printf("+-----------------------------------------------------+\n");
}

int allQuestsCompleted(const Quest quests[QUEST_COUNT]) {
    for (int i = 0; i < QUEST_COUNT; i++) {
        if (!quests[i].claimed) return 0;
    }
    return 1;
}

void updateKillQuests(Quest quests[QUEST_COUNT]) {
    if (quests[0].active && !quests[0].claimed && quests[0].progress < quests[0].required)
        quests[0].progress++;
    if (quests[0].progress >= quests[0].required) quests[0].completed = 1;
}

void updateCollectQuest(Quest quests[QUEST_COUNT], int amount) {
    if (quests[1].active && !quests[1].claimed) {
        quests[1].progress += amount;
        if (quests[1].progress > quests[1].required) quests[1].progress = quests[1].required;
        if (quests[1].progress >= quests[1].required) quests[1].completed = 1;
    }
}

int claimQuest(Quest *quest, int *money, int *xp) {
    if (!quest->completed || quest->claimed) return 0;
    quest->claimed = 1;
    *money += quest->rewardMoney;
    *xp += quest->rewardXp;
    return 1;
}
