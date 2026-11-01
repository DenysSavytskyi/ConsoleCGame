#include "DialogService.h"

#include "../Modules/Adventurer.h"
#include <stdlib.h>
#include <ncurses.h>


State dialogService() {
    if (!getAdventurer()) {
        createAdventurer();
        return MAP_STATE;
    }
    printw("You already have a character.\n");
    refresh();
    return END_STATE;
}
