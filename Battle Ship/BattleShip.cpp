#include "Морской бой.h"
int main() {
    for (int Alive = 1; Alive != 0;) {
        char*** players = new char** [2];
        for (int i = 0; i < 2; i++) {
            players[i] = new char* [10];
            for (int j = 0; j < 10; j++) {
                players[i][j] = new char[11]{ "0000000000" };
            }
        }
        Alive = Gameplay_BattleShip(players);
        system("cls");
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 10; j++) {
                delete[] players[i][j];
            }
            delete[] players[i];
        }
        delete[] players;
    }
    cout << "Спасибо, что сыграли :)";
    Sleep(1000);
}