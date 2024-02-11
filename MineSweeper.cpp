#include <bits/stdc++.h>

#define vertical 10
#define horizontal 10
#define mineNum 10

using namespace std;
int jadgeField[vertical][horizontal];
char field[vertical][horizontal];
// int life = 3;

void isMine(int x, int y) {
    if (jadgeField[y][x] == -1) {
        cout << "Boom!" << endl;
        cout << "\x1b[31mGame Over\x1b[39m" << endl;
    } else {
        field[y][x] = ' ';
    }
    // 回りの八個のそれぞれの周りの地雷の数を数える
    int mineCount = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (y + i >= 0 && y + i < vertical && x + j >= 0 &&
                x + j < horizontal) {
                if (jadgeField[y + i][x + j] == -1) mineCount++;
            }
        }
    }

    // int mineCount = 0;
    // if (y - 1 >= 0 && x - 1 >= 0) {
    //     if (jadgeField[y - 1][x - 1] == -1) mineCount++;
    //     if (jadgeField[y - 1][x] == -1) mineCount++;
    //     if (jadgeField[y - 1][x + 1] == -1 && x + 1 < horizontal)
    //     mineCount++; if (jadgeField[y][x - 1] == -1) mineCount++;
    // }
    // if (y + 1 < vertical && x + 1 < horizontal) {
    //     if (jadgeField[y][x + 1] == -1) mineCount++;
    //     if (jadgeField[y + 1][x - 1] == -1 && y + 1 < vertical) mineCount++;
    //     if (jadgeField[y + 1][x] == -1) mineCount++;
    //     if (jadgeField[y + 1][x + 1] == -1) mineCount++;
    // }
    char test = mineCount + '0';
    cout << "test::" << test << endl;
    if (mineCount != 0) field[y][x] = mineCount + '0';
    cout << field[y][x] << endl;
    // field[y][x] = char(mineCount);
}

int main(void) {
    cout << "MineSweeper" << endl;
    // 地雷の位置(minePos[地雷の固有番号][2(x,y)])
    int minePos[mineNum][2];
    // 地雷の座標をランダムに重複なく決定
    srand((unsigned)time(NULL));
    for (int i = 0; i < mineNum; i++) {
        int x, y;
        bool isSame;
        do {
            isSame = false;
            x = rand() % horizontal;
            y = rand() % vertical;
            for (int j = 0; j < i; j++) {
                if (minePos[j][0] == x && minePos[j][1] == y) {
                    isSame = true;
                    break;
                }
                cout << "\x1b[31mCreate a field...\x1b[39m" << endl;
            }
        } while (isSame);
        minePos[i][0] = x;
        minePos[i][1] = y;
    }

    // フィールドのつくるお
    for (int i = 0; i < vertical; i++) {
        for (int j = 0; j < horizontal; j++) {
            field[i][j] = '-';
            jadgeField[i][j] = 0;
        }
    }
    // 地雷おくんご
    for (int i = 0; i < mineNum; i++) {
        jadgeField[minePos[i][1]][minePos[i][0]] = -1;
    }
    // デバッグ用に(2,5)に地雷を置く
    jadgeField[2][5] = -1;

    // フィールドの表示
    cout << "  ";
    for (int i = 0; i < horizontal; i++) cout << i << " ";
    cout << endl;

    for (int i = 0; i < vertical; i++) {
        cout << i;
        for (int j = 0; j < horizontal; j++) {
            cout << " " << field[i][j];
        }
        cout << endl;
    }

    int k = 0;
    while (k < 5) {
        cout << "enter the coordinates to check>>";
        int x, y;
        cin >> x >> y;
        isMine(x, y);
        // フィールドの表示
        cout << "  ";
        for (int i = 0; i < horizontal; i++) cout << i << " ";
        cout << endl;
        for (int i = 0; i < vertical; i++) {
            cout << i;
            for (int j = 0; j < horizontal; j++) {
                cout << " " << field[i][j];
            }
            cout << endl;
        }
        k++;
    }

    return 0;
}