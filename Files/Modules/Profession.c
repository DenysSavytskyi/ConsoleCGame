#include "Profession.h"

static char *fighter[] = {
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

static char *mage[] = {
    "     /\\     ",
    "    /  \\    ",
    "   /    \\   ",
    "  /______\\  ",
    "  | (o.o)|  ",
    " /|  ##  |\\*",
    "/ |  ##  | |",
    "  +==++==+  ",
    "  /______\\  "
};

static char *thief[] = {
    "   /----\\   ",
    "  /  %%  \\  ",
    "  | (..) |  ",
    "  \\  --  /  ",
    "  /| OO |\\  ",
    " / | OO | \\ ",
    "   +====+  X",
    "   /    \\ / ",
    "  /______\\  "
};

static char *bard[] = {
    "    /\\/\\    ",
    "   ( . .)   ",
    "   /\\--/\\   ",
    "  /| #  |\\  ",
    " / | $  | \\ ",
    "(  | ## |  )",
    " \\ \\/--\\/ / ",
    "  \\______/  ",
    "  /_/  \\_\\  "
};

static char *cleric[] = {
    "    +--+    ",
    "   /+--+\\   ",
    "   | v v|   ",
    "  /++--++\\  ",
    " /|  ##  |\\ ",
    "| | #### | |",
    " \\|  ##  |/ ",
    "  +-+--+-+  ",
    "   /_||_\\   "
};

char* getASCII(Profession profession, int line) {
    switch (profession) {
        case FIGHTER:
            return fighter[line];
        case MAGE:
            return mage[line];
        case THIEF:
            return thief[line];
        case BARD:
            return bard[line];
        case CLERIC:
            return cleric[line];
        default:
            return "ASCII  IMAGE";
    }
}