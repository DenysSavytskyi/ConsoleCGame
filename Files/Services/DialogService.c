#include "DialogService.h"

#include <stdio.h>

#include "../Modules/Adventurer.h"
#include <stdlib.h>


State dialogService() {
    if (!getAdventurer()) {
        createAdventurer();
        return MAP_STATE;
    }
    printf("You already have a character.\n");
    return END_STATE;
}
