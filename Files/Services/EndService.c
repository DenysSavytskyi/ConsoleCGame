#include "EndService.h"

#include <ncurses.h>

State endService() {
    refresh();
    getchar();
    return END_STATE;
}
