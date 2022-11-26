#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Equipe {
    string pays;
    int points;
    int buts_marques;
    int buts_encaisses;
    int skill_diff;
};

struct Match {
    Equipe& equipe1;
    Equipe& equipe2;
};

void calculer_match(Equipe& equipe1, Equipe& equipe2) {
    cout << "Match " << equipe1.pays << " - " << equipe2.pays << ": ";
    cin >> equipe1.buts_marques >> equipe2.buts_marques;

    equipe1.buts_encaisses += equipe2.buts_marques;
    equipe2.buts_encaisses += equipe1.buts_marques;

    if (equipe1.buts_marques == equipe2.buts_marques) {
        equipe1.points += 1;
        equipe2.points += 1;
    } else if (equipe1.buts_marques > equipe2.buts_marques) {
        equipe1.points += 3;
    } else {
        equipe2.points += 3;
    }
}

bool meilleure(const Equipe& equipe1, const Equipe& equipe2) {
    return equipe1.points > equipe2.points;
}

void swap(Equipe& equipe1, Equipe& equipe2) {
    Equipe tmp(equipe1);
    equipe1 = equipe2;
    equipe2 = tmp;
}

void calculer_resultat(array<Equipe, 4>& equipes) {
    for (auto& equipe : equipes) {
        equipe.skill_diff = equipe.buts_marques - equipe.buts_encaisses;
    }
}

void calculer_classement(array<Equipe, 4>& equipes) {
    for (int i(0); i < 3; i++) {
        for (int j(3); j > i; j--) {
            if (meilleure(equipes[j], equipes[j-1])) {
                swap(equipes[j], equipes[j-1]);
            }
        }
    }
}

void afficher_resultat(const array<Equipe, 4>& equipes) {
	cout << "Resultats:" << endl;
    for (auto equipe : equipes) {
        cout << equipe.pays << " : "
             << equipe.points << " points, "
             << equipe.buts_marques << " buts marqués, "
             << equipe.buts_encaisses << " buts encaissés, différence: "
             << equipe.skill_diff << endl;
    }
}

void afficher_classement(const array<Equipe, 4>& equipes) {
    int i(1);
    cout << "Le classement final est :" << endl;
    for (auto e : equipes) {
        cout << i << " : " << e.pays << endl;
        i++;
    }
}

int main() {
    Equipe Suisse = {"Suisse", 0, 0, 0};
    Equipe Croatie = {"Croatie", 0, 0, 0};
    Equipe Angleterre = {"Angleterre", 0, 0, 0};
    Equipe France{"France", 0, 0, 0};

    array<Equipe, 4> equipes = {Suisse, Croatie, Angleterre, France};

	calculer_match(equipes[0], equipes[1]);
    calculer_match(equipes[3], equipes[2]);
    calculer_match(equipes[0], equipes[2]);
    calculer_match(equipes[3], equipes[1]);
    calculer_match(equipes[2], equipes[1]);
    calculer_match(equipes[0], equipes[3]);

    calculer_resultat(equipes);
    afficher_resultat(equipes);

    calculer_classement(equipes);
    afficher_classement(equipes);

    return 0;
}