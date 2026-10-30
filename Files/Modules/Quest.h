#ifndef GAME_QUEST_H
#define GAME_QUEST_H
#pragma once

#define QUEST_COUNT 3

typedef enum QuestType {
    KILL_QUEST,
    COLLECT_QUEST,
    STORY_QUEST
} QuestType;

typedef struct Quest {
    char title[60];
    char description[120];
    QuestType type;
    int progress;
    int required;
    int rewardMoney;
    int rewardXp;
    int active;
    int completed;
    int claimed;
} Quest;

void initializeQuests(Quest quests[QUEST_COUNT]);
void printQuests(const Quest quests[QUEST_COUNT]);
int allQuestsCompleted(const Quest quests[QUEST_COUNT]);
void updateKillQuests(Quest quests[QUEST_COUNT]);
void updateCollectQuest(Quest quests[QUEST_COUNT], int amount);
int claimQuest(Quest *quest, int *money, int *xp);

#endif
