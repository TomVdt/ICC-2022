#include <iostream>
#include <string>

using namespace std;

struct Complex {
    double re;
    double im;
};

Complex addition(Complex z, Complex w) {
    return {z.re + w.re, z.im + w.im};
}

Complex soustraction(Complex z, Complex w) {
    return {z.re - w.re, z.im - w.im};
}

Complex multiplication(Complex z, Complex w) {
    return {z.re * w.re - z.im * w.im, z.re * w.im + z.im * w.re};
}

Complex division(Complex z, Complex w) {
    return {(z.re * w.re + z.im * w.im) / (w.re * w.re + w.im * w.im), (z.im * w.re - z.re * w.im) / (w.re * w.re + w.im * w.im)};
}

void show(Complex z) {
    cout << z.re << (z.im >= 0 ? "+" : "") << z.im << "i" << endl;
}

int main() {
    show(division({2, -3}, {1, 1}));
    return 0;
}