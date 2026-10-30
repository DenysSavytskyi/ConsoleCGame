//
// Created by User on 20.10.2026.
//

#include "Service.h"

bool checkInput(const char *possibleInputs, char input) {
    if (possibleInputs == nullptr)
        return false;
    for (int i = 0; possibleInputs[i] != '\0'; i++) {
        if (input == possibleInputs[i]) {
            return true;
        }
    }
    return false;
}

int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}