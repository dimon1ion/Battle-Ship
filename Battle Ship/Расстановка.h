#pragma once
#include "Морской бой.h"

int Placement_BattleShip(char**, bool);                                //Этап расстановки кораблей игрокам
bool Place_check_BattleShip(int, int, char**);                         //Находит 1цу около выбранной клетки с радиусов в 1 клетку
bool Check_insert_BattleShip(int, int, bool[], char**, char**, int);   //Выдает при расстановке удачное положение корабля
int Action_Ship_BattleShip(char**, char**, int, int, bool);            //Действия с кораблем во время расстановки

#include "Бой.h"

int Placement_BattleShip(char** player, bool comp) {                   //Этап расстановки кораблей игрокам
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD nullpos = { 0,0 };
    bool Alive = true, exit = false, check[4];
    char** tmp = new char* [10];
    for (int i = 0; i < 10; i++) {
        tmp[i] = new char[11]{ "0000000000" };
    }
    for (int ship = 1, length = 1, randx, randy, write; ship != 11; ) {
        randx = rand() % 10;
        randy = rand() % 10;
        switch (ship) {
        case 1:
        case 2:
        case 3:
        case 4:
            if (Place_check_BattleShip(randx, randy, player)) {
                tmp[randx][randy] = '1';
                break;
            }
            continue;
        case 5:
        case 6:
        case 7:
            length = 2;
            if (Check_insert_BattleShip(randx, randy, check, player, tmp, length)) {
                break;
            }
            continue;
        case 8:
        case 9:
            length = 3;
            if (Check_insert_BattleShip(randx, randy, check, player, tmp, length)) {
                break;
            }
            continue;
        case 10:
            length = 4;
            if (Check_insert_BattleShip(randx, randy, check, player, tmp, length)) {
                break;
            }
            continue;
        }
        while (true) {
            if (!comp) {
                cout << endl;
                Grids_BattleShip(tmp, player);
                if (Alive) {
                    cout << endl;
                    cout << "Слева сетка куда вы можете расположить свой корабль, справа ваша сетка с вашими уже поставленными кораблями.";
                    cout << "\nС каждым поставленным кораблём компьютер рекомендует свой вариант месторасположения корабля";
                    cout << "\nЧтобы перемещать корабль используйте WASD";
                    cout << "\nЧтобы вращать корабль используйте клавиши Q(налево) E(направо)";
                    cout << "\nПримечание: расстояние между кораблями должно быть минимум 1 клетка!";
                    cout << "\nЕсли вы определелились с месторасположением, нажмите \"Enter\"";
                    cout << "\nЧтобы запустить игру заново нажмите \"Esc\"";
                    Alive = false;
                }
            }
            switch (comp) {
            case true:
                write = 13;
                break;
            default:
                write = _getch();
            }
            switch (Action_Ship_BattleShip(tmp, player, write, length, comp)) {
            case 1:
                if (!comp) {
                    SetConsoleCursorPosition(hConsole, nullpos);
                }
                continue;
            case -1:
                exit = true;
                break;
            default:
                if (!comp) {
                    SetConsoleCursorPosition(hConsole, nullpos);
                }
                break;
            }
            break;
        }
        if (exit) { break; }
        ship++;
    }
    for (int i = 0; i < 10; i++) {
        delete[] tmp[i];
    }
    delete[] tmp;
    if (exit) { return 1; }
    system("cls");
    return 0;
}

bool Place_check_BattleShip(int i, int j, char** player) {             //Находит 1цу около выбранной клетки с радиусов в 1 клетку
    if (0 <= i && i < 10 && 0 <= j && j < 10) {
        if (player[i][j] == '1') { return false; }
    }
    else {
        return false;
    }
    if (j - 1 >= 0) {
        if (player[i][j - 1] == '1') { return false; }
    }
    if (j - 1 >= 0 && i - 1 >= 0) {
        if (player[i - 1][j - 1] == '1') { return false; }
    }
    if (i - 1 >= 0) {
        if (player[i - 1][j] == '1') { return false; }
    }
    if (j + 1 < 10 && i - 1 >= 0) {
        if (player[i - 1][j + 1] == '1') { return false; }
    }
    if (j + 1 < 10) {
        if (player[i][j + 1] == '1') { return false; }
    }
    if (j + 1 < 10 && i + 1 < 10) {
        if (player[i + 1][j + 1] == '1') { return false; }
    }
    if (i + 1 < 10) {
        if (player[i + 1][j] == '1') { return false; }
    }
    if (j - 1 >= 0 && i + 1 < 10) {
        if (player[i + 1][j - 1] == '1') { return false; }
    }
    return true;
}

