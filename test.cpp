#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

class MineSweeper {
  private:
    // ボードのサイズと爆弾の数
    const unsigned int SIZE;
    const unsigned int MINENUM;

    // 判定用と表示用のボード
    // vector<vector<int>> judgement_board(SIZE, vector<int>(SIZE));
    unsigned char *judgement_board;
    vector<vector<char>> visualized_board;

    // ボードの範囲内かどうかを判定
    bool isInBoard(int x, int y) {
        return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
    }
    // セルが開かれているか旗が立っているかを判定
    bool isFlagOrOpen(int x, int y) {
        return !(visualized_board[x][y] == '-') &&
               !(visualized_board[x][y] == 'F');
    }
    // 指定した座標に爆弾があるかどうかを判定
    bool isMine(int x, int y) {
        return (judgement_board[y] & (0x80 >> x)) == 0;
    }
    int countMines(int x, int y) {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                // if (x + 1 >= 0 && x + 1 <= SIZE && y + 1 >= 0 && y + 1 <=
                // SIZE) {
                if (isInBoard(x + i, y + j)) {
                    if (isMine(x + i, y + j)) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
    // セルを開く
    void openCell(int x, int y) {
        if (isFlagOrOpen(x, y)) {
            return;
        }
        if (isMine(x, y)) {
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

  public:
    int life;
    MineSweeper() : SIZE(8), MINENUM(10), life(3) {
        judgement_board = new unsigned char[SIZE];
        visualized_board = vector<vector<char>>(SIZE, vector<char>(SIZE));
    }
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
        int minesPlaced = 0;
        while (minesPlaced < MINENUM) {
            int y = rand() % SIZE;
            int x = rand() % SIZE;
            // if ((judgement_board[x] & (0x80 >> n)) == 0) {
            if (!(isMine(x, y))) {
                judgement_board[y] |= (0x80 >> x);
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
};

int main() {
    MineSweeper ms;
    ms.initialize();
    ms.displayBoard();

    int x, y, choice;
    while (ms.life > 0) {
        cout
            << "Enter the x and y coordinates and the choice (1: open, 2: flag)"
            << endl;
        cin >> x >> y >> choice;
        ms.flagOrOpen(x, y, choice);
        ms.displayBoard();
    }

    return 0;
}