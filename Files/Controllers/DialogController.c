#include "DialogController.h"

#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "Controller.h"

int currentLine = 0;

void printTyped(const char *text, int lineOfText, int startX) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            lineOfText++;
            setCursor(startX, lineOfText);
        } else {
            addch((unsigned char)text[i]);
            refresh();
            sleep_ms(CHARS_DELAY_MS);
        }
    }
}

static int getFrameWidth(int terminalWidth) {
    int width = terminalWidth / 2 - 2;
    if (width > 50) width = 50;
    if (width < 20) width = 20;
    return width;
}

static WINDOW *createFrame(bool left, int numberOfLines, int *textY, int *textX) {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    int width = getFrameWidth(cols);
    int height = numberOfLines + 2;
    int x = left ? 1 : cols - width - 2;

    // if (cols < width * 2 + 3 || height + 2 >= rows) {
    //     erase();
    //     mvprintw(0, 0, "Terminal too small. Please enlarge it.");
    //     refresh();
    //     waitForInput();
    //     currentLine = 0;
    //     erase();
    // } else if (currentLine + height + 1 >= rows) {
    //     erase();
    //     currentLine = 0;
    // }

    WINDOW *frame = newwin(height, width + 1, currentLine, x);
    box(frame, 0, 0);
    if (left) {
        mvwaddch(frame, 1, 0, ACS_RTEE);
    } else {
        mvwaddch(frame, 1, width, ACS_LTEE);
    }
    wrefresh(frame);
    *textY = currentLine + 1;
    *textX = x + 2;
    currentLine += height + 1;
    return frame;
}

void drawEmptyLeftFrame(int numberOfLines) {
    int textY, textX;
    WINDOW *frame = createFrame(true, numberOfLines, &textY, &textX);
    delwin(frame);
}

void drawEmptyRightFrame(int numberOfLines) {
    int textY, textX;
    WINDOW *frame = createFrame(false, numberOfLines, &textY, &textX);
    delwin(frame);
}

void printLeft(const char *text, int numberOfLines) {
    int textY, textX;
    WINDOW *frame = createFrame(true, numberOfLines, &textY, &textX);
    setCursor(textX, textY + 1);
    printTyped(text, textY + 1, textX);
    delwin(frame);
    sleep_ms(PHRASES_DELAY_MS);
}

void printRight(const char *text, int numberOfLines) {
    int textY, textX;
    WINDOW *frame = createFrame(false, numberOfLines, &textY, &textX);
    setCursor(textX, textY + 1);
    printTyped(text, textY + 1, textX);
    delwin(frame);
    sleep_ms(PHRASES_DELAY_MS);
}

void printRightInput(const char *text, char *buffer, int buffer_size, int numberOfLines) {
    int textY, textX;
    WINDOW *frame = createFrame(false, numberOfLines + 1, &textY, &textX);
    setCursor(textX, textY + 1);
    printTyped(text, textY + 1, textX);
    setCursor(textX, textY + 2);
    addstr("> ");
    refresh();
    echo();
    curs_set(1);
    getnstr(buffer, buffer_size - 1);
    noecho();
    curs_set(0);
    buffer[strcspn(buffer, "\n")] = '\0';
    delwin(frame);
}

void resetDialog() {
    erase();
    refresh();
    currentLine = 0;
}
