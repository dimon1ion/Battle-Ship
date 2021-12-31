#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

int Gameplay_BattleShip(char***);									   //Весь геймплей игры
void Grids_BattleShip(char**, char**);                                 //Показывает 2 сетки

#include "Расстановка.h"
#include "Бой.h"

int Gameplay_BattleShip(char*** players) {                  //Весь геймплей игры
    setlocale(LC_ALL, "");
    system("color 07");
    srand(time(NULL));

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    COORD nullpos = { 0,0 };
    int write;
    bool settings[3]{}, cheats = false;

    cout << "Добро пожаловать в игру \"Морской бой\"!"; Sleep(500);
    cout << "\nЗагрузка."; Sleep(500); cout << '.'; Sleep(500); cout << '.'; Sleep(500);

    system("cls");
    for (int i = 0; i != 3;) {
        switch (i) {
        case 0:
            cout << "Выберите (нажав клавишу на клавиатуре) режим игры:"
                << "\n1.Человек-Компьютер"
                << "\n2.Компьютер-Компьютер"
                << "\nEsc. Запустить игру заново";
            break;
        case 1:
            if (settings[0]) {
                cout << "Выберите (нажав клавишу на клавиатуре) способ расстановки кораблей:"
                    << "\n1.Игрок расставляет вручную"
                    << "\n2.Компьютер выставляет за игрока"
                    << "\nEsc. Запустить игру заново";
                break;
            }
            settings[i] = false;
            i++;
        case 2:
            cout << "Выберите (нажав клавишу на клавиатуре) режим игры Компьютера:"
                << "\n1.Глупый(Случайные выстрелы)"
                << "\n2.Умный(Компьютер строит стратегию игры)"
                << "\nEsc. Запустить игру заново";
            break;
        }
        write = _getch();
        cout << endl;
        switch (write) {
        case 49:
            settings[i] = true;
            break;
        case 50:
            settings[i] = false;
            break;
        case 27:
            system("cls");
            return 1;
        default:
            cout << "\nError. Выберите одно из верных клавиш";
            SetConsoleCursorPosition(hConsole, nullpos);
            continue;
        }
        system("cls");
        i++;
    }

    switch (settings[0]) {
    case true:
        switch (settings[1]) {
        case true:
            if (Placement_BattleShip(players[0], false) == 1) {
                return 1;
            }
            break;
        case false:
            Placement_BattleShip(players[0], true);
            break;
        }
        Placement_BattleShip(players[1], true);
        cout << "   Ваша зона:\n\n";
        Grids_BattleShip(players[0], 0);
        cout << "\nНажмите на клавишу чтобы продолжить..."
            << "\nEsc.Запустить игру заново";
        write = _getch();
        system("cls");
        if (write == 27) { return 1; }
        break;
    case false:
        Placement_BattleShip(players[0], true);
        Placement_BattleShip(players[1], true);
        for (; ;) {
            cout << "Показать корабли компьютеров перед битвой?"
                << "\n1.Да"
                << "\nНажмите на клавишу чтобы продолжить..."
                << "\nEsc. Запустить игру заново";
            write = _getch();
            switch (write) {
            case 49:
                system("cls");
                cout << "Игрок 1\t\tИгрок 2\n\n";
                Grids_BattleShip(players[0], players[1]);
                cout << "\nНажмите на клавишу чтобы продолжить..."
                    << "\nEsc.Запустить игру заново";
                write = _getch();
                if (write == 27) { return 1; }
                break;
            case 27:
                return 1;
            default:
                break;
            }
            system("cls");
            break;
        }
        break;
    }
    switch (settings[0]) {
    case true:
        cout << "Хотите включить читы(вы будете видеть корабли противника)?"
            << "\n1.Да"
            << "\nНажмите на клавишу чтобы продолжить..."
            << "\nEsc.Запустить игру заново";
        write = _getch();
        switch (write) {
        case 49:
            cheats = true;
            break;
        case 27:
            return 1;
        default:
            break;
        }
        system("cls");
        switch (settings[2]) {
        case true:
            if ((write = Fight_BattleShip(players[0], players[1], false, false, cheats)) == 1) {
                return 1;
            }
            break;
        case false:
            if ((write = Fight_BattleShip(players[0], players[1], false, true, cheats)) == 1) {
                return 1;
            }
            break;
        }
        break;
    default:
        switch (settings[2]) {
        case true:
            if ((write = Fight_BattleShip(players[0], players[1], true, false, cheats)) == 1) {
                return 1;
            }
            break;
        case false:
            if ((write = Fight_BattleShip(players[0], players[1], true, true, cheats)) == 1) {
                return 1;
            }
            break;
        }
        break;
    }
    if (write == 0) {
        cout << "Победил Игрок: 1!!!";
    }
    else {
        cout << "Победил Игрок: 2!!!";
    }
    cout << "\n\nХотите сыграть еще раз?"
        << "\nEsc.Запустить игру заново"
        << "\nНажмите на клавишу чтобы продолжить...";
    write = _getch();
    if (write == 27) { return 1; }
    return 0;
}

void Grids_BattleShip(char** grid1, char** grid2) {                    //Показывает 2 сетки
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 10; i++) {
        if (grid1 != nullptr) {
            for (int j = 0; j < 10; j++) {
                switch (grid1[i][j]) {
                case '1':
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << grid1[i][j];
                    SetConsoleTextAttribute(hConsole, 15);
                    continue;
                case '2':
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << grid1[i][j];
                    SetConsoleTextAttribute(hConsole, 15);
                    continue;
                case 'X':
                case 'x':
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << grid1[i][j];
                    SetConsoleTextAttribute(hConsole, 15);
                    continue;
                }
                cout << grid1[i][j];
            }
        }
        else { cout << "\t"; }
        if (grid2 == nullptr) {
            cout << endl;
            continue;
        }
        cout << "\t";
        for (int j = 0; j < 10; j++) {
            switch (grid2[i][j]) {
            case '1':
                SetConsoleTextAttribute(hConsole, 10);
                cout << grid2[i][j];
                SetConsoleTextAttribute(hConsole, 15);
                continue;
            case '2':
                SetConsoleTextAttribute(hConsole, 14);
                cout << grid2[i][j];
                SetConsoleTextAttribute(hConsole, 15);
                continue;
            case 'X':
            case 'x':
                SetConsoleTextAttribute(hConsole, 12);
                cout << grid2[i][j];
                SetConsoleTextAttribute(hConsole, 15);
                continue;
            }
            cout << grid2[i][j];
        }
        cout << endl;
    }
}

