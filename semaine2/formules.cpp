#include <iostream>
#include <cmath>

using namespace std;

/*
Écrivez un programme formules.cc qui :
1. demande à l'utilisateur d'entrer un réel ;
2. enregistre la réponse de l'utilisateur dans une variable x de type réel ;
3. teste pour chacune des expressions ci-dessus si elle est définie pour x :
si oui, le programme calcule le résultat de l'expression puis l'affiche ;
sinon, le programme affiche : « Expression i : indéfinie » où i est le
numéro de l'expression considérée.
Testez votre programme avec les valeurs : -1, 0, 1, 2, 3, 8
*/

int main() {

    double x;
    cout << "Nombre réel stp: ";
    cin >> x;

    // Fonction 1
    if (x != 0.0) {
        cout << "Valeur formule 1: " << x / (1 - exp(x)) << endl;
    } else {
        cout << "Expression 1 non-définie pour cette valeur" << endl;
    }

    // Fonction 2
    if (x >= 0.0 && x != 1.0) {
        cout << "Valeur formule 2: " << x * log10(x) * exp(2 / (x - 1)) << endl;
    } else {
        cout << "Expression 2 non-définie pour cette valeur" << endl;
    }

    // Fonction 3
    if (x <= 0 || 8 <= x) {
        cout << "Valeur formule 3: " << (-x-sqrt(x*x-8*x))/(2-x) << endl;
    } else {
        cout << "Expression 3 non-définie pour cette valeur" << endl;
    }

    // Fonction 4
    if ((sin(x) - x/20 != 0.0) and (x != 0.0) and (x*x - 1/x > 0.0) and (log(x*x - 1/x) != 0.0)) {
        cout << "Valeur formule 4: " << sqrt((sin(x) - x/20) * log(x*x - 1/x)) << endl;
    } else {
        cout << "Expression 4 non-définie pour cette valeur" << endl;
    }

    return 0;
}
