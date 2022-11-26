#include <iostream>
#include <vector>

using namespace std;

void swap(int i, int j, vector<double>& t) {
    double tmp(t[i]);
    t[i] = t[j];
    t[j] = tmp;
}

vector<double> shellsort(vector<double> const& l) {
    vector<double> sorted = l;
    int j(0);
    for (int k(l.size() / 2); k >= 1; k /= 2) {
        for (int i(k); i <= l.size(); i++) {
            j = i - k;
            while (j > 0) {
                if (sorted[j - 1] > sorted[j + k - 1]) {
                    swap(j - 1, j + k - 1, sorted);
                    j -= k;
                } else {
                    j = 0;
                }
            }
        }
    }
    return sorted;
}

int main() {
    vector<double> l = {3, 5, 12, -1, 215, -2, 17, 8, 3, 5, 13, 18, 23, 5, 4, 3, 2, 1};
    vector<double> t(shellsort(l));
    for (auto val : t) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}