#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
//hogehoge
using namespace std;

const int SIZE = 10;
const int MINES = 10;

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
    while (minesPlaced < MINES) {
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
            cout << showboard[x][y] << " ";
        }
        cout << endl;
    }
}

int countMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (x + 1 >= 0 && x + 1 <= SIZE && y + 1 >= 0 && y + 1 <= SIZE) {
                if (board[x + i][y + j] == '*') count++;
            }
        }
    }
    return count;
}

void open(int x, int y) {
    int mines = countMines(x, y);
    if (mines > 0) {
        showboard[x][y] = '0' + mines;
    } else {
        showboard[x][y] = ' ';
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                open(x + i, y + j);
            }
        }
    }
}

int main() {
    initialize();
    displayBoard();
    int x, y;
    do {
        cout << "Enter x,y>>";
        cin >> x >> y;
        if (x < 0 || x > SIZE || y < 0 || y > SIZE) {
            cout << "Error enter a valid value";
        }
    } while (x < 0 || x > SIZE || y < 0 || y > SIZE);
    open(x, y);
    displayBoard();
    return 0;
}
