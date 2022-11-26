#include <iostream>

using namespace std;

/*
1. demande à l'utilisateur d'entrer un réel ;
2. enregistre la réponse de l'utilisateur dans une variable x de type réel ;
3. teste l'appartenance de x à l'ensemble I et affiche le message « x appartient à I »
si c'est le cas, et « x n'appartient pas à I » dans le cas contraire.
Testez votre programme en l'exécutant plusieurs fois de suite en donnant successivement à x les
valeurs -2.5, -1, 0.5, 1, et 1.5.
*/

int main() {

    double x;
    cout << "Nombre réel stp: ";
    cin >> x;

    if (-1.0 <= x and x < 1.0) {
        cout << "x appartient à I" << endl;
    } else {
        cout << "x n'appartient pas à I" << endl;
    }

    return 0;
}
