#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 10;
const int MINENUM = 10;
int life = 3;

vector<vector<char>> board(SIZE, vector<char>(SIZE));
vector<vector<char>> showboard(SIZE, vector<char>(SIZE));

void initialize() {
    // Initialize board
    // 全部ハイフンをいれる
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            board[x][y] = '-';
            showboard[x][y] = '-';
        }
    }
    // 爆弾の配置
    srand(time(NULL));
    int minesPlaced = 0;
    while (minesPlaced < MINENUM) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (board[x][y] != '*') {
            board[x][y] = '*';
            minesPlaced++;
        }
    }
}

void displayBoard() {
    // Display board
    cout << "  ";
    for (int x = 0; x < SIZE; x++) {
        cout << x << " ";
    }
    cout << endl;
    for (int y = 0; y < SIZE; y++) {
        cout << y << " ";
        for (int x = 0; x < SIZE; x++) {
            // cout << board[x][y] << " ";
            cout << showboard[x][y] << " ";
        }
        cout << endl;
    }
}

bool inBoard(int x, int y) { return x >= 0 && x < SIZE && y >= 0 && y < SIZE; }

int countMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // if (x + 1 >= 0 && x + 1 <= SIZE && y + 1 >= 0 && y + 1 <= SIZE) {
            if (inBoard(x + i, y + j)) {
                if (board[x + i][y + j] == '*') count++;
            }
        }
    }
    return count;
}

void open(int x, int y) {
    if (showboard[x][y] != '-') return;

    if (board[x][y] == '*') {
        showboard[x][y] = '*';
        life--;
        cout << "\033[31m BOOM!! \033[m Your life is " << life << endl;
        return;
    }
    int mineNum = countMines(x, y);
    if (mineNum > 0) {
        // board[x][y]='0'+mines;
        showboard[x][y] = '0' + mineNum;
    } else {
        // board[x][y] = ' ';
        showboard[x][y] = ' ';

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                open(x + i, y + j);
            }
        }
    }
}
void flagOrOpen(int x, int y) {
    int flag;
    cout << "1:Flag 2:Open>>";
    cin >> flag;
    if (flag == 1) {
        showboard[x][y] = 'F';
    } else if (flag == 2) {
        open(x, y);
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
            if (!inBoard(x, y)) {
                cout << "Error enter a valid value";
            }
        } while (!inBoard(x, y));
        flagOrOpen(x, y);
        displayBoard();
    }
    return 0;
}
