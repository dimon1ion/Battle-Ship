#pragma once
#include "Морской бой.h"

int Fight_BattleShip(char**, char**, bool, bool, bool);                //Этап битвы
int Action_Fight_BattleShip(char**, int, int&, int&);                  //Передвижение прицела
bool Fight_enter_BattleShip(char**, char**, int, int, bool&);          //Стрельба по вражеской зоне + заполнение 'X' если корабль уничтожен
bool Tactic_BattleShip(char**, char**, bool&, int&, int&);             //Режим интеллектуального боя

#include "Расстановка.h"

int Fight_BattleShip(char** player1, char** player2, bool comp, bool tactic_comp, bool cheats) {   //Этап битвы
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD nullpos = { 0,0 };
    char*** tmp = new char** [2];
    int randx, randy, write;
    bool exit = false, game_over = false, player01 = true, tactic2 = false, tactic1 = false, repeat = false, found2 = false, Alive = true;
    for (int i = 0; i < 2; i++) {
        tmp[i] = new char* [10];
        for (int j = 0; j < 10; j++) {
            tmp[i][j] = new char[11]{ "0000000000" };
        }
    }
    bool step = true;
    while (true) {
        SetConsoleCursorPosition(hConsole, nullpos);
        if (!repeat) {
            for (int u = 0, v = 0; u < 10; u++) {
                for (v = 0; v < 10; v++) {
                    if (player1[u][v] == '1') {
                        game_over = false;
                        break;
                    }
                    else {
                        game_over = true;
                    }
                }
                if (v != 10) {
                    break;
                }
            }
            if (game_over) {
                player01 = false;
                break;
            }
            for (int u = 0, v = 0; u < 10; u++) {
                for (v = 0; v < 10; v++) {
                    if (player2[u][v] == '1') {
                        game_over = false;
                        break;
                    }
                    else {
                        game_over = true;
                    }
                }
                if (v != 10) {
                    break;
                }
            }
        }
        else { repeat = false; }
        if (game_over) { break; }
        randx = rand() % 10;
        randy = rand() % 10;
        switch (tmp[!step][randx][randy]) {
        case 'X':
        case '2':
            continue;
        default:
            tmp[!step][randx][randy] = 'x';
            break;
        }
        switch (step) {
        case true:
            while (true) {
                if (!comp) {
                    cout << "\nВаша зона\tЗона противника\n\n";
                    Grids_BattleShip(player1, tmp[0]);
                    if (cheats) {
                        cout << endl;
                        Grids_BattleShip(0, player2);
                    }
                    if (Alive) {
                        cout << "\nЧтобы перемещать прицел используйте WASD";
                        cout << "\nЕсли вы определелились с месторасположением, нажмите \"Enter\"";
                        cout << "\nЧтобы поменять место прицела(рандомно) нажмите 'R'";
                        Alive = false;
                    }
                    write = _getch();
                    switch (write) {
                    case 13:
                        Fight_enter_BattleShip(tmp[0], player2, randx, randy, found2);
                        break;
                    case 114:
                    case 170:
                        repeat = true;
                        break;
                    default:
                        switch (Action_Fight_BattleShip(tmp[0], write, randx, randy)) {
                        case 1:
                            SetConsoleCursorPosition(hConsole, nullpos);
                            continue;
                        case -1:
                            exit = true;
                            break;
                        }
                    }
                }
                break;
            }
            if (comp) {
                if (tactic_comp) {
                    if (tactic1) {
                        tmp[0][randx][randy] = '0';
                        tactic1 = Tactic_BattleShip(tmp[0], player2, found2, randx, randy);
                        if (tactic1 && found2) {
                            Fight_enter_BattleShip(tmp[0], player2, randx, randy, found2);
                        }
                    }
                    else {
                        tactic1 = Fight_enter_BattleShip(tmp[0], player2, randx, randy, found2);
                    }
                }
                else { Fight_enter_BattleShip(tmp[0], player2, randx, randy, found2); }
            }
            if (repeat) {
                tmp[0][randx][randy] = '0';
                continue;
            }
            if (found2) { continue; }
            break;
        default:
            if (tactic_comp) {
                if (tactic2) {
                    tmp[1][randx][randy] = '0';
                    tactic2 = Tactic_BattleShip(tmp[1], player1, found2, randx, randy);
                    if (tactic2 && found2) {
                        tactic2 = Fight_enter_BattleShip(tmp[1], player1, randx, randy, found2);
                    }
                }
                else {
                    tactic2 = Fight_enter_BattleShip(tmp[1], player1, randx, randy, found2);
                }
            }
            else { Fight_enter_BattleShip(tmp[1], player1, randx, randy, found2); }
            if (found2) { continue; }
        }
        if (comp) {
            cout << "\nИгрок 1\t\tИгрок 2\n\n";
            Grids_BattleShip(player1, player2);
            cout << "\nНажмите на клавишу чтобы продолжить..."
                << "\nEsc.Запустить игру заново";
            write = _getch();
            if (write == 27) {
                exit = true;
                break;
            }
        }
        if (exit) { break; }
        step = !step;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            delete[] tmp[i][j];
        }
        delete[] tmp[i];
    }
    delete[] tmp;
    if (exit) { return 1; }
    system("cls");
    if (player01) { return 0; }
    else { return 3; }
}

