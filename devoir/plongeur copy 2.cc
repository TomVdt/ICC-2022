#include <cmath>  // pour exp()
#include <iostream>
#include <string>
using namespace std;

// ======================================================================

// Types et constantes
struct Conditions {
    double profondeur;
    double vitesse;
    double temps;
};

struct Diver {
    string nom;
    double masse;
    double volume;
    double acceleration;
    Conditions conditions;
};

struct Status {
    bool profondeur_atteinte;
    bool vitesse_max_atteinte;
    bool ballon_gonfle;
};

constexpr double VOLUME_BALLON(0.0375);

// Prototypes

void display(const Diver& d);
void dive(Diver d);
void evolve(Diver& d, const Conditions& conditions_initiales);
void message(const Diver& d, const string& mess, double valeur, const string& unitees);
void update_status(Diver& d, Conditions& conditions_initiales, Status& status);
double coefficient_archimede(double volume, double masse);

// Implémentations

// Affiche les données du plongeur (temps, profondeur, vitesse, acceleration)
void display(const Diver& d) {
    cout << d.conditions.temps << ", "
         << d.conditions.profondeur << ", "
         << d.conditions.vitesse << ", "
         << d.acceleration << endl;
}

// Affiche un message pour un certain état donné
void message(const Diver& d, const string& mess, double valeur, const string& unite) {
    cout << "## (t = "
         << d.conditions.temps << " s) "
         << d.nom << " "
         << mess << " ("
         << valeur << " "
         << unite << ")"
         << endl;
}

// Calcul du µ des équations
double coefficient_archimede(double volume, double masse) {
    return 1.0 - 1000.0 * (volume / masse);
}

// Boucle principale de la simulation
void dive(Diver d) {
    // Vérification des données d'entrée
    // Une masse négative ou nulle n'a pas trop de sens dans ce contexte
    // (en plus d'éviter la division par 0 pour le "coefficient d'archimede")
    if (d.masse <= 0.0) {
        cerr << "La masse du plongeur ne peut pas être négative ou nulle!" << endl;
        return;
    }
    // Un volume négatif ou nul n'a pas de sens
    if (d.volume <= 0.0) {
        cerr << "Le volume du plongeur ne peut pas être négatif ou nul!" << endl;
        return;
    }

    // Vérification de conditions initiales cohérentes
    // Les equations sont seulement valables dans l'eau, on veut donc commencer
    // la simulation dans l'eau
    if (d.conditions.profondeur > 0.0) {
        cerr << "Le plongeur doit commencer dans l'eau!" << endl;
        return;
    }
    // Pour éviter que le plongeur sorte de l'eau avant de couler, on veut une vitesse positive
    if (d.conditions.vitesse < 0.0) {
        cerr << "Le plongeur doit commencer avec une vitesse vers le bas! (vitesse positive ou nulle)" << endl;
        return;
    }

    // Éviter une boucle infinie
    // Si la réduction du poids par la poussée d'Archimède est positive après le
    // gonflage du ballon, le plongeur continuera à couler malgré le ballon
    // Si elle est nulle, le plongeur reste sur place
    if (coefficient_archimede(d.volume + VOLUME_BALLON, d.masse) >= 0.0) {
        cerr << "Le plongeur ne pourra pas remonter à l'aide du ballon! (volume trop petit par rapport à la masse)" << endl;
        return;
    }
    // Si ce coefficient est nul initialement, le plongeur ne coule pas!
    // Cas spécial: la vitesse initiale est suffisante pour dépasser les -43m
    // Les autres cas sont traités correctement dans la simulation
    if (coefficient_archimede(d.volume, d.masse) == 0.0 && !(d.conditions.profondeur - d.conditions.vitesse < -43.0)) {
        cerr << "Le plongeur reste en équilibre et ne dépassera pas les -43m! (les forces s'équilibrent, profondeur max: "
             << d.conditions.profondeur - d.conditions.vitesse
             << " m)" << endl;
        return;
    }

    // La simulation peut maintenant avoir lieu
    // Copie des conditions du plongeur pour les conditions initiales
    Conditions conditions_initiales(d.conditions);

    Status status({false, false, false});

    // do ... while pour accepter le cas profondeur = 0
    // (conflicterait avec la fin de la simulation, profondeur >= 0)
    do {
        display(d);
        evolve(d, conditions_initiales);
        update_status(d, conditions_initiales, status);
    } while (d.conditions.profondeur < 0.0);

    // On est sorti de l'eau
    message(d, "est de retour à la surface", d.conditions.profondeur, "m");
}

// Calculs pour l'évolution des parametres du plongeur
void evolve(Diver& d, const Conditions& conditions_initiales) {
    ++d.conditions.temps;

    // Des alias pour alleger les formules
    const double& p0(conditions_initiales.profondeur);
    const double& v0(conditions_initiales.vitesse);
    const double& t0(conditions_initiales.temps);

    // Quelques constantes qui apparaissent plusieurs fois dans les formules
    constexpr double g(9.81);
    const double t(t0 - d.conditions.temps);
    const double mu(coefficient_archimede(d.volume, d.masse));
    const double alpha(exp(t));
    const double k(v0 - g * mu);

    // Application des formules
    d.conditions.vitesse = (alpha * k) + (g * mu);
    d.acceleration = -(alpha * k);
    d.conditions.profondeur = p0 + (k * (alpha - 1)) + (t * g * mu);
}

