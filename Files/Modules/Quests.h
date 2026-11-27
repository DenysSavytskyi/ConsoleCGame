#ifndef GAME_QUESTS_H
#define GAME_QUESTS_H

typedef enum QuestType {
    KILL_ENEMIES,
    FIND_ITEM,
    GIVE_MONEY,
    QUESTS_COUNT
} QuestType;

typedef enum QuestStatus {
    IN_PROGRESS,
    NOT_TAKEN,
    COMPLETED
} QuestStatus;

typedef struct Quest {
    QuestType type;
    int count;
    QuestStatus status;
} Quest;

void generateNPC(void);
void resetNPCQuest(void);
void spawnPendingQuestItem(void);
void interactWithNPC(void);

#endif
