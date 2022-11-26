#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double a0, a1, a2;
    cout << "Valeur de a0: ";
    cin >> a0;
    cout << "Valeur de a1: ";
    cin >> a1;
    cout << "Valeur de a2: ";
    cin >> a2;

    double Q = (3.0 * a1 - a2 * a2) / 9.0;
    double R = (9 * a2 * a1 - 27 * a0 - 2 * a2 * a2* a2) / 54;
    double D = Q * Q * Q + R * R;

    double z1(0), z2(0), z3(0);

    if (D > 0.0) {
        // 3 solutions
        double theta = acos(R / sqrt(pow(-Q, 3)));
        z1 = 2 * sqrt(-Q) * cos(theta/3) - a2/3;
        z2 = 2 * sqrt(-Q) * cos((theta + 2 * M_PI) / 3) - a2/3;
        z3 = 2 * sqrt(-Q) * cos((theta + 4 * M_PI)/3) - a2/3;
    } else {
        double S = pow(R + sqrt(D), 1.0 / 3.0);
        double T = pow(R - sqrt(D), 1.0 / 3.0);

        if (D == 0.0 && S + T != 0.0) {
            // 2 solutions
            z1 = S + T - a2/3;
            z2 = -(S + T) / 2 - a2/3;
        } else {
            // 1 solution
            z1 = S + T - a2/3;
        }
    }
    
    cout << "z1: " << z1 << "\nz2: " << z2 << "\nz3: " << z3 << endl;
}
