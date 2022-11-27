#include <cmath>  // pour exp()
#include <iostream>
#include <string>
using namespace std;

// ======================================================================

// =============== Types et constantes ===============

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
constexpr double PROFONDEUR_DESIREE(-40.0);
constexpr double PROFONDEUR_BALLON(-43.0);
constexpr double SEUIL_VMAX(1e-5);

// =============== Prototypes ===============

void display(const Diver& d);
void dive(Diver d);
void evolve(Diver& d, const Conditions& conditions_initiales);
void message(const Diver& d, const string& mess, double valeur, const string& unitees);
void update_status(Diver& d, Conditions& conditions_initiales, Status& status);

// =============== Implémentations ===============

void display(const Diver& d) {
    cout << d.conditions.temps << ", "
         << d.conditions.profondeur << ", "
         << d.conditions.vitesse << ", "
         << d.acceleration << endl;
}

void message(const Diver& d, const string& mess, double valeur, const string& unite) {
    cout << "## (t = "
         << d.conditions.temps << " s) "
         << d.nom << " "
         << mess << " ("
         << valeur << " "
         << unite << ")"
         << endl;
}

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
    // L'accélération initiale n'affecte pas la simulation

    // Vérification de conditions initiales cohérentes
    // Les equations sont seulement valables dans l'eau, on veut donc commencer la simulation dans l'eau
    if (d.conditions.profondeur > 0.0) {
        cerr << "Le plongeur doit commencer dans l'eau!" << endl;
        return;
    }
    // La vitesse initiale peut prendre n'importe quelle valeur, puisque:
    //  - soit le plongeur monte et sort de l'eau (fin)
    //  - soit le plongeur monte (on ne compte que vmax pour la descente), redescend, puis remonte (fin)
    //  - soit le plongeur descend, puis remonte (fin)
    // On a que des écarts de temps dans les equations, le temps initial n'a donc pas d'importance

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

    // Fin de la simulation, on est sorti de l'eau
    message(d, "est de retour à la surface", d.conditions.profondeur, "m");
}

void evolve(Diver& d, const Conditions& conditions_initiales) {
    ++d.conditions.temps;

    // Des alias pour alleger les formules
    const double& p0(conditions_initiales.profondeur);
    const double& v0(conditions_initiales.vitesse);
    const double& t0(conditions_initiales.temps);

    // Quelques constantes qui apparaissent plusieurs fois dans les formules
    constexpr double g(9.81);
    const double t(t0 - d.conditions.temps);
    const double mu(1.0 - 1000.0 * (d.volume / d.masse));
    const double alpha(exp(t));
    const double k(v0 - g * mu);

    // Application des formules
    d.conditions.vitesse = (alpha * k) + (g * mu);
    d.acceleration = -(alpha * k);
    d.conditions.profondeur = p0 + (k * (alpha - 1)) + (t * g * mu);
}

void update_status(Diver& d, Conditions& conditions_initiales, Status& status) {
    // Seulement afficher le message si le plongeur descend (vitesse > 0) et qu'il n'a pas déjà été affiché
    if (!status.vitesse_max_atteinte && d.acceleration < SEUIL_VMAX && d.conditions.vitesse > 0) {
        status.vitesse_max_atteinte = true;
        message(d, "a atteint sa vitesse maximale", d.acceleration, "ms-2");
    }
    if (!status.profondeur_atteinte && d.conditions.profondeur < PROFONDEUR_DESIREE) {
        status.profondeur_atteinte = true;
        message(d, "a atteint la profondeur desirée", d.conditions.profondeur, "m");
    }
    if (!status.ballon_gonfle && d.conditions.profondeur < PROFONDEUR_BALLON) {
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
int main() {
    Diver jacques({ "Jacques"s, 90.0, 0.075, 0.0, {-1.2, 0.8, 0} });
    dive(jacques);
    return 0;
}
