#include <iostream>
using namespace std;

void test2(int t[], size_t size) {
    for (size_t i(0); i < size; i++) {
        for (int j(0); j < 4; j++) {
            cout << (char)((t[i] >> (3-j)) & 0x7f);
        }
    }
}

int main() {
    int test[5] = {41, 42, 44, 45, 46};

    test2(test, 1293);
    cout << endl;
    return 0;
}