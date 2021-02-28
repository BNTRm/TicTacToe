#pragma once

namespace MyLib {

    enum Cell { EMPTY = '-', CROSS = 'X', ZERO = '0' };
    enum GameProgress { IN_PROGRESS, HUMAN_WON, AI_WON, DRAW };

    struct Field {
        Cell** ppCells;
        size_t size, goal, turns = 0;
        Cell human, aI;
        bool humanFirst;
        GameProgress progress;
    };

    const char LITERAL_Y_AXIS[20] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T' };

    struct Coord {
        size_t x, y;
    };

    void clearScr();
    int myrand();
    int yIndexByChar(char ch);

    void printField(const Field& f);


    void updateScreen(Field& f);

}