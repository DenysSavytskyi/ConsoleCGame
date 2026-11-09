//
// Created by User on 13.10.2026.
//

#include "MapController.h"
#include "../Services/Service.h"
#include <ncurses.h>

#include "Controller.h"

static int colorForCell(Cell cell) {
    switch (cell) {
        case Enemy:
            return 1;
        case NPC:
        case Shop:
        case Player:
            return 2;
        case Portal:
            return 3;
        case Stuff:
        case Treasure:
            return 4;
        default:
            return 0;
    }
}

static int colorForRoom(RoomType roomType) {
    switch (roomType) {
        case EnemyRoom:
        case BossRoom:
            return 1;
        case NPCRoom:
        case ShopRoom:
        case StartRoom:
            return 2;
        case TreasureRoom:
            return 4;
        default:
            return 0;
    }
}

void printRoom() {
    int roomSize = getCurrentRoom()->roomSize;
    //int terminalRows, terminalCols;
    //getmaxyx(stdscr, terminalRows, terminalCols);
    // if (terminalRows < roomSize + 4 || terminalCols < roomSize + 16) {
    //     mvprintw(0, 0, "Terminal too small. Please enlarge it.");
    //     refresh();
    //     return;
    // }

    WINDOW *roomWindow = newwin(roomSize, roomSize, 0, 0);
    for (int y = 0; y < roomSize; y++) {
        for (int x = 0; x < roomSize; x++) {
            Cell cell = getCurrentRoomCell(y, x);
            if (y == getAdventurer()->y && x == getAdventurer()->x) {
                cell = Player;
            }
            int color = colorForCell(cell);
            if (y==0 || y==roomSize-1 || x==0 || x==roomSize-1) {
                color = 6;
            }
            if (color) wattron(roomWindow, COLOR_PAIR(color));
            mvwaddch(roomWindow, y, x, (unsigned char)cell);
            if (color) wattroff(roomWindow, COLOR_PAIR(color));
        }
    }
    wrefresh(roomWindow);
    delwin(roomWindow);
}

void printMap() {
    printRoom();
    printMinimap();
}

void printMinimap() {
    int roomSize = getCurrentRoom()->roomSize;
    int startX = roomSize + 4;
    int terminalRows, terminalCols;
    getmaxyx(stdscr, terminalRows, terminalCols);
    // if (terminalRows < 9 || terminalCols < startX + 12) {
    //     mvprintw(0, 0, "Terminal too small. Please enlarge it.");
    //     refresh();
    //     return;
    // }
    WINDOW *minimapWindow = newwin(7, 9, 0, startX);
    box(minimapWindow, 0, 0);
    mvwprintw(minimapWindow, 0, 1, "Minimap");

    for (int i = 0; i < getMap()->roomsCount; i++) {
        int row = i / 3;
        int col = i % 3;
        int color = colorForRoom(getMinimap()[i]);
        if (color) wattron(minimapWindow, COLOR_PAIR(color));
        mvwaddch(minimapWindow, row * 2 + 1, col * 2 + 2, getMinimap()[i]);
        if (color) wattroff(minimapWindow, COLOR_PAIR(color));

        if (col < 2 && areRoomsConnected(i, i + 1)) {
            mvwaddch(minimapWindow, row * 2 + 1, col * 2 + 3, ACS_HLINE);
        }
        if (row < 2 && i + 3 < getMap()->roomsCount &&
            areRoomsConnected(i, i + 3)) {
            mvwaddch(minimapWindow, row * 2 + 2, col * 2 + 2, ACS_VLINE);
        }
    }
    wrefresh(minimapWindow);
    delwin(minimapWindow);
}

char getAndCheckMapInput() {
    while (1) {
        clearConsole();
        printMap();

        char possibleInputs[6]; //[w][a][s][d] [i] and terminator
        int inputCount = checkPossibleMovesMap(possibleInputs);
        possibleInputs[inputCount] = '\0';
        int statusY = getCurrentRoom()->roomSize + 3;
        mvprintw(statusY, 0, "Possible moves:");
        for (int i = 0; i < inputCount; i++) {
            printw(" %c", possibleInputs[i]);
        }
        printw("\nEnter your move:\n");
        refresh();

        char input = (char)getch();
        while (input == ERR) {
            input = (char)getch();
        }
        if (checkInput(possibleInputs, input)) {
            return input;
        }
    }
}
