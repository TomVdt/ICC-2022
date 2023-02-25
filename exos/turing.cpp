#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef string Bande;
typedef int Etat;
typedef int Tete;

struct Transition {
    Etat etat;
    char caractere;
    int deplacement;
};

typedef array<Transition, 3> Ligne;
typedef vector<Ligne> TableTransition;

struct TuringMachine {
    Etat etat;
    Tete tete;
    Bande bande;
    TableTransition transition;
};

enum Characteres {
    EPSILON = 'e',
    UN = '1',
    ZERO = '0'
};

enum Deplacement {
    DROITE = 1,
    GAUCHE = -1
};

constexpr Etat STOP(-1);
constexpr Transition DEFAUT({STOP, EPSILON, DROITE});

void expand(Bande& bande, Tete& tete) {
    int taille(bande.size());
    if (tete < 0) {
        string padding(abs(tete), EPSILON);
        bande = padding + bande;
        tete = 0;
    } else if (tete >= taille) {
        string padding(tete - taille + 1, EPSILON);
        bande = bande + padding;
    }
}

char lire(Bande& bande, Tete& tete) {
    expand(bande, tete);

    return bande[tete];
}

void ecrire(char c, Bande& bande, Tete& tete) {
    expand(bande, tete);

    bande[tete] = c;
}

void avance(Tete& tete) {
    tete++;
}

void recule(Tete& tete) {
    tete--;
}

void init(Bande& bande, const string& valeur) {
    bande = valeur + bande;
}

void reinitialise(TuringMachine& machine, const string& entree = "") {
    machine.etat = 1;
    machine.tete = 0;
    init(machine.bande, entree);
}

void cree(TuringMachine& machine, const TableTransition& transition) {
    machine.bande = "";
    reinitialise(machine);
    machine.transition = transition;
}

Transition const* transition_pour_caractere(const Ligne& ligne, char lu) {
    Transition const* transition(nullptr);
    switch (lu) {
        case ZERO:
            transition = &ligne[0];
            break;

        case UN:
            transition = &ligne[1];
            break;

        case EPSILON:
            transition = &ligne[2];
            break;

        default:
            transition = &DEFAUT;
            break;
    }
    return transition;
}

void update(TuringMachine& machine, Transition const* transition) {
    ecrire(transition->caractere, machine.bande, machine.tete);

    machine.etat = transition->etat;

    if (transition->deplacement == DROITE) {
        avance(machine.tete);
    } else {
        recule(machine.tete);
    }
}

void afficher_machine(const TuringMachine& machine) {
    cout << "Etat: " << machine.etat << endl
         << "Bande: " << endl
         << setw(5) << " " << machine.bande << endl
         << setw(5 + machine.tete) << " "
         << "^  (tête: " << machine.tete << ")" << endl;
}

void afficher_changement(char lu, Transition const* transition) {
    cout << "lu: `" << lu << "`"
         << ", ecrit: `" << transition->caractere << "`"
         << ", nouvel état: " << transition->etat
         << ", déplacement: " << transition->deplacement
         << endl;
}

void separateur() {
    cout << "------------------------------" << endl;
}

void run(TuringMachine& machine) {
    afficher_machine(machine);
    separateur();
    while (machine.etat != STOP) {
        char lu(lire(machine.bande, machine.tete));

        Ligne& ligne(machine.transition[machine.etat - 1]);
        Transition const* transition(transition_pour_caractere(ligne, lu));

        update(machine, transition);

        afficher_changement(lu, transition);
        separateur();
        afficher_machine(machine);
        separateur();
    }
}

int main() {
    TuringMachine machine;
    TableTransition transition = {
        {{{2, ZERO, DROITE}, {3, UN, DROITE}, {STOP, EPSILON, DROITE}}},
        {{{2, ZERO, DROITE}, {3, UN, DROITE}, {4, EPSILON, DROITE}}},
        {{{2, ZERO, DROITE}, {3, UN, DROITE}, {5, EPSILON, DROITE}}},
        {{{4, ZERO, DROITE}, {4, UN, DROITE}, {6, ZERO, GAUCHE}}},
        {{{5, ZERO, DROITE}, {5, UN, DROITE}, {6, UN, GAUCHE}}},
        {{{6, ZERO, GAUCHE}, {6, UN, GAUCHE}, {7, EPSILON, GAUCHE}}},
        {{{8, EPSILON, GAUCHE}, {8, EPSILON, GAUCHE}, {7, EPSILON, GAUCHE}}},
        {{{10, ZERO, DROITE}, {11, UN, DROITE}, {9, EPSILON, DROITE}}},
        {{{STOP, ZERO, GAUCHE}, {STOP, UN, GAUCHE}, {9, EPSILON, DROITE}}},
        {{{4, ZERO, DROITE}, {4, UN, DROITE}, {10, EPSILON, DROITE}}},
        {{{5, ZERO, DROITE}, {5, UN, DROITE}, {11, EPSILON, DROITE}}}
	};
    cree(machine, transition);
    reinitialise(machine, "e");

    run(machine);

    return 0;
}
