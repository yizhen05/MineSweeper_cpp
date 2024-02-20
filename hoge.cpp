#include <bits/stdc++.h>

using namespace std;
int main() {

    class hoge {
      public:
        int a, b;
        hoge() : a(1), b(2) {}
    };

    hoge hoge;
    cout << hoge.a << std::endl;
    cout << hoge.b << std::endl;

    return 0;
}
