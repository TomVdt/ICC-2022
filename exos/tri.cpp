#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> List;

List merge(List a, List b) {
    if (a.empty()) {
        return b;
    }
    if (b.empty()) {
        return a;
    }

    auto back(b.back());
    b.pop_back();
    List out(merge(b, a));
    out.push_back(back);

    return out;
}

void print(List a) {
    for (auto el : a) {
        cout << el << " ";
    }
    cout << endl;
}

int main() {
    List a = {1};
    List b = {9, 8, 5, 2, 4, 5, 6, 6, 3, 2};

    print(merge(a, b));

    return 0;
}