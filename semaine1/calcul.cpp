#include <iostream>

using namespace std;

/*
1. déclare les variables x et y de type entier ;
2. déclare les variables a, b, c et d de type réel ;
3. affecte la valeur 2 à x et 4 à y ;
4. calcule la somme, la différence, le produit, et le quotient de x par y, et affecte les résultats à a, b, c et d ;
5. affiche les valeurs de a, b, c et d.
*/

int main() {
    double x, y;
    double a, b, c, d;

    x = 2;
    y = 4;

    a = x + y;
    b = x - y;
    c = x * y;
    d = x / y;

    cout << a << ", " << b << ", " << c << ", " << d << ", " << endl;

    return 0;
}
