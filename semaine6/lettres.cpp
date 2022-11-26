#include <iostream>
#include <string>

using namespace std;

enum Sexe {
	Male,
	Femelle
};

void genereLettre(Sexe sexe, string destinataire, string sujet, int jour, int mois, string politesse, string auteur) {
	cout << "Bonjour " << (sexe == Male ? "cher" : "chère") << " " << destinataire << "," << endl;
	cout << "Je vous écris à propos de " << sujet << endl;
	cout << "Il faudrait que nous nous voyons le " << jour << "/" << mois << " pour en discuter." << endl;
	cout << "Donnez-moi vite de vos nouvelles !" << endl;
	cout << politesse << " " << auteur << "." << endl;
}

int main() {
	genereLettre(Femelle, "Mireille", "votre cours.", 18, 12, "Amicallement,", "John");
	genereLettre(Male, "John", "votre demande de rendez-vous.", 16, 12, "Sincèrement,", "Mireille");

	return 0;
}