// Met à jour l'état et affiche des messages quand certaines conditions sur la plongée sont atteintes
void update_status(Diver& d, Conditions& conditions_initiales, Status& status) {
    // Seulement afficher le message si le plongeur descend!
    if (!status.vitesse_max_atteinte && d.acceleration < 1e-5 && d.conditions.vitesse > 0) {
        status.vitesse_max_atteinte = true;
        message(d, "a atteint sa vitesse maximale", d.acceleration, "ms-2");
    }
    if (!status.profondeur_atteinte && d.conditions.profondeur < -40.0) {
        status.profondeur_atteinte = true;
        message(d, "a atteint la profondeur desirée", d.conditions.profondeur, "m");
    }
    if (!status.ballon_gonfle && d.conditions.profondeur < -43.0) {
        status.ballon_gonfle = true;
        // Nouvelles conditions "initiales"
        d.volume += VOLUME_BALLON;
        conditions_initiales.profondeur = d.conditions.profondeur;
        conditions_initiales.vitesse = 0.0;
        conditions_initiales.temps = d.conditions.temps;
        message(d, "s'arrête et gonfle son ballon", d.conditions.profondeur, "m");
    }
}

// ======================================================================
// Ce main() NE DOIT PAS ÊTRE MODIFIÉ !
// int main() {
//   Diver jacques({ "Jacques"s, 90.0, 0.075, 0.0, {-1.2, 0.8, 0} });
//   dive(jacques);
//   return 0;
// }

void annoncer_test(const Diver& d) {
    cout << d.nom << "(m="
         << d.masse << ", v="
         << d.volume << ", acc="
         << d.acceleration << ") plonge avec conditions profondeur "
         << d.conditions.profondeur << ", vitesse "
         << d.conditions.vitesse << ", temps "
         << d.conditions.temps << endl;
}

void test(Diver d) {
    annoncer_test(d);
    dive(d);
    cout << endl;
}

int main() {
    cout << "Normal" << endl;
    test({"Jacques"s, 90.0, 0.075, 0.0, {-1.2, 0.8, 0}});

    cout << "Tout nul" << endl;
    test({"Michel"s, 90.0, 0.075, 0.0, {0.0, 0.0, 0}});

    cout << "Masses et volumes chelous" << endl;
    test({"Michel"s, 0.0, 0.075, 0.0, {-1.2, 0.8, 0}});
    test({"Michel"s, 90.0, 0.0, 0.0, {-1.2, 0.8, 0}});

    cout << "Conditions initiales cheloues" << endl;
    cout << "En hauteur" << endl;
    test({"Michel"s, 90.0, 0.075, 0.0, {1.2, 0.8, 0}});
    test({"Michel"s, 90.0, 0.075, 0.0, {3, -0.8, 0}});
    cout << "Vitesse haute, sous l'eau" << endl;
    test({"Michel"s, 90.0, 0.075, 0.0, {-1.2, 5.0, 0}});
    test({"Michel"s, 90.0, 0.075, 0.0, {-1.2, 100.0, 0}});
    test({"Michel"s, 90.0, 0.075, 0.0, {-1.2, -5.0, 0}});
    cout << "Vitesse initiale nulle" << endl;
    test({"Michel"s, 90.0, 0.075, 0.0, {-1.2, 0.0, 0}});
    cout << "Profondeur initiale nulle" << endl;
    test({"Michel"s, 90.0, 0.075, 0.0, {0.0, 0.8, 0}});

    cout << "t0 != 0" << endl;
    test({"Michel"s, 90.0, 0.075, 0.0, {-1.2, 0.8, -32}});
    test({"Michel"s, 90.0, 0.075, 0.0, {-1.2, 0.8, 69}});

    cout << "Valeurs cheloues, flotte naturellement" << endl;
    test({"Michel"s, 90.0, 0.75, 420.69, {-1.2, 0.8, 0}});
    test({"Michel"s, 90.0, 0.75, 0.0, {-1.2, 0.8, 0}});
    test({"Michel"s, 90.0, 0.100, 0.0, {-1.0, -0.5, 0}});

    cout << "Valeurs cheloues, coule même avec le ballon aka \"la brique\"" << endl;
    test({"Michel"s, 500.0, 0.400, 0.0, {-1.2, 0.8, 0}});

    cout << "Poussée d'archimède compensant le poids" << endl;
    test({"Michel"s, 100.0, 0.100, 0.0, {-1.2, 0.0, 0}});

    cout << "Montées et descentes lentes" << endl;
    test({"Michel"s, 100.0, 0.101, 0.0, {-1.2, 0.0, 0}});
    test({"Michel"s, 100.0, 0.101, 0.0, {-1.2, 0.0, 420}});
    test({"Michel"s, 100.0, 0.095, 0.0, {-1.2, 0.0, 0}});

    cout << "Vitesse initiale forte pour atteindre -43m, malgré equilibre" << endl;
    test({"Michel"s, 100.0, 0.100, 0.0, {-1.0, 42.0, 0}});
    test({"Michel"s, 100.0, 0.105, 0.0, {-1.0, 43.0, 0}});
    test({"Michel"s, 100.0, 0.105, 0.0, {-1.0, 0.0, 0}});

    return 0;
}
