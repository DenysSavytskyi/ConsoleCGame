#include "EndController.h"

static EndState endState = UNKNOWN_ERROR;

void setEndState(EndState state) {
    endState = state;
}

void printEnd() {
    clear();
    int x,y;
    getmaxyx(stdscr,y,x);
    WINDOW* win = newwin(y,x,0,0);
    box(win,0,0);
    switch (endState) {
        case UNKNOWN_ERROR:
            mvwprintw(win, y/2, x/2-10, "Unknown error occurred!");
            break;
        case GAME_OVER:
            mvwprintw(win, y/2, x/2-5, "Game Over!");
            break;
        case VICTORY:
            mvwprintw(win, y/2, x/2-5, "Victory!");
            break;
    }
    wrefresh(win);
    getchar();
    delwin(win);
}
