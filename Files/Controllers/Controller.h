//
// Created by User on 17.10.2026.
//

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#pragma once

void clearConsole();
void readInput(const char *prompt, char *buffer, int bufferSize);
char readCommand(const char *prompt, const char *allowed);
int readNumber(const char *prompt, int min, int max);
void waitForEnter();

#endif //GAME_CONTROLLER_H
