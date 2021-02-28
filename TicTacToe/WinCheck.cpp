
#include "MyLib.h"

using namespace MyLib;

namespace WinCheck {

    // Проверка строки и столбца с индексами index на наличие победы
    bool checkRowAndCol(Field& f, size_t index) {
        // Накапливаемые значения для строки и столбца соответственно
        short colZeros = 0, colCrosses = 0;
        short rowZeros = 0, rowCrosses = 0;

        // Бежим по строке/столбцу и накапливаем
        for (size_t i = 0; i < f.size; i++) {
            // Для строки
            if (f.ppCells[index][i] == ZERO) {
                colZeros++;

                // Если накопили нужное количество, то считаем игру завершенной
                if (colZeros == f.goal) {
                    f.progress = f.human == ZERO ? HUMAN_WON : AI_WON;
                    return true;
                }

                colCrosses = 0;
            }
            else if (f.ppCells[index][i] == CROSS) {
                colCrosses++;

                if (colCrosses == f.goal) {
                    f.progress = f.human == CROSS ? HUMAN_WON : AI_WON;
                    return true;
                }

                colZeros = 0;
            }
            else if (f.ppCells[index][i] == EMPTY) {
                colZeros = 0;
                colCrosses = 0;
            }

            // Для столбца
            if (f.ppCells[i][index] == ZERO) {
                rowZeros++;

                if (rowZeros == f.goal) {
                    f.progress = f.human == ZERO ? HUMAN_WON : AI_WON;
                    return true;
                }

                rowCrosses = 0;
            }
            else if (f.ppCells[i][index] == CROSS) {
                rowCrosses++;

                if (rowCrosses == f.goal) {
                    f.progress = f.human == CROSS ? HUMAN_WON : AI_WON;
                    return true;
                }

                rowZeros = 0;
            }
            else if (f.ppCells[i][index] == EMPTY) {
                rowZeros = 0;
                rowCrosses = 0;
            }
        }

        return false;
    }

    // Проверка НЕ центральных диагоналей на победу
    bool checkNonCentralDiag(Field& f, size_t index) {
        short lUpDiagZeros = 0, lUpDiagCrosses = 0;
        short lDownDiagZeros = 0, lDownDiagCrosses = 0;
        short rUpDiagZeros = 0, rUpDiagCrosses = 0;
        short rDownDiagZeros = 0, rDownDiagCrosses = 0;

        for (size_t i = 0; i < f.size - index; i++) {
            // Выше левой ц. диагонали
            if (f.ppCells[i][index + i] == ZERO) {
                lUpDiagZeros++;
                if (lUpDiagZeros == f.goal) {
                    f.progress = f.human == ZERO ? HUMAN_WON : AI_WON;
                    return true;
                }

                lUpDiagCrosses = 0;
            }
            else if (f.ppCells[i][index] == CROSS) {
                lUpDiagCrosses++;
                if (lUpDiagCrosses == f.goal) {
                    f.progress = f.human == CROSS ? HUMAN_WON : AI_WON;
                    return true;
                }

                lUpDiagZeros = 0;
            }
            else if (f.ppCells[i][index] == EMPTY) {
                lUpDiagZeros = 0;
                lUpDiagCrosses = 0;
            }

            // Ниже левой ц. диагонали
            if (f.ppCells[index + i][i] == ZERO) {
                lDownDiagZeros++;
                if (lDownDiagZeros == f.goal) {
                    f.progress = f.human == ZERO ? HUMAN_WON : AI_WON;
                    return true;
                }

                lDownDiagCrosses = 0;
            }
            else if (f.ppCells[index + 1][i] == CROSS) {
                lDownDiagCrosses++;
                if (lDownDiagCrosses == f.goal) {
                    f.progress = f.human == CROSS ? HUMAN_WON : AI_WON;
                    return true;
                }

                lDownDiagZeros = 0;
            }
            else if (f.ppCells[index + i][i] == EMPTY) {
                lDownDiagZeros = 0;
                lDownDiagCrosses = 0;
            }

            // Выше правой ц. диагонали
            if (f.ppCells[i][f.size - 1 - index - i] == ZERO) {
                rUpDiagZeros++;
                if (rUpDiagZeros == f.goal) {
                    f.progress = f.human == ZERO ? HUMAN_WON : AI_WON;
                    return true;
                }

                rUpDiagCrosses = 0;
            }
            else if (f.ppCells[i][f.size - 1 - index - i] == CROSS) {
                rUpDiagCrosses++;
                if (rUpDiagCrosses == f.goal) {
                    f.progress = f.human == CROSS ? HUMAN_WON : AI_WON;
                    return true;
                }

                rUpDiagZeros = 0;
            }
            else if (f.ppCells[i][f.size - 1 - index - i] == EMPTY) {
                rUpDiagZeros = 0;
                rUpDiagCrosses = 0;
            }

            // Ниже правой ц. диагонали
            if (f.ppCells[index + i][f.size - 1 - i] == ZERO) {
                rDownDiagZeros++;
                if (rDownDiagZeros == f.goal) {
                    f.progress = f.human == ZERO ? HUMAN_WON : AI_WON;
                    return true;
                }

                rDownDiagCrosses = 0;
            }
            else if (f.ppCells[index + i][f.size - 1 - i] == CROSS) {
                rDownDiagCrosses++;
                if (rDownDiagCrosses == f.goal) {
                    f.progress = f.human == CROSS ? HUMAN_WON : AI_WON;
                    return true;
                }

                rDownDiagZeros = 0;
            }
            else if (f.ppCells[index + i][f.size - 1 - i] == EMPTY) {
                rDownDiagZeros = 0;
                rDownDiagCrosses = 0;
            }
        }

        return false;
    }