bool Check_insert_BattleShip(int randx, int randy, bool check[], char** player, char** tmp, int length) {
    for (int i = 0; i < 4; i++) {                           //Выдает при расстановке удачное положение корабля
        check[i] = true;
    }
    for (int i = 0, j = 0; i < length; i++) {
        if (check[0]) {
            if (!Place_check_BattleShip(randx + i, randy, player)) {
                check[0] = false;
                j++;
            }
        }
        if (check[1]) {
            if (!Place_check_BattleShip(randx - i, randy, player)) {
                check[1] = false;
                j++;
            }
        }
        if (check[2]) {
            if (!Place_check_BattleShip(randx, randy - i, player)) {
                check[2] = false;
                j++;
            }
        }
        if (check[3]) {
            if (!Place_check_BattleShip(randx, randy + i, player)) {
                check[3] = false;
                j++;
            }
        }
        if (j == 4) { return false; }
    }
    for (int randif, attempts = 0, l = 1; ; attempts++) {
        switch (attempts) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            randif = rand() % 4 + 1;
            break;
        default:
            randif = l;
            l++;
        }
        switch (randif) {
        case 1:
            if (check[0]) {
                for (int i = 0; i < length; i++) {
                    tmp[randx + i][randy] = '1';
                }
                return true;
            }
            continue;
        case 2:
            if (check[1]) {
                for (int i = 0; i < length; i++) {
                    tmp[randx - i][randy] = '1';
                }
                return true;
            }
            continue;
        case 3:
            if (check[2]) {
                for (int i = 0; i < length; i++) {
                    tmp[randx][randy - i] = '1';
                }
                return true;
            }
            continue;
        case 4:
            if (check[3]) {
                for (int i = 0; i < length; i++) {
                    tmp[randx][randy + i] = '1';
                }
                return true;
            }
            continue;
        default:
            return false;
        }
    }
}

int Action_Ship_BattleShip(char** tmp, char** player, int write, int length, bool comp) {      //Действия с кораблем во время расстановки
    int x = 0, y = 0, answer = 1;
    switch (write) {
    case 162:
    case 100:
    case 235:
    case 115:
        x = 11;
    case 230:
    case 119:
    case 228:
    case 97:
        answer = 1;
        for (int i = 0; i < 10; i++) {
            switch (write) {
            case 162:
            case 100:
            case 235:
            case 115:
                y = 9;
                x -= 2;
            }
            for (int j = 0; j < 10; j++) {
                if (tmp[i + x][j + y] == '1') {
                    switch (write) {
                    case 230:
                    case 119:
                        if (i - 1 >= 0) {
                            swap(tmp[i][j], tmp[i - 1][j]);
                        }
                        else { return answer; }
                        break;
                    case 228:
                    case 97:
                        if (j - 1 >= 0) {
                            swap(tmp[i][j], tmp[i][j - 1]);
                        }
                        else { return answer; }
                        break;
                    case 162:
                    case 100:
                        if (j + y + 1 < 10) {
                            swap(tmp[i + x][j + y], tmp[i + x][j + y + 1]);
                        }
                        else { return answer; }
                        break;
                    case 235:
                    case 115:
                        if (i + x + 1 < 10) {
                            swap(tmp[i + x][j + y], tmp[i + x + 1][j + y]);
                        }
                        else { return answer; }
                        break;
                    }
                }
                switch (write) {
                case 162:
                case 100:
                case 235:
                case 115:
                    y -= 2;
                }
            }
        }
        break;
    case 13:
        answer = 0;
        {
            int check[4][2]{};
            for (int i = 0; i < 4 * 2; i++) {
                check[0][i] = -1;
            }
            for (int i = 0, k = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (tmp[i][j] == '1') {
                        switch (comp) {
                        default:
                            if (!Place_check_BattleShip(i, j, player)) {
                                return 1;
                            }
                            break;
                        case true:
                            break;
                        }
                        check[k][0] = i;
                        check[k][1] = j;
                        k++;
                    }
                }
            }
            for (int i = 0; i < 4; i++) {
                if (check[i][0] == -1) { break; }
                player[check[i][0]][check[i][1]] = tmp[check[i][0]][check[i][1]];
                tmp[check[i][0]][check[i][1]] = '0';
            }
        }
        break;
    case 27:
        return -1;
    case 113:
    case 169:
    case 101:
    case 227:
        answer = 1;
        if (length == 1) { return 1; }
        {
            int x = 0, y = 0;
            for (int tmplength = length; x < 10; x++) {
                for (y = 0; y < 10; y++) {
                    if (tmp[x][y] == '1') {
                        tmplength--;
                        if (tmplength == 0) {
                            break;
                        }
                    }
                }
                if (tmplength == 0) {
                    break;
                }
            }
            bool up = true, check[4] = { true, true, true, true };
            if (0 <= y - 1) {
                if (tmp[x][y - 1] == '1') { up = false; }
            }
            for (int i = 1; i < length; i++) {
                if (check[0]) {
                    if (x - i < 0) { check[0] = false; }
                }
                if (check[1]) {
                    if (x + i >= 10) { check[1] = false; }
                }
                if (check[2]) {
                    if (y - i < 0) { check[2] = false; }
                }
                if (check[3]) {
                    if (y + i >= 10) { check[3] = false; }
                }
            }
            switch (up) {
            case true:
                switch (write) {
                case 113:
                case 169:
                    if (check[2]) {
                        for (int i = 1; i < length; i++) {
                            swap(tmp[x - i][y], tmp[x][y - i]);
                        }
                    }
                    break;
                default:
                    if (check[3]) {
                        for (int i = 1; i < length; i++) {
                            swap(tmp[x - i][y], tmp[x][y + i]);
                        }
                    }
                }
                break;
            default:
                switch (write) {
                case 113:
                case 169:
                    if (check[1]) {
                        for (int i = 1; i < length; i++) {
                            swap(tmp[x][y - i], tmp[x + i][y]);
                        }
                    }
                    break;
                default:
                    if (check[1]) {
                        for (int i = 1; i < length; i++) {
                            swap(tmp[x][y - i], tmp[x - i][y]);
                        }
                    }
                }
            }
        }
        break;
    }
    return answer;
}