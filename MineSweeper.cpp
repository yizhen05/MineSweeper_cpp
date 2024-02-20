#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

// ボードのサイズと爆弾の数
const unsigned int SIZE = 8;
const unsigned int MINES = 10;
// ライフ
unsigned int life = 3;

// 判定用と表示用のボード
// vector<vector<int>> judgement_board(SIZE, vector<int>(SIZE));
unsigned char judgement_board[SIZE];
vector<vector<char>> visualized_board(SIZE, vector<char>(SIZE));

// ボードの範囲内かどうかを判定
bool isInBoard(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}
// セルが開かれているか旗が立っているかを判定
bool isFlagOrOpen(int x, int y) {
    return !(visualized_board[x][y] == '-') && !(visualized_board[x][y] == 'F');
}
// 指定した座標に爆弾があるかどうかを判定
bool isMine(int x, int y) { return (judgement_board[y] & (0x80 >> x)) == 0; }

// ボードの初期化
void initialize() {
    // 計測開始
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            judgement_board[y] = 0b00000000;
            visualized_board[x][y] = '-';
        }
    }
    // 爆弾を配置
    srand(time(NULL));
    int mines_placed = 0;
    while (mines_placed < MINES) {
        int y = rand() % SIZE;
        int x = rand() % SIZE;
        // if ((judgement_board[x] & (0x80 >> n)) == 0) {
        if (!(isMine(x, y))) {
            judgement_board[y] |= (0x80 >> x);
            mines_placed++;
        }
    }
    // 計測終了
    // clock_t end = clock();
    // cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" <<
    // endl;
}

// ボードの表示
void displayBoard() {
    cout << "  ";
    for (int x = 0; x < SIZE; x++) {
        cout << x << " ";
    }
    cout << endl;
    for (int y = 0; y < SIZE; y++) {
        cout << y << " ";
        for (int x = 0; x < SIZE; x++) {
            // cout << board[x][y] << " ";
            cout << visualized_board[x][y] << " ";
        }
        cout << endl;
    }
}

// ボードの範囲内かどうかを判定
bool isInBoard(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

// 指定した座標の周囲の爆弾の数をカウント
int countMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // if (x + 1 >= 0 && x + 1 <= SIZE && y + 1 >= 0 && y + 1 <= SIZE) {
            if (isInBoard(x + i, y + j)) {
                if (judgement_board[x + i] & (0x80 >> (y + j))) {
                    count++;
                }
            }
        }
    }
    return count;
}

// セルを開く
void openCell(int x, int y) {
    if (!(visualized_board[x][y] == '-') && !(visualized_board[x][y] == 'F')) {
        return;
    }
    if (judgement_board[x] & (0x80 >> y)) {
        visualized_board[x][y] = '*';
        life--;
        cout << "\033[31m BOOM!! \033[m Your life is " << life << endl;
        return;
    }
    int MINES = countMines(x, y);
    if (MINES > 0) {
        visualized_board[x][y] = '0' + MINES;
    } else {
        visualized_board[x][y] = ' ';
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
        if (visualized_board[x][y] == '-') {
            visualized_board[x][y] = 'F';
        } else if (visualized_board[x][y] == 'F') {
            visualized_board[x][y] = '-';
        }
    }
}

int main(void) {
    initialize();
    displayBoard();
    // int x, y, choice;
    // while (life > 0) {
    //     do {
    //         cout << "1. Open 2. Flag" << endl;
    //         cout << "Enter x y Open/Flag >>";
    //         cin >> x >> y >> choice;
    //         if (!isInBoard(x, y) || (choice != 1 && choice != 2)) {
    //             cout << "Error! Enter a valid value!" << endl;
    //         }
    //     } while (!isInBoard(x, y));

    //     flagOrOpen(x, y, choice);
    //     displayBoard();
    // }
    return 0;
}
