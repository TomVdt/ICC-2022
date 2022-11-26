#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct QCM {
    string question;
    vector<string> reponses;
    int solution;
};

typedef vector<QCM> Examen;

int demander_nombre(int min, int max) {
    int x(min - 1);
    do {
        cout << "Entrez un nombre entier compris entre " << min << " et " << max << ": ";
        cin >> x;
    } while (x > max or x < min);
    return x;
}

void affiche(QCM qcm) {
    cout << qcm.question << endl;
    for (int i(1); i <= qcm.reponses.size(); i++) {
        cout << "\t" << i << "- " << qcm.reponses[i - 1] << endl;
    }
}

int poser_question(QCM qcm) {
    affiche(qcm);
    return demander_nombre(1, qcm.reponses.size());
}

int main() {
    Examen exam = {
        // Question 1
        {
            "Combien de dents possède un éléphant adulte",
            {"32", "de 6 à 10", "beaucoup", "24", "2"},
            2  // réponse
        },
        // Question 2
        {
            "Laquelle des instructions suivantes est un prototype de fonction",
            {"int f(0);",
             "int f(int 0);",
             "int f(int i);",
             "int f(i);"},
            3  // réponse
        },
        // Question 3
        {
            "Qui pose des questions stupides",
            {"le prof. de math",
             "mon copain/ma copine",
             "le prof. de physique",
             "moi",
             "le prof. d'info",
             "personne, il n'y a pas de question stupide",
             "les sondages"},
            6  // réponse
        }
    };

	int score(0);

	for (auto question : exam) {
		int reponse(poser_question(question));
		score += reponse == question.solution;
	}
	cout << "Votre score est: " << score << "/" << exam.size() << endl;

	switch (score) {
		case 0:
			cout << "Tu est une sale merde sans culture bro." << endl;
			break;
		case 1:
			cout << "Tu peux faire mieux je crois." << endl;
			break;
		case 2:
			cout << "Si proche de la gloire et pourtant ta médiocrité se laisse voir." << endl;
			break;
		case 3:
			cout << "Sale intello va, à apprendre les réponses par coeur!" << endl;
			break;
		default:
			cout << "Tu a cassé le système. Tu as mon respect bro.";
			break;
	}

    return 0;
}