int Action_Fight_BattleShip(char** tmp, int write, int& randx, int& randy) {   //Передвижение прицела
    int k = 0;
    bool out = true;
    switch (write) {
    case 230:
    case 119:
        if (randx - 1 >= 0) {
            while (true) {
                if (tmp[randx - 1 - k][randy] == 'X' || tmp[randx - 1 - k][randy] == '2') {
                    k++;
                    if (randx - 1 - k >= 0) {
                        continue;
                    }
                    out = false;
                }
                break;
            }
            if (out) {
                swap(tmp[randx][randy], tmp[randx - 1 - k][randy]);
                randx -= 1 + k;
            }
        }
        else { return 1; }
        break;
    case 228:
    case 97:
        if (randy - 1 >= 0) {
            while (true) {
                if (tmp[randx][randy - 1 - k] == 'X' || tmp[randx][randy - 1 - k] == '2') {
                    k++;
                    if (randy - 1 - k >= 0) {
                        continue;
                    }
                    out = false;
                }
                break;
            }
            if (out) {
                swap(tmp[randx][randy], tmp[randx][randy - 1 - k]);
                randy -= 1 + k;
            }
        }
        else { return 1; }
        break;
    case 162:
    case 100:
        if (randy + 1 < 10) {
            while (true) {
                if (tmp[randx][randy + 1 + k] == 'X' || tmp[randx][randy + 1 + k] == '2') {
                    k++;
                    if (randy + 1 + k < 10) {
                        continue;
                    }
                    out = false;
                }
                break;
            }
            if (out) {
                swap(tmp[randx][randy], tmp[randx][randy + 1 + k]);
                randy += 1 + k;
            }
        }
        else { return 1; }
        break;
    case 235:
    case 115:
        if (randx + 1 < 10) {
            while (true) {
                if (tmp[randx + 1 + k][randy] == 'X' || tmp[randx + 1 + k][randy] == '2') {
                    k++;
                    if (randx + 1 + k < 10) {
                        continue;
                    }
                    out = false;
                }
                break;
            }
            if (out) {
                swap(tmp[randx][randy], tmp[randx + 1 + k][randy]);
                randx += 1 + k;
            }
        }
        else { return 1; }
        break;
    case 27:
        return -1;
    }
    return 1;
}

