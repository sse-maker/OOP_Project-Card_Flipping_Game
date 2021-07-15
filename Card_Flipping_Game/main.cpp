//
//  main.cpp
//  Card_Flipping_Game
//
//  Created by 세광 on 2021/07/13.
//

#include <iostream>
#include <random>
#include <unistd.h>
#define matrix 4
#define MAX 8

using namespace std;

class Board_Game {
public:
    Board_Game();
    ~Board_Game();
    
    void Set_Data();
    void Print_Board();
    void Check_Input();
    void End_Game();
    
private:
    unsigned int **card;
    unsigned int *score;
    unsigned int *position;
    bool *on_off;
    unsigned int order;
    char y_n;
};

int main() {
    while (true) {
        Board_Game *game = new Board_Game;
        cout << "Memorize the board number!!" << endl;
        game->Print_Board();
        game->Set_Data();
        game->End_Game();
        delete game;
    }
}

Board_Game::Board_Game() : order(1) {
    card = new unsigned int*[matrix];
    for (size_t i = 0; i < matrix; i++) card[i] = new unsigned int[matrix];
    score = new unsigned int[2];
    fill_n(score, 2, 0);
    position = new unsigned int[matrix];
    on_off = new bool[matrix * matrix];
    fill_n(on_off, matrix * matrix, true);
    
    unsigned int *count = new unsigned int[MAX];
    fill_n(count, MAX, 0);
    
    random_device rd;
    mt19937 gen(rd());
    for (size_t i = 0; i < matrix; i++) {
        for (size_t j = 0; j < matrix; j++) {
            uniform_int_distribution<int> dis(1, MAX);
            unsigned int temp = dis(gen);
            if (count[temp - 1] < 2) {
                card[i][j] = temp;
                count[temp - 1]++;
            }
            else j--;
        }
    }
    
    delete [] count;
}

Board_Game::~Board_Game() {
    for (size_t i = 0; i < matrix; i++) delete card[i];
    delete [] card;
    delete [] score;
    delete [] position;
}

void Board_Game::Set_Data() {
    fill_n(on_off, matrix * matrix, false);
    sleep(3);
    system("clear");
    Print_Board();
    while (score[0] + score[1] != MAX) {
        while (true) {
            cout << '\n' << "[player " << order << "] : ";
            for (size_t i = 0; i < matrix; i++) cin >> position[i];
            if (position[0] == position[2] && position[1] == position[3]) cout << "same position... try again.." << endl;
            else if (on_off[position[0] * matrix + position[1]] == true || on_off[position[2] * matrix + position[3]] == true) cout << "already open... try again.." << endl;
            else break;
        }
        on_off[position[0] * matrix + position[1]] = true;
        on_off[position[2] * matrix + position[3]] = true;
        Print_Board();
        Check_Input();
    }
}

void Board_Game::Print_Board() {
    cout << '\n' << "    0   1   2   3" << endl;
    cout << "  +";
    for (size_t i = 0; i < matrix; i++) cout << "---+";
    cout << endl;
    for (size_t i = 0; i < matrix; i++) {
        cout << i << " | ";
        for (size_t j = 0; j < matrix; j++) {
            if (on_off[i * matrix + j] == true) cout << card[i][j] << " | ";
            else cout << "* | ";
        }
        cout << '\n' << "  +";
        for (size_t k = 0; k < matrix; k++) cout << "---+";
        cout << endl;
    }
}

void Board_Game::Check_Input() {
    if (card[position[0]][position[1]] == card[position[2]][position[3]]) {
        score[order - 1]++;
        cout << '\n' << "player " << order << " get score!!" << endl;
        cout << "[player 1] " << score[0] << " : " << score[1] << " [player 2]" << endl;
        if (score[0] + score[1] != MAX) cout << "player " << order << " get one more chance!!" << endl;
    }
    else {
        cout << '\n' << "mismatch!" << endl;
        on_off[position[0] * matrix + position[1]] = false;
        on_off[position[2] * matrix + position[3]] = false;
        if (order == 1) order = 2;
        else order = 1;
        sleep(3);
        system("clear");
        Print_Board();
    }
}

void Board_Game::End_Game() {
    if (score[0] > score[1]) cout << '\n' << "Game End! Player 1 wins!" << endl;
    else if (score[0] < score[1]) cout << '\n' << "Game End! Player 2 wins!" << endl;
    else cout << '\n' << "Game End! Draw!" << endl;
    cout << "Continue? (y/n) "; cin >> y_n;
    if (y_n == 'n') {
        cout << "Good bye" << endl;
        exit(1);
    }
    else cout << '\n' << "New Game!" << endl;
}
