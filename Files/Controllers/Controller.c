//
// Created by User on 17.10.2026.
//

#include "Controller.h"
#include <stdlib.h>
#include <stdio.h>

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    fflush(stdout);
}