bool Fight_enter_BattleShip(char** tmp, char** player, int randx, int randy, bool& found2) {   //Стрельба по вражеской зоне + заполнение 'X' если корабль уничтожен
    bool work = true;
    int repeat = 0;
    bool check[4] = { false, false, false, false }, alone = false;
    switch (player[randx][randy]) {
    case '0':
        player[randx][randy] = 'X';
        tmp[randx][randy] = 'X';
        found2 = false;
        return false;
    case '1':
    case '2':
        player[randx][randy] = '2';
        tmp[randx][randy] = '2';
        if (Place_check_BattleShip(randx, randy, player)) {
            while (true) {
                if (randx - 1 >= 0) {
                    if (alone) {
                        player[randx - 1][randy] = 'X';
                        tmp[randx - 1][randy] = 'X';
                    }
                    else if (player[randx - 1][randy] == '2') {
                        if (randx - 2 >= 0) {
                            if (player[randx - 2][randy] == '2' || player[randx - 2][randy] == '1') {
                                if (!Place_check_BattleShip(randx - 2, randy, player)) {
                                    found2 = true;
                                    return true;
                                }
                            }
                        }
                        check[0] = true;
                        repeat++;
                    }
                }
                if (randx + 1 < 10) {
                    if (alone) {
                        player[randx + 1][randy] = 'X';
                        tmp[randx + 1][randy] = 'X';
                    }
                    else if (player[randx + 1][randy] == '2') {
                        if (randx + 2 < 10) {
                            if (player[randx + 2][randy] == '2' || player[randx + 2][randy] == '1') {
                                if (!Place_check_BattleShip(randx + 2, randy, player)) {
                                    found2 = true;
                                    return true;
                                }
                            }
                        }
                        check[1] = true;
                        repeat++;
                    }
                }
                if (randy - 1 >= 0) {
                    if (alone) {
                        player[randx][randy - 1] = 'X';
                        tmp[randx][randy - 1] = 'X';
                    }
                    else if (player[randx][randy - 1] == '2') {
                        if (randy - 2 >= 0) {
                            if (player[randx][randy - 2] == '2' || player[randx][randy - 2] == '1') {
                                if (!Place_check_BattleShip(randx, randy - 2, player)) {
                                    found2 = true;
                                    return true;
                                }
                            }
                        }
                        check[2] = true;
                        repeat++;
                    }
                }
                if (randy + 1 < 10) {
                    if (alone) {
                        player[randx][randy + 1] = 'X';
                        tmp[randx][randy + 1] = 'X';
                    }
                    else if (player[randx][randy + 1] == '2') {
                        if (randy + 2 < 10) {
                            if (player[randx][randy + 2] == '2' || player[randx][randy + 2] == '1') {
                                if (!Place_check_BattleShip(randx, randy + 2, player)) {
                                    found2 = true;
                                    return true;
                                }
                            }
                        }
                        check[3] = true;
                        repeat++;
                    }
                }
                if (repeat > 1) {
                    if (check[0]) {
                        randx--;
                        check[0] = false;
                    }
                    else if (check[1]) {
                        randx++;
                        check[1] = false;
                    }
                    else if (check[2]) {
                        randy--;
                        check[2] = false;
                    }
                    else if (check[3]) {
                        randy++;
                        check[3] = false;
                    }
                    repeat = 0;
                    continue;
                }
                else if (repeat == 1) { break; }
                if (alone) {
                    if (randx - 1 >= 0 && randy - 1 >= 0) {
                        player[randx - 1][randy - 1] = 'X';
                        tmp[randx - 1][randy - 1] = 'X';
                    }
                    if (randx - 1 >= 0 && randy + 1 < 10) {
                        player[randx - 1][randy + 1] = 'X';
                        tmp[randx - 1][randy + 1] = 'X';
                    }
                    if (randx + 1 < 10 && randy - 1 >= 0) {
                        player[randx + 1][randy - 1] = 'X';
                        tmp[randx + 1][randy - 1] = 'X';
                    }
                    if (randx + 1 < 10 && randy + 1 < 10) {
                        player[randx + 1][randy + 1] = 'X';
                        tmp[randx + 1][randy + 1] = 'X';
                    }
                    found2 = true;
                    return false;
                }
                alone = true;
            }
        }
        else {
            found2 = true;
            return true;
        }
    }
    if (check[0]) {
        if (randx + 1 < 10) { randx++; }
        else { work = false; }
    }
    else if (check[1]) {
        if (randx - 1 >= 0) { randx--; }
        else { work = false; }
    }
    else if (check[2]) {
        if (randy + 1 < 10) { randy++; }
        else { work = false; }
    }
    else if (check[3]) {
        if (randy - 1 >= 0) { randy--; }
        else { work = false; }
    }
    while (true) {
        if (check[0] || check[1]) {
            if (player[randx][randy] == '0' || player[randx][randy] == 'X') {
                player[randx][randy] = 'X';
                tmp[randx][randy] = 'X';
                work = !work;
            }
            if (randy - 1 >= 0) {
                player[randx][randy - 1] = 'X';
                tmp[randx][randy - 1] = 'X';
            }
            if (randy + 1 < 10) {
                player[randx][randy + 1] = 'X';
                tmp[randx][randy + 1] = 'X';
            }
        }
        else {
            if (player[randx][randy] == '0' || player[randx][randy] == 'X') {
                player[randx][randy] = 'X';
                tmp[randx][randy] = 'X';
                work = !work;
            }
            if (randx - 1 >= 0) {
                player[randx - 1][randy] = 'X';
                tmp[randx - 1][randy] = 'X';
            }
            if (randx + 1 < 10) {
                player[randx + 1][randy] = 'X';
                tmp[randx + 1][randy] = 'X';
            }
        }
        if (check[0]) {
            if (randx - 1 >= 0) { randx--; }
            else { work = true; }
        }
        if (check[1]) {
            if (randx + 1 < 10) { randx++; }
            else { work = true; }
        }
        if (check[2]) {
            if (randy - 1 >= 0) { randy--; }
            else { work = true; }
        }
        if (check[3]) {
            if (randy + 1 < 10) { randy++; }
            else { work = true; }
        }
        if (work) { break; }
    }
    found2 = true;
    return false;
}

