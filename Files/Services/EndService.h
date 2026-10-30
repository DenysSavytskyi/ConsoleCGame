#ifndef END_SERVICE_H
#define END_SERVICE_H
#pragma once

#include "../State.h"

State endService();
typedef enum Ending {
    NO_ENDING,
    GOOD_ENDING,
    BAD_ENDING,
    QUIT_ENDING
} Ending;
void setEnding(Ending ending);

#endif
