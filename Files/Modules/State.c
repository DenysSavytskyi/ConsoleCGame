#include "State.h"

static State previousState = MAP_STATE;

void setPreviousState(State state) {
    previousState = state;
}

State getPreviousState() {
    return previousState;
}