#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

int Gameplay_BattleShip(char***);									   //���� �������� ����
void Grids_BattleShip(char**, char**);                                 //���������� 2 �����

#include "�����������.h"
#include "���.h"

int Gameplay_BattleShip(char*** players) {                  //���� �������� ����
    setlocale(LC_ALL, "");
    system("color 07");
    srand(time(NULL));

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    COORD nullpos = { 0,0 };
    int write;
    bool settings[3]{}, cheats = false;

    cout << "����� ���������� � ���� \"������� ���\"!"; Sleep(500);
    cout << "\n��������."; Sleep(500); cout << '.'; Sleep(500); cout << '.'; Sleep(500);

    system("cls");
    for (int i = 0; i != 3;) {
        switch (i) {
        case 0:
            cout << "�������� (����� ������� �� ����������) ����� ����:"
                << "\n1.�������-���������"
                << "\n2.���������-���������"
                << "\nEsc. ��������� ���� ������";
            break;
        case 1:
            if (settings[0]) {
                cout << "�������� (����� ������� �� ����������) ������ ����������� ��������:"
                    << "\n1.����� ����������� �������"
                    << "\n2.��������� ���������� �� ������"
                    << "\nEsc. ��������� ���� ������";
                break;
            }
            settings[i] = false;
            i++;
        case 2:
            cout << "�������� (����� ������� �� ����������) ����� ���� ����������:"
                << "\n1.������(��������� ��������)"
                << "\n2.�����(��������� ������ ��������� ����)"
                << "\nEsc. ��������� ���� ������";
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
            cout << "\nError. �������� ���� �� ������ ������";
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
        cout << "   ���� ����:\n\n";
        Grids_BattleShip(players[0], 0);
        cout << "\n������� �� ������� ����� ����������..."
            << "\nEsc.��������� ���� ������";
        write = _getch();
        system("cls");
        if (write == 27) { return 1; }
        break;
    case false:
        Placement_BattleShip(players[0], true);
        Placement_BattleShip(players[1], true);
        for (; ;) {
            cout << "�������� ������� ����������� ����� ������?"
                << "\n1.��"
                << "\n������� �� ������� ����� ����������..."
                << "\nEsc. ��������� ���� ������";
            write = _getch();
            switch (write) {
            case 49:
                system("cls");
                cout << "����� 1\t\t����� 2\n\n";
                Grids_BattleShip(players[0], players[1]);
                cout << "\n������� �� ������� ����� ����������..."
                    << "\nEsc.��������� ���� ������";
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
        cout << "������ �������� ����(�� ������ ������ ������� ����������)?"
            << "\n1.��"
            << "\n������� �� ������� ����� ����������..."
            << "\nEsc.��������� ���� ������";
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
        cout << "������� �����: 1!!!";
    }
    else {
        cout << "������� �����: 2!!!";
    }
    cout << "\n\n������ ������� ��� ���?"
        << "\nEsc.��������� ���� ������"
        << "\n������� �� ������� ����� ����������...";
    write = _getch();
    if (write == 27) { return 1; }
    return 0;
}

void Grids_BattleShip(char** grid1, char** grid2) {                    //���������� 2 �����
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