    // Проверка на наличие победы
    bool check(Field& f) {
        short lDiagZeros = 0, lDiagCrosses = 0;
        short rDiagZeros = 0, rDiagCrosses = 0;

        for (size_t i = 0; i < f.size; i++) {
            if (checkRowAndCol(f, i)) {
                return true;
            }

            // Для левой центральной диагонали
            if (f.ppCells[i][i] == ZERO) {
                lDiagZeros++;
                if (lDiagZeros == f.goal) {
                    f.progress = f.human == ZERO ? HUMAN_WON : AI_WON;
                    return true;
                }

                lDiagCrosses = 0;
            }
            else if (f.ppCells[i][i] == CROSS) {
                lDiagCrosses++;
                if (lDiagCrosses == f.goal) {
                    f.progress = f.human == CROSS ? HUMAN_WON : AI_WON;
                    return true;
                }

                lDiagZeros = 0;
            }
            else if (f.ppCells[i][i] == EMPTY) {
                lDiagZeros = 0;
                lDiagCrosses = 0;
            }

            // Для правой центральной диагонали
            if (f.ppCells[f.size - i - 1][i] == ZERO) {
                rDiagZeros++;
                if (rDiagZeros == f.goal) {
                    f.progress = f.human == ZERO ? HUMAN_WON : AI_WON;
                    return true;
                }

                rDiagCrosses = 0;
            }
            else if (f.ppCells[f.size - i - 1][i] == CROSS) {
                rDiagCrosses++;
                if (rDiagCrosses == f.goal) {
                    f.progress = f.human == CROSS ? HUMAN_WON : AI_WON;
                    return true;
                }

                rDiagZeros = 0;
            }
            else if (f.ppCells[f.size - i - 1][i] == EMPTY) {
                rDiagZeros = 0;
                rDiagCrosses = 0;
            }
        }

        for (size_t i = 1; i <= f.size - f.goal; i++) {
            if (checkNonCentralDiag(f, i)) {
                return true;
            }
        }

        return false;
    }

}