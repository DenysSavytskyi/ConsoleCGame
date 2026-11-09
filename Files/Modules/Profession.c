#include "Profession.h"

char *fighter[] = {
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

char *mage[] = {
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

char *thief[] = {
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

char *bard[] = {
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

char *cleric[] = {
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