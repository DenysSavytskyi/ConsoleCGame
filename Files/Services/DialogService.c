#include "DialogService.h"
#pragma once

State dialogService() {
    if (!getAdventurer()) {
        createAdventurer();
        return MAP_STATE;
    }
    return END_STATE;
}
