#include "DialogService.h"

State dialogService() {
    if (!getAdventurer()) {
        createAdventurer();
        return MAP_STATE;
    }
    printw("unknown error occurred!");
    refresh();
    return END_STATE;
}
