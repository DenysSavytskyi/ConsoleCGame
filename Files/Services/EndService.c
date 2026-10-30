#include "EndService.h"
#include <stdio.h>
#include "../Controllers/Controller.h"
#include "../Modules/Adventurer.h"

static Ending currentEnding = NO_ENDING;

State endService() {
    Adventurer *player = getAdventurer();
    if (currentEnding == NO_ENDING)
        currentEnding = player && player->hp <= 0 ? BAD_ENDING : QUIT_ENDING;
    clearConsole();
    if (currentEnding == GOOD_ENDING) {
        printf("=======================================================\n");
        printf("                 THE CROWN OF DAWN                     \n");
        printf("You completed every quest and saved the valley.        \n");
        printf("                 GOOD ENDING                            \n");
        printf("=======================================================\n");
    } else if (currentEnding == BAD_ENDING) {
        printf("=======================================================\n");
        printf("                    YOU DIED                           \n");
        printf("The road won this time.                                \n");
        printf("                 BAD ENDING                             \n");
        printf("=======================================================\n");
    } else {
        printf("The adventure ends here.\n");
    }
    printf("\n1. Restart adventure\n2. Quit\n");
    int choice = readNumber("> ", 1, 2);
    if (choice == 1) {
        resetAdventurer();
        currentEnding = NO_ENDING;
        return DIALOG_STATE;
    }
    return END_STATE;
}

void setEnding(Ending ending) {
    currentEnding = ending;
}
