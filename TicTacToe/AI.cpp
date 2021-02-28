
#include "MyLib.h"

using namespace MyLib;

// AI будет пытаться выиграть только по строкам и столбцам
// По диагоналям AI не умеет искать выигрышные позиции
// Игроку AI не мешает
namespace AI {

    bool checkAIPreWin(const Field& f, Coord& c) {
        return false;
    }

    bool checkAIPreFail(const Field& f, Coord& c) {
        return false;
    }

    // inLine отвечает за количество уже имеющихся в линии меток AI
    bool checkForTurnInRowsAndColumns(const Field& f, Coord& c, const size_t index, const short needInLine) {
        Cell aI = f.aI;
        short inRow = 0, inCol = 0;
        short rowHasSpace = 0, colHasSpace = 0;
        bool rowCanWin = false, colCanWin = false;
        short rowIndex = -1, colIndex = -1;

        for (int i = 0; i < f.size; i++) {
            // Для строки
            if (f.ppCells[index][i] == EMPTY || f.ppCells[index][i] == aI) {
                rowHasSpace++;
            }
            else {
                rowHasSpace = 0;
                inRow = 0;
            }

            if (rowHasSpace >= f.goal) {
                rowCanWin = true;
            }

            if (f.ppCells[index][i] == aI) {
                inRow++;
            }
            else {
                inRow = 0;
            }

            if (inRow == needInLine && rowIndex < 0) {
                rowIndex = i;
            }

            // Для столбца
            if (f.ppCells[i][index] == EMPTY || f.ppCells[i][index] == aI) {
                colHasSpace++;
            }
            else {
                colHasSpace = 0;
                inCol = 0;
            }

            if (colHasSpace >= f.goal) {
                colCanWin = true;
            }

            if (f.ppCells[i][index] == aI) {
                inCol++;
            }
            else {
                inCol = 0;
            }

            if (inCol == needInLine && colIndex < 0) {
                colIndex = i;
            }
        }

        if (rowCanWin && rowIndex >= 0) {
            if (rowIndex - needInLine >= 0 && f.ppCells[index][rowIndex - needInLine] == EMPTY) {
                c.y = index;
                c.x = rowIndex - needInLine;

                return true;
            }
            else if (rowIndex + 1 < f.size && f.ppCells[index][rowIndex + 1] == EMPTY) {
                c.y = index;
                c.x = rowIndex + 1;

                return true;
            }
        }

        if (colCanWin && colIndex >= 0) {
            if (colIndex - needInLine >= 0 && f.ppCells[colIndex - needInLine][index] == EMPTY) {
                c.y = colIndex - needInLine;
                c.x = index;

                return true;
            }
            else if (colIndex + 1 < f.size && f.ppCells[colIndex + 1][index] == EMPTY) {
                c.y = colIndex + 1;
                c.x = index;

                return true;
            }
        }

        return false;
    }

    Coord getAICoord(Field& f) {
        Coord c;

        do {
            c.x = myrand() % f.size;
            c.y = myrand() % f.size;
        } while (f.ppCells[c.y][c.x] != EMPTY);

        if (f.turns == 0 || f.turns == 1) {
            return c;
        }

        short inLDiag = 0, inRDiag = 0;

        // Ищем подряд идущие метки AI, начиная с самой большой очереди
        for (short i = f.goal - 1; i >= 0; i--) {
            for (size_t j = 0; j < f.size; j++) {
                if (checkForTurnInRowsAndColumns(f, c, j, i)) {
                    return c;
                }
                // TODO проверка ходов на диагоналях
            }
        }

        // TODO Препятствование игроку

        return c;
    }

}