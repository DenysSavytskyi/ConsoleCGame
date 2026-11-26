#include "Controller.h"
#include <stdlib.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define MIN_TERMINAL_ROWS 40
#define MIN_TERMINAL_COLS 95

static int cursorX = 1;
static int cursorY = 1;
static int maxCursorY = 1;

void initializeController() {
    sleep_ms(1000);
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, FALSE);

    // int rows, cols;
    // getmaxyx(stdscr, rows, cols);
    // if (rows < MIN_TERMINAL_ROWS || cols < MIN_TERMINAL_COLS) {
    //     clear();
    //     mvprintw(0, 0, "Terminal is too small. Press F11 to maximize within 3 seconds.");
    //     refresh();
    //     sleep_ms(3000);
    //     resize_term(0, 0);
    //     getmaxyx(stdscr, rows, cols);
    //     if (rows < MIN_TERMINAL_ROWS || cols < MIN_TERMINAL_COLS) {
    //         clear();
    //         mvprintw(0, 0, "The window was not enlarged in time. Please restart and press F11.");
    //         mvprintw(1, 0, "Required minimum: %d rows x %d columns.", MIN_TERMINAL_ROWS, MIN_TERMINAL_COLS);
    //         mvprintw(2, 0, "Press any key to exit.");
    //         refresh();
    //         getch();
    //         endwin();
    //         exit(EXIT_FAILURE);
    //     }
    // }

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
    cursorX = 1;
    cursorY = 1;
    maxCursorY = 1;
    setCursor(cursorX, cursorY);
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
    cursorX = x;
    cursorY = y;
    if (cursorY > maxCursorY) maxCursorY = cursorY;
}

void clearLine() {
    clrtoeol();
    cursorX = 1;
}

int getCursorX() {
    return cursorX;
}

int getCursorY() {
    return cursorY;
}
int getMaxCursorY() {
    return maxCursorY;
}

void resetAllControllers() {
    clearConsole();
    setCursor(1, 1);
    cursorX = 1;
    cursorY = 1;
    maxCursorY = 1;
}

void putDelayedCharAt(char c, int x, int y, int charDelay) {
    setCursor(x, y);
    addch((unsigned char)c);
    cursorX++;
    sleep_ms(charDelay);
    refresh();
}

void putCharAt(char c, int x, int y) {
    putDelayedCharAt(c, x, y, 0);
}

void putChar(char c) {
    putDelayedCharAt(c, cursorX, cursorY, 0);
}

void putDelayedChar(char c, int charDelay) {
    putDelayedCharAt(c, cursorX, cursorY, charDelay);
}

void waitForInput() {
    getch();
}

void printHorizontalLine(WINDOW *win, int y) {
    printLeftAndRightTees(win, y);
    printOnlyHorizontalLine(win, y);
}

void printLeftAndRightTees(WINDOW *win, int y) {
    int height, width;
    getmaxyx(win, height, width);

    mvwaddch(win, y, 0, ACS_LTEE);
    mvwaddch(win, y, width - 1, ACS_RTEE);
}
void printOnlyHorizontalLine(WINDOW *win, int y) {
    int height, width;
    getmaxyx(win, height, width);

    for (int x = 1; x < width-1; x++) {
        mvwaddch(win, y, x, ACS_HLINE);
    }
}

void printVerticalLine(WINDOW *win, int x) {
    int height, width;
    getmaxyx(win, height, width);

    for (int y = 0; y < height; y++) {
        mvwaddch(win, y, x, ACS_VLINE);
    }
    mvwaddch(win, 0, x, ACS_TTEE);
    mvwaddch(win, height - 1, x, ACS_BTEE);
}

void printCross(WINDOW *win, int y, int x) {
    int height, width;
    getmaxyx(win, height, width);

    printVerticalLine(win, x);
    printHorizontalLine(win, y);
    mvwaddch(win, y, x, ACS_PLUS);
}
