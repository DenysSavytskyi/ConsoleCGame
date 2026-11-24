#include "EnemyEntity.h"
#include "../Services/MapService.h"
#include "Adventurer.h"

static EnemyEntity* enemies = NULL;
static int enemiesCount = 0;

void generateEnemy(int roomIndex, bool isBoss) {
    enemies = realloc(enemies, sizeof(*enemies) * (enemiesCount + 1));
    int hp = 1;
    switch ((EnemyType)getRandom(0,7)) {
        case GOBLIN:
            enemies[enemiesCount].type = GOBLIN;
            hp = 20;
            break;
        case ORC:
            enemies[enemiesCount].type = ORC;
            hp = 25;
            break;
        case TROLL:
            enemies[enemiesCount].type = TROLL;
            hp = 30;
            break;
        case SKELETON:
            enemies[enemiesCount].type = SKELETON;
            hp = 15;
            break;
        case ZOMBIE:
            enemies[enemiesCount].type = ZOMBIE;
            hp = 20;
            break;
        case VAMPIRE:
            enemies[enemiesCount].type = VAMPIRE;
            hp = 25;
            break;
        case WITCH:
            enemies[enemiesCount].type = WITCH;
            hp = 30;
            break;
        case DEMON:
            enemies[enemiesCount].type = DEMON;
            hp = 40;
            break;
    }
    int bossHp = isBoss*getLevel()*2*hp;
    enemies[enemiesCount].hp = (bossHp!=0)?bossHp:hp * getLevel();
    enemies[enemiesCount].isBoss = isBoss;
    enemies[enemiesCount].maxHp = enemies[enemiesCount].hp;
    enemies[enemiesCount].roomIndex = roomIndex;
    enemiesCount++;
}

int getEnemiesCount() {
    return enemiesCount;
}

int getEnemyDamage(int roomIndex) {
    if (enemies == NULL) {
        return 0;
    }
    for (int i = 0; i < enemiesCount; i++) {
        if (enemies[i].roomIndex == roomIndex) {
            switch (enemies[i].type) {
                case GOBLIN:
                    return 5;
                case ORC:
                    return 10;
                case TROLL:
                    return 15;
                case SKELETON:
                    return 7;
                case ZOMBIE:
                    return 8;
                case VAMPIRE:
                    return 12;
                case WITCH:
                    return 9;
                case DEMON:
                    return 20;
            }
        }
    }
    return 0;
}

int attackEnemy(int roomIndex, int damage) {
    if (enemies == NULL) {
        return -1;
    }
    for (int i = 0; i < enemiesCount; i++) {
        if (enemies[i].roomIndex == roomIndex) {
            enemies[i].hp -= damage;
            if (enemies[i].hp <= 0) {
                getRewards(enemies[i].maxHp);
                removeEnemyFromMap(enemies[i].isBoss);
                for (int j = i; j < enemiesCount - 1; j++) {
                    enemies[j] = enemies[j + 1];
                }
                enemiesCount--;
                enemies = realloc(enemies, sizeof(EnemyEntity) * enemiesCount);
                return 1; // Enemy defeated
            }
            return 0; // Enemy still alive
        }
    }
    return -1; // Enemy not found
}

int getEnemyHp(int roomIndex) {
    if (enemies == NULL) {
        return 0;
    }
    for (int i = 0; i < enemiesCount; i++) {
        if (enemies[i].roomIndex == roomIndex) {
            return enemies[i].hp;
        }
    }
    return 0;
}

int getEnemyMaxHp(int roomIndex) {
    if (enemies == NULL) {
        return 0;
    }
    for (int i = 0; i < enemiesCount; i++) {
        if (enemies[i].roomIndex == roomIndex) {
            return enemies[i].maxHp;
        }
    }
    return 0;
}

void freeEnemies() {
    free(enemies);
    enemies = NULL;
    enemiesCount = 0;
}