#include "DialogService.h"
#include "../Modules/Adventurer.h"
#include "../Modules/Quests.h"
#include "../Controllers/DialogController.h"

State dialogService() {
    if (!getAdventurer()) {
        createAdventurer();
        return MAP_STATE;
    }
    resetDialog();
    interactWithNPC();
    return MAP_STATE;
}
