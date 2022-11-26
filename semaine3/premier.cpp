#include <cmath>
#include <iostream>

using namespace std;

int main() {
    int n;
    cout << "Quel entier bro? ";
    cin >> n;

    int D(0);

    for (int i(2); i < sqrt(n); ++i) {
        if (n % i == 0) {
            D = i;
            break;
        }
    }
    if (D != 0) {
        cout << n << " n'est pas premier, car il est divisible par " << D << endl;
    } else {
        cout << n << " est premier" << endl;
    }
    return 0;
}