bool Tactic_BattleShip(char** tmp, char** player, bool& found2, int& randx, int& randy) {  //Режим интеллектуального боя

    int i, j, r = 0;
    bool found = true, Alive = true, random = true;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (player[i][j] == '2') {
                if (!(found = (Place_check_BattleShip(i, j, player)))) { break; }
            }
        }
        if (!found) {
            break;
        }
    }
    if (!found) {
        while (true) {
            if (Alive) {
                if (i - 1 >= 0) {
                    if (tmp[i - 1][j] == '2') {
                        r = 2;
                        random = false;
                    }
                }
                else if (i + 1 < 10) {
                    if (tmp[i + 1][j] == '2') {
                        r = 1;
                        random = false;
                    }
                }
                else if (j - 1 >= 0) {
                    if (tmp[i][j - 1] == '2') {
                        r = 4;
                        random = false;
                    }
                }
                else if (j + 1 < 10) {
                    if (tmp[i][j + 1] == '2') {
                        r = 3;
                        random = false;
                    }
                }
                Alive = false;
            }
            if (random) {
                r = rand() % 4 + 1;
            }
            switch (r) {
            case 1:
                if (i - 1 >= 0) {
                    if (tmp[i - 1][j] == '0') {
                        if (player[i - 1][j] == '1') {
                            player[i - 1][j] = '2';
                            tmp[i - 1][j] = '2';
                            randx = i - 1;
                            randy = j;
                            found2 = true;
                            return true;
                        }
                        else {
                            player[i - 1][j] = 'X';
                            tmp[i - 1][j] = 'X';
                            found2 = false;
                            return true;
                        }
                    }
                    continue;
                }
                continue;
            case 2:
                if (i + 1 < 10) {
                    if (tmp[i + 1][j] == '0') {
                        if (player[i + 1][j] == '1') {
                            player[i + 1][j] = '2';
                            tmp[i + 1][j] = '2';
                            randx = i + 1;
                            randy = j;
                            found2 = true;
                            return true;
                        }
                        else {
                            player[i + 1][j] = 'X';
                            tmp[i + 1][j] = 'X';
                            found2 = false;
                            return true;
                        }
                    }
                    continue;
                }
                continue;
            case 3:
                if (j - 1 >= 0) {
                    if (tmp[i][j - 1] == '0') {
                        if (player[i][j - 1] == '1') {
                            player[i][j - 1] = '2';
                            tmp[i][j - 1] = '2';
                            randx = i;
                            randy = j - 1;
                            found2 = true;
                            return true;
                        }
                        else {
                            player[i][j - 1] = 'X';
                            tmp[i][j - 1] = 'X';
                            found2 = false;
                            return true;
                        }
                    }
                    continue;
                }
                continue;
            case 4:
                if (j + 1 < 10) {
                    if (tmp[i][j + 1] == '0') {
                        if (player[i][j + 1] == '1') {
                            player[i][j + 1] = '2';
                            tmp[i][j + 1] = '2';
                            randx = i;
                            randy = j + 1;
                            found2 = true;
                            return true;
                        }
                        else {
                            player[i][j + 1] = 'X';
                            tmp[i][j + 1] = 'X';
                            found2 = false;
                            return true;
                        }
                    }
                    continue;
                }
                continue;
            }
            break;
        }
    }
    return false;
}