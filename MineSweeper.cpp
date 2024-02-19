#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// ボードのサイズと爆弾の数
const unsigned int SIZE = 10;
const unsigned int MINENUM = 10;
// ライフ
unsigned int life = 3;

// 判定用と表示用のボード
vector<vector<int>> judgement_board(SIZE, vector<int>(SIZE));
vector<vector<char>> visualized_board(SIZE, vector<char>(SIZE));

// ボードの初期化
void initialize() {
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            judgement_board[x][y] = '1';
            visualized_board[x][y] = '-';
        }
    }
    // 爆弾を配置
    srand(time(NULL));
    int minesPlaced = 0;
    while (minesPlaced < MINENUM) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (judgement_board[x][y] != -1) {
            judgement_board[x][y] = -1;
            minesPlaced++;
        }
    }
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
                if (judgement_board[x + i][y + j] == -1) {
                    count++;
                }
            }
        }
    }
    return count;
}

// セルを開く
void openCell(int x, int y) {
    if (visualized_board[x][y] != '-') {
        return;
    }
    if (judgement_board[x][y] == -1) {
        visualized_board[x][y] = '*';
        life--;
        cout << "\033[31m BOOM!! \033[m Your life is " << life << endl;
        return;
    }
    int mineNum = countMines(x, y);
    if (mineNum > 0) {
        visualized_board[x][y] = '0' + mineNum;
    } else {
        visualized_board[x][y] = ' ';
    }
}

// 旗を立てるかセルを開くかする
void flagOrOpen(int x, int y, int choice) {
    if (!(visualized_board[x][y] == '-') && !(visualized_board[x][y] == 'F')) {
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
    int x, y, choice;
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
        displayBoard();
    }
    return 0;
}
