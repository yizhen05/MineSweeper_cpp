#include <time.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

bool debug = false;

// ボードのサイズと爆弾の数
const unsigned int SIZE = 8;
const unsigned int MINES = 10;
// ライフ
unsigned int life = 3;

// 判定用と表示用のボード
unsigned char judgement_board[SIZE];
vector<vector<char>> display_board(SIZE, vector<char>(SIZE));

// ボードの範囲内かどうかを判定
bool isInBoard(int x, int y) {
    return x > 0 && x <= SIZE && y > 0 && y <= SIZE;
}
// セルが開かれているか旗が立っているかを判定
bool isFlagOrOpen(int x, int y) {
    return !((display_board[x - 1][y - 1] == '-') ||
             (display_board[x - 1][y - 1] == 'F'));
}
// 指定した座標に爆弾があるかどうかを判定
bool isMine(int x, int y) {
    return (judgement_board[y - 1] & (0x80 >> (x - 1)));
}

// ボードの初期化
void initialize(int x, int y, bool debug) {
    for (int y = 0; y < SIZE; y++) {     // y座標のループ
        judgement_board[y] = 0b00000000; // y座標ごとに初期化
        for (int x = 0; x < SIZE; x++) { // x座標のループ
            display_board[x][y] = '-';
        }
    }
    // 爆弾を配置
    srand(time(NULL));
    int mines_placed = 0;
    while (mines_placed < MINES) {
        int y = rand() % SIZE;
        int x = rand() % SIZE;
        if (!(isMine(x, y))) {
            judgement_board[y] |= (0x80 >> x);
            mines_placed++;
        }
    }
}

// ボードの表示
void displayBoard(bool debug) {
    cout << "  ";
    for (int x = 0; x < SIZE; x++) {
        cout << x + 1 << " ";
    }
    cout << endl;
    for (int y = 0; y < SIZE; y++) {
        cout << y + 1 << " ";
        for (int x = 0; x < SIZE; x++) {
            cout << display_board[x][y] << " ";
        }
        cout << endl;
    }

    if (debug) { // judegement_boardの表示
        cout << endl << "Judgement Board" << endl;
        cout << "  ";
        for (int x = 0; x < SIZE; x++) {
            cout << x << " ";
        }
        cout << endl;
        for (int y = 0; y < SIZE; y++) {
            cout << y << " ";
            for (int x = 0; x < SIZE; x++) {
                cout << ((judgement_board[y] & (0x80 >> x)) ? '*' : '-') << " ";
            }
            cout << endl;
        }
    }
}

// 指定した座標の周囲の爆弾の数をカウント
int countMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (isInBoard(x + i, y + j)) {
                if (isMine(x + i, y + j)) {
                    count++;
                }
            }
        }
    }
    return count;
}

void autoOpneCell(int x, int y);

// セルを開く
void openCell(int x, int y) {
    if (isFlagOrOpen(x - 1, y - 1)) {
        return;
    }
    if (isMine(x - 1, y - 1)) {
        display_board[x - 1][y - 1] = '*';
        life--;
        cout << "\033[31m BOOM!! \033[m Your life is " << life << endl;
        return;
    }
    if (countMines(x - 1, y - 1) == 0) {
        autoOpneCell(x - 1, y - 1);
    } else {
        int mine_num = countMines(x - 1, y - 1);
        display_board[x - 1][y - 1] = '0' + mine_num;
    }
}

void autoOpneCell(int x, int y) {
    while (true) {
        bool is_opened = false;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (isInBoard(x + i, y + j)) {
                    if (isFlagOrOpen(x + i, y + j)) {
                        int mine_num = countMines(x + i, y + j);
                        if (mine_num == 0) {
                            display_board[x + i][y + j] = ' ';
                        } else {
                            display_board[x + i][y + j] = '0' + mine_num;
                        }
                        if (mine_num == 0) {
                            x = x + i;
                            y = y + j;
                            // is_opened = true;
                            break;
                        }
                    }
                }
            }
            if (is_opened) {
                break;
            }
        }
        if (!is_opened) {
            break;
        }
    }
}

// 旗を立てるかセルを開くかする
void flagOrOpen(int x, int y, int choice) {
    if (isFlagOrOpen(x, y)) {
        cout << "Error! You cannot open or put a flag here!" << endl;
        return;
    }
    if (choice == 1) {
        openCell(x, y);
    } else if (choice == 2) {
        if (display_board[x][y] == '-') {
            display_board[x][y] = 'F';
        } else if (display_board[x][y] == 'F') {
            display_board[x][y] = '-';
        }
    }
}

int main(void) {
    int x, y, choice;
    initialize(x, y, debug);
    displayBoard(debug);

    while (life > 0) {
        do {
            cout << "1. Open 2. Flag" << endl;
            cout << "Enter x y Open/Flag >>";
            cin >> x >> y >> choice;
            if (!isInBoard(x, y) || (choice != 1 && choice != 2)) {
                cout << "Error! Enter a valid value!" << endl;
            }
        } while (!isInBoard(x, y));

        flagOrOpen(x, y, choice);
        displayBoard(debug);
    }
    if (life == 0) {
        cout << "\033[31m Game Over!! \033[33" << endl;
        // cout << "Do you want to play again? (yes:1, no:0) >>";
        // cin >> choice;
    }
    return 0;
}
