#include <iostream>

using namespace std;

int main() {
    const int BASE(4);
    double fromage(800.0);
    double eau(2.0);
    double ail(2.0);
    double pain(400.0);

    int nb_convives;
    cout << "Combien de personnes?" << endl;
    cin >> nb_convives;

    cout << "Pour faire une fondue fribourgeoise pour " << nb_convives << " personnes, il vous faut :" << endl;
    cout << " - " << fromage * nb_convives / BASE << " gr de Vacherin fribourgeois" << endl;
    cout << " - " << eau * nb_convives / BASE << " dl d'eau" << endl;
    cout << " - " << ail * nb_convives / BASE << " gousse(s) d'ail" << endl;
    cout << " - " << pain * nb_convives / BASE << " gr de pain" << endl;
    cout << " - " << "du poivre à volonté" << endl;

    return 0;
}
