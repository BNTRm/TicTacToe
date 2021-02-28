
#include <iostream>
#include <random>
#include <Windows.h>
#include "MyLib.h"

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distrib(1, 100);

namespace MyLib {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    void clearScr() {
        //system("cls");
        std::cout << "\x1B[2J\x1B[H";
    }

    int myrand() {
        return distrib(gen);
    }

    int yIndexByChar(char ch) {
        return std::distance(LITERAL_Y_AXIS, std::find(LITERAL_Y_AXIS, LITERAL_Y_AXIS + 20, toupper(ch))) + 1;
    }


    void printField(const Field& f) {
        cout << "    ";

        SetConsoleTextAttribute(hConsole, 3);
        for (size_t i = 0; i < f.size; i++) {
            cout << LITERAL_Y_AXIS[i] << " ";
        }
        cout << endl;

        for (size_t y = 0; y < f.size; y++) {
            cout << (y + 1 < 10 ? " " : "");

            SetConsoleTextAttribute(hConsole, 3);
            cout << y + 1;

            SetConsoleTextAttribute(hConsole, 8);
            cout << "|";

            for (size_t x = 0; x < f.size; x++) {
                cout << " ";
                
                if (f.ppCells[y][x] == CROSS) {
                    SetConsoleTextAttribute(hConsole, 12);
                }
                else if (f.ppCells[y][x] == ZERO) {
                    SetConsoleTextAttribute(hConsole, 11);
                }
                else {
                    SetConsoleTextAttribute(hConsole, 15);
                }
                cout << (char)f.ppCells[y][x];
            }
            SetConsoleTextAttribute(hConsole, 8);
            cout << " |" << endl;
        }

        cout << endl;
    }

    void updateScreen(Field& f) {
        clearScr();
        printField(f);

        SetConsoleTextAttribute(hConsole, 6);
        cout << "Human: ";

        if (f.human == CROSS) {
            SetConsoleTextAttribute(hConsole, 12);
        }
        else if (f.human == ZERO) {
            SetConsoleTextAttribute(hConsole, 11);
        }
        cout << char(f.human) << endl;

        SetConsoleTextAttribute(hConsole, 6);
        cout << "AI: ";
        if (f.aI == CROSS) {
            SetConsoleTextAttribute(hConsole, 12);
        }
        else if (f.aI == ZERO) {
            SetConsoleTextAttribute(hConsole, 11);
        }
        cout << char(f.aI) << endl << endl;
    }

}