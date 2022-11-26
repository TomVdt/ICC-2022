#include <string.h>

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Mat;

int somme_consecutifs_max(vector<int> in) {
    int max(0);
    int sum(0);
    for (auto x : in) {
        if (x == 0) {
            sum = 0;
        }
        sum += x;
        max = sum > max ? sum : max;
    }
    return max;
}

vector<size_t> lignes_max(Mat in) {
    vector<size_t> out;
    int max(0);
    for (int i(0); i < in.size(); i++) {
        int n = somme_consecutifs_max(in[i]);
        if (n > max) {
            out.clear();
            max = n;
        }
        if (n == max) {
            out.push_back(i);
        }
    }
    return out;
}

Mat tranches_max(Mat in) {
    Mat out;
    for (auto i : lignes_max(in)) {
        out.push_back(in[i]);
    }
    return out;
}

int main() {
    Mat t = {
        {0, 0, 0, 0}};

    for (auto ligne : tranches_max(t)) {
        for (auto i : ligne) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}