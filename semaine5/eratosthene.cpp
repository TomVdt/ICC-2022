#include <iostream>
#include <vector>

using namespace std;

vector<bool> eratosthene(int n) {
    vector<bool> removed(n, false);
	removed[0] = true;
	removed[1] = true;
    for (int i(2); i <= n; i++) {
        if (!removed[i]) {
            for (int j(i + i); j <= n; j += i) {
                removed[j] = true;
                cout << j << endl;
            }
        }
    }

    return removed;
}

int main() {
    constexpr int n(100);

    auto removed(eratosthene(n));

    for (int i(0); i < n; i++) {
        if (!removed[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}