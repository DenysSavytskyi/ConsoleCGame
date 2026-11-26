#include "Controller.h"
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void initializeController() {
    sleep_ms(1000);
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, FALSE);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_BLACK, COLOR_WHITE);
    }
}

void clearConsole() {
    erase();
    setCursor(1, 1);
    refresh();
}

void sleep_ms(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void setCursor(int x, int y) {
    move(y - 1, x - 1);
}

void resetAllControllers() {
    clearConsole();
}

void printInputOptions(int y, const char *title, const char *possibleInputs, int inputCount) {
    mvprintw(y, 0, "%s", title);
    for (int i = 0; i < inputCount; i++) {
        printw(" %c", possibleInputs[i]);
    }
    printw("\nEnter your move:\n");
    refresh();
}

char getInputChar() {
    char input = (char)getch();
    while (input == ERR) {
        input = (char)getch();
    }
    return input;
}

void printLeftAndRightTees(WINDOW *win, int y) {
    int width = getmaxx(win);

    mvwaddch(win, y, 0, ACS_LTEE);
    mvwaddch(win, y, width - 1, ACS_RTEE);
}
void printOnlyHorizontalLine(WINDOW *win, int y) {
    int width = getmaxx(win);

    for (int x = 1; x < width-1; x++) {
        mvwaddch(win, y, x, ACS_HLINE);
    }
}

void printVerticalLine(WINDOW *win, int x) {
    int height = getmaxy(win);

    for (int y = 0; y < height; y++) {
        mvwaddch(win, y, x, ACS_VLINE);
    }
    mvwaddch(win, 0, x, ACS_TTEE);
    mvwaddch(win, height - 1, x, ACS_BTEE);
}

void printCross(WINDOW *win, int y, int x) {
    printVerticalLine(win, x);
    printLeftAndRightTees(win, y);
    printOnlyHorizontalLine(win, y);
    mvwaddch(win, y, x, ACS_PLUS);
}
