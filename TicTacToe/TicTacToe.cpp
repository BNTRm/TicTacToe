
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <Windows.h>
#include "MyLib.h"
#include "WinCheck.h"
#include "AI.h"

using namespace std;
using namespace MyLib;

//=======================================================

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Field f;

void setGoalConsideringSize() {
    bool condition;
    short min, max;

    switch (f.size) {
        case 3: {
            f.goal = 3;
            return;
        }
        case 4: {
            min = 3;
            max = 4;
            break;
        }
        case 5: {
            min = 3;
            max = 5;
            break;
        }
        case 6: {
            min = 4;
            max = 5;
            break;
        }
        default: {
            f.goal = 5;
            return;
        }
    }

    while (f.goal < min || f.goal > max) {
        clearScr();

        cout << "Enter goal (" << min << "-" << max << "): ";
        cin >> f.goal;
    }
}

void initField() {
    SetConsoleTextAttribute(hConsole, 6);

    while (f.size < 3 || f.size > 20) {
        clearScr();

        cout << "Enter field size (3-20): ";
        cin >> f.size;
    }

    setGoalConsideringSize();

    f.ppCells = new Cell * [f.size];
    
    for (size_t y = 0; y < f.size; y++) {
        f.ppCells[y] = new Cell[f.size];
    }

    for (size_t y = 0; y < f.size; y++) {
        for (size_t x = 0; x < f.size; x++) {
            f.ppCells[y][x] = EMPTY;
        }
    }

    if (myrand() > 50) {
        f.human = CROSS;
        f.aI = ZERO;
        f.humanFirst = true;
    }
    else {
        f.human = ZERO;
        f.aI = CROSS;
        f.humanFirst = false;
    }

    f.progress = IN_PROGRESS;
}

void deinitField() {
    for (size_t y = 0; y < f.size; y++) {
        delete[] f.ppCells[y];
    }

    delete[] f.ppCells;
    f.ppCells = nullptr;
}

Coord getHumanCoord() {
    Coord c;
    string input;
    do {
        updateScreen(f);

        SetConsoleTextAttribute(hConsole, 14);
        cout << "Enter cell: ";
        cin >> input;

        stringstream ss(input);

        char yLetter;

        ss >> yLetter >> c.y;
        c.x = yLetter;

        c.x = yIndexByChar(yLetter);
    } while (c.y < 1 || c.y > f.size || c.x < 1 || c.x > f.size || f.ppCells[c.y - 1][c.x - 1] != EMPTY);

    c.x--;
    c.y--;

    return c;
}

void printWonOrDraw() {
    SetConsoleTextAttribute(hConsole, 10);
    if (f.progress == DRAW) {
        cout << "DRAW!" << endl;
    }
    else if (f.progress == HUMAN_WON) {
        cout << "HUMAN WON!" << endl;
    }
    else if (f.progress == AI_WON) {
        cout << "AI WON!" << endl;
    }

    SetConsoleTextAttribute(hConsole, 8);
}

//=======================================================

int main() {
    initField();

    updateScreen(f);

    bool humansTurn = (f.humanFirst) ? true : false;

    Coord c;

    while (f.progress == IN_PROGRESS) {
        if (humansTurn) {
            c = getHumanCoord();

            f.ppCells[c.y][c.x] = f.human;

            humansTurn = false;
        }
        else {
            c = AI::getAICoord(f);

            f.ppCells[c.y][c.x] = f.aI;

            humansTurn = true;
        }

        f.turns++;

        updateScreen(f);

        if (!WinCheck::check(f)) {
            if (f.turns == f.size * f.size) {
                f.progress = DRAW;
            }
        }
    }

    printWonOrDraw();

    cin.get();
    deinitField();
}