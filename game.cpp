#include "Game.h"

Game::Game() {
    spawnTile();
}

void Game::moveRowRight(int* row) {
    int* temp = new int[4] {0, 0, 0, 0};

    int j = 0;
    for (int i = 0; i < 4; i++) {
        if (row[3 - i] != 0) {
            if (j > 0 && row[3 - i] == temp[4 - j]) {
                temp[4 - j] <<= 1;
            }
            else {
                temp[3 - j] = row[3 - i];
            }
            j++;
        }
    }

    j = 0;
    for (int i = 0; i < 4; i++) {
        row[3 - i] = 0;
        if (temp[3 - i] != 0) {
            row[3 - j] = temp[3 - i];
            j++;
        }
    }
}
void Game::moveRowLeft(int* row) {
    int* temp = new int[4] {0, 0, 0, 0};

    int j = 0;
    for (int i = 0; i < 4; i++) {
        if (row[i] != 0) {
            if (j > 0 && row[i] == temp[j - 1]) {
                temp[j - 1] <<= 1;
            }
            else {
                temp[j] = row[i];
            }
            j++;
        }
    }

    j = 0;
    for (int i = 0; i < 4; i++) {
        row[i] = 0;
        if (temp[i] != 0) {
            row[j] = temp[i];
            j++;
        }
    }
}

void Game::moveLeft() {
    for (int i = 0; i < 4; i++) {
        moveRowLeft(board[i]);
    }
}
void Game::moveRight() {
    for (int i = 0; i < 4; i++) {
        moveRowRight(board[i]);
    }
}
void Game::moveUp() {
    for (int i = 0; i < 4; i++) {
        int* proxyRow =
            new int[4] {board[0][i], board[1][i], board[2][i], board[3][i]};
        moveRowLeft(proxyRow);

        board[0][i] = proxyRow[0];
        board[1][i] = proxyRow[1];
        board[2][i] = proxyRow[2];
        board[3][i] = proxyRow[3];
    }
}
void Game::moveDown() {
    for (int i = 0; i < 4; i++) {
        int* proxyRow =
            new int[4] {board[0][i], board[1][i], board[2][i], board[3][i]};
        moveRowRight(proxyRow);

        board[0][i] = proxyRow[0];
        board[1][i] = proxyRow[1];
        board[2][i] = proxyRow[2];
        board[3][i] = proxyRow[3];
    }
}

void Game::printBoard() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                cout << ".\t";
            }
            else {
                cout << board[i][j] << "\t";
            }
        }
        cout << endl;
    }
}
bool Game::boardIsFull() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}
bool Game::boardIsEqual(int board2[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != board2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int Game::getMaxTile() {
    int max = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] > max) {
                max = board[i][j];
            }
        }
    }
    return max;
}

void Game::spawnTile() {
    int count = 0; // number of 0s
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                count++;
            }
        }
    }
    if (count == 0) {
        return;
    }

    int randIndex = rand() % count;
    count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                if (count == randIndex) {
                    board[i][j] = (rand() % 20) == 0 ? 4 : 2;
                    return;
                }
                count++;
            }
        }
    }
}

/*Output: true if a move was successfully made*/
bool Game::loop(int move, bool print, std::string perPrint) {
    if (perPrint != "" && print) {
        system(perPrint.c_str());
    }

    int prev[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            prev[i][j] = board[i][j];
        }
    }
    switch (move) {
    case 0:
        moveUp();
        break;
    case 1:
        moveDown();
        break;
    case 2:
        moveLeft();
        break;
    case 3:
        moveRight();
        break;
    }

    if (print) {
        printBoard();
    }

    if (!boardIsEqual(prev)) {
        spawnTile();
        score += 1;
        return true;
    }
    score -= 2;
    return false;
}
/*Output: true if a move was successfully made*/
bool Game::loop(std::vector<float> move, bool print, std::string perPrint) {
    for (int i = 0; i < 4; i++) {
        if (loop(findMove(move)[i], print, perPrint)) {
            return true;
        }
    }
    return false;
}
std::vector<float> Game::boardPosition() {
    std::vector<float> vec;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            vec.push_back((float)board[i][j]);
        }
    }
    return vec;
}

std::vector<int> Game::findMove(std::vector<float> output) {
    std::vector<int> indices;
    for (int j = 0; j < 4; j++) {
        float max = -1; // float min
        int index = -1;
        for (int i = 0; i < output.size(); i++) {
            if (output[i] > max) {
                max = output[i];
                index = i;
            }
        }
        output[index] = 0;
        indices.push_back(index);
    }
    return indices;
}
