#include <iostream>

using namespace std;

/*
	int FibonacciIteratif(int n) {
		int Fn(0); // stocke F(i) , initialisé par F(0)
		int Fn_1(Fn); // stocke F(i-1), initialisé par F(0)
		int Fn_2(1); // stocke F(i-2), initialisé par F(-1)
		if (n > 0) {
			for (int i(1); i <= n; ++i) {
				Fn = Fn_1 + Fn_2; // pour n>=1 on calcule F(n)=F(n-1)+F(n-2)
				Fn_2 = Fn_1; // et on decale...
				Fn_1 = Fn;
			}
		}
		return Fn;
	}
*/

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
		return 1;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    cout << "Indice de F(n): ";
    cin >> n;

    cout << "F(" << n << ") = " << fibonacci(n) << endl;
}
