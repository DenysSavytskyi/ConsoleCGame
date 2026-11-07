#include "BattleController.h"

#define INFO_Y 13
#define INFO_X 27
#define OPTIONS_Y 13
#define OPTIONS_X 27


static BattleState battleState = OPTIONS;

BattleState getBattleState() {
    return battleState;
}

void setBattleState(BattleState newState) {
    battleState = newState;
}

char getAndCheckBattleInput() {
    while (1) {
        clearConsole();
        printBattle();
        int inputsCount = 0;
        switch (battleState) {
            case OPTIONS:
                inputsCount = 4;
                break;
            case POTION:
                inputsCount = getItemCount(POTION);
                break;
            case ABILITIES:
                inputsCount = getAbilityCount();
                break;
        }
        char possibleInputs[inputsCount + 1];
        possibleInputs[inputsCount] = '\0';
        int inputCount = checkPossibleMovesBattle(possibleInputs);
        mvprintw(OPTIONS_Y + INFO_Y + 1, 0, "Possible moves:\n");
        for (int i = 0; i < inputCount; i++) {
            printw(" %c", possibleInputs[i]);
        }
        printw("\nEnter your move:\n");
        refresh();

        char input = (char)getch();
        while (input == ERR) {
            input = (char)getch();
        }
        if (checkInput(possibleInputs, input)) {
            return input;
        }
    }
}
void printCross(WINDOW *infoWin) {
    int x = INFO_X / 2;
    int y = INFO_Y - 3;

    for (int i = 0; i < INFO_Y; i++) {
        mvwaddch(infoWin, i, x, ACS_VLINE);
    }
    for (int j = 0; j < INFO_X; j++) {
        mvwaddch(infoWin, y, j, ACS_HLINE);
    }
    mvwaddch(infoWin, y, x, ACS_PLUS);
    mvwaddch(infoWin, 0, x, ACS_TTEE);
    mvwaddch(infoWin, INFO_Y-1, x, ACS_BTEE);
    mvwaddch(infoWin, y, 0, ACS_LTEE);
    mvwaddch(infoWin, y, INFO_X-1, ACS_RTEE);
}
void printBattle() {
    WINDOW *win = newwin(OPTIONS_Y+INFO_X, INFO_X, 0, 0);
    WINDOW *infoWin = derwin(win, INFO_Y, INFO_X, 0, 0);
    box(infoWin, 0, 0);
    printCross(infoWin);
    for (int i = 0; i < 9; i++) {
        mvwprintw(infoWin, 1 + i, 1, "%s", getASCII(getAdventurer()->profession, i));
    }
    mvwprintw(infoWin, INFO_Y-2, 1, "hp: %d/%d", getAdventurer()->hp, getAdventurer()->hpMax);
    mvwprintw(infoWin, INFO_Y-2, INFO_X/2+1, "hp: 100/100"); //TODO: replace with actual enemy hp
    wrefresh(infoWin);

    WINDOW *optionsWin = derwin(win, OPTIONS_Y, OPTIONS_X, INFO_Y+1, 0);
    box(optionsWin, 0, 0);
    int lineCount = 1;
    if (battleState == OPTIONS) {
        mvwprintw(optionsWin, lineCount++, 1, "Options: ");
        mvwprintw(optionsWin, lineCount++, 1, "0. Attack");
        if (getItemCount(POTION) > 0) {
            mvwprintw(optionsWin, lineCount++, 1, "1. Potions");
        }
        mvwprintw(optionsWin, lineCount++, 1, "2. Abilities");
        mvwprintw(optionsWin, lineCount++, 1, "3. Run Away");
    } else if (battleState == POTIONS) {
        mvwprintw(optionsWin, lineCount++, 1, "Potions: ");
        for (int i = 0; i < getItemCount(POTION); i++) {
            Potion *potion = getPotion(i);
            mvwprintw(optionsWin, lineCount++, 1, "%d. %s (%d)", i, potion->name, potion->amount);
        }
    } else if (battleState == ABILITIES) {
        mvwprintw(optionsWin, lineCount++, 1, "Abilities: ");
        for (int i = 0; i < getAbilityCount(); i++) {
            Ability *ability = &getAdventurer()->abilities[i];
            char* abilityName = "UNKNOWN";
            switch (*ability) {
                case BLOCK:
                    abilityName = "Block";
                    break;
                case FIREBALL:
                    abilityName = "Fireball";
                    break;
                case STEAL:
                    abilityName = "Steal";
                    break;
                case SMOKE_BOMB:
                    abilityName = "Smoke Bomb";
                    break;
                case CLONE:
                    abilityName = "Clone";
                    break;
            }
            mvwprintw(optionsWin, lineCount++, 1, "%d. %s", i, abilityName);
        }
    }
    wrefresh(optionsWin);
    delwin(infoWin);
    delwin(optionsWin);
    delwin(win);
}
