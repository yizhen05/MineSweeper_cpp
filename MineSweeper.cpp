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
                if (judgement_board[x + i][y + j] == -1) count++;
            }
        }
    }
    return count;
}

// セルセルを開く
void open(int x, int y) {
    if (visualized_board[x][y] != '-') return;

    if (judgement_board[x][y] == '*') {
        visualized_board[x][y] = '*';
        life--;
        cout << "\033[31m BOOM!! \033[m Your life is " << life << endl;
        return;
    }
    int mineNum = countMines(x, y);
    if (mineNum > 0) {
        // board[x][y]='0'+mines;
        visualized_board[x][y] = '0' + mineNum;
    } else {
        // board[x][y] = ' ';
        visualized_board[x][y] = ' ';

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                open(x + i, y + j);
            }
        }
    }
}

// 旗を立てるかセルを開くかを選択
void flagOrOpen(int x, int y) {
    int choice;
    do {
        cout << "1. Open 2. Flag >>";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "Error enter a valid value!" << endl;
        }

    } while (choice != 1 && choice != 2);
    if (choice == 1) {
        open(x, y);
    } else {
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
    int x, y;
    while (life > 0) {
        do {
            cout << "Enter x,y>>";
            cin >> x >> y;
            if (!isInBoard(x, y)) {
                cout << "Error enter a valid value";
            }
        } while (!isInBoard(x, y));
        flagOrOpen(x, y);
        displayBoard();
    }
    return 0;
}
