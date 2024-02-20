#include <bits/stdc++.h>

using namespace std;

class hoge {
    int a;
    int b;
    hoge(int a, int b) {
        this->a = a;
        this->b = b;
    }
};
int main() {
    for (int i = 0; i < 10; i++) {
        cout << "Hello World!" << endl;
    }
    hoge hoge(1, 2);
    hoge.a;
    return 0;
}