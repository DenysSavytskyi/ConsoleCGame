#include "Profession.h"

const char *fighter[] = {
    "   /##\\     ",
    "  | ## |    ",
    " /|{==}|\\   ",
    "/ | ## | |  ",
    "| |[##]|-+--",
    "\\ | ## |    ",
    " \\+----+    ",
    "  / /\\ \\    ",
    " /_/  \\_\\   "
};

char* getASCII(Profession profession, int line) {
    switch (profession) {
        case FIGHTER:
            return fighter[line];
        case MAGE:
            return "Mage ASCII Art";
        case THIEF:
            return "Thief ASCII Art";
        case BARD:
            return "Bard ASCII Art";
        case CLERIC:
            return "Cleric ASCII Art";
    }
}