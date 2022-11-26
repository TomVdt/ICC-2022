#include <array>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<double> Distribution;

double entropie(const Distribution& d) {
    double sum(0.0);
    for (const auto& p : d) {
        if (p > 0) {
            sum -= p * log2(p);
        }
    }
    return sum;
}

Distribution calcule_probas(const string& str, bool espaces = false) {
    // A, B, C, ..., Z, ' '
    array<size_t, 27> occurences({0});
    size_t total(0);

    for (auto c : str) {
        if (isalpha(c)) {
            c = toupper(c);
            occurences[c - 'A'] += 1;
            total += 1;
        }
        if (espaces && c == ' ') {
            occurences[26] += 1;
            total += 1;
        }
    }

    Distribution sortie;
    for (const auto& nb : occurences) {
        if (nb > 0) {
            sortie.push_back(nb / (double)total);
        }
    }

    return sortie;
}

int main() {
    Distribution test({1.0, 0.0});

    cout << entropie(calcule_probas("AAAAAAAAAAAAAAAAAAAAAAAAAAA")) << endl;
    cout << entropie(test) << endl;

    return 0;
}