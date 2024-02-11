#include <bits/stdc++.h>

// 地雷の数

using namespace std;

int main(void) {
    int vertical, horizontal;
    cout << "MineSweeper" << endl;
    cout << "vertical horizontal>>";
    cin >> vertical >> horizontal;
    int mineNum = vertical * horizontal / 5;
    // 判定用フィールド
    int isfield[vertical][horizontal];
    char field[vertical][horizontal];
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
    for (int i = 0; i < mineNum; i++) {
        isfield[minePos[i][1]][minePos[i][0]] = -1;
    }
    // フィールドのつくるお
    for (int i = 0; i < vertical; i++) {
        for (int j = 0; j < horizontal; j++) {
            field[i][j] = '-';
            isfield[i][j] = 0;
        }
    }

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
}