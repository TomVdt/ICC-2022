#include <cmath>
#include <iostream>

using namespace std;

// 1. Définition du type Conditions
struct Conditions {
    double profondeur;
    double vitesse;
    double temps;
};

// 2. Définition du type Diver
struct Diver {
    string nom;
    double masse;
    double volume;
    double acceleration;
    Conditions conditions;
};

// 3. Définition de la fonction display()
void display(Diver plongeur) {
    cout << plongeur.conditions.temps << ", " << plongeur.conditions.profondeur << ", " << plongeur.conditions.vitesse << ", " << plongeur.acceleration << endl;
}

// 4. Définition de la fonction dive()
void dive(Diver plongeur) {
    display(plongeur);
}

// 5. Définition de la fonction evolve()
void evolve(Diver& plongeur, Conditions conditions_initiales) {
    // Calcul des valeurs intermédiaires
    double g = 9.81;
    double mu = 1 - 1000 * plongeur.volume / plongeur.masse;
    double alpha = exp(conditions_initiales.temps - plongeur.conditions.temps);

    // Calcul des équations d'évolution
    plongeur.conditions.vitesse = alpha * (conditions_initiales.vitesse - g * mu) + g * mu;
    plongeur.acceleration = -alpha * (conditions_initiales.vitesse - g * mu);
    plongeur.conditions.profondeur = conditions_initiales.profondeur + (conditions_initiales.vitesse - g * mu) * (alpha - 1) + (conditions_initiales.temps - plongeur.conditions.temps) * g * mu;

    // Incrémentation du temps de plongée
    plongeur.conditions.temps++;
}

// 6. Mise à jour de la fonction dive()
void dive(Diver& plongeur, Conditions conditions_initiales) {
    // Calcul de l'évolution de la plongée
    while (plongeur.conditions.profondeur > 0) {
        evolve(plongeur, conditions_initiales);
    }

    // Affichage des informations du plongeur
    display(plongeur);
}

int main() {
    // Initialisation du plongeur jacques
    Diver jacques = {"Jacques", 90, 0.075, 0, {-1.2, 0.8, 0}};

    // Plongée de jacques
    dive(jacques, {-1.2, 0.8, 0});

    return 0;
}