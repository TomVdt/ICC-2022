#include <iostream>
#include <vector>

using namespace std;

typedef size_t Position;
typedef vector<int> Sequence;

struct SousSequence {
	Position debut;
	Position fin;
	int somme;
};

SousSequence tranche_max_1(Sequence const& seq) {
	SousSequence sseq = {0, 0, 0};
	int somme(0);
	for (size_t i(0); i < seq.size(); i++) {
		for (size_t j(i); j < seq.size(); j++) {
			somme += seq[j];
			if (somme > sseq.somme) {
				sseq = {i, j, somme};
			}
		}
		somme = 0;
	}
	return sseq;
}

SousSequence tranche_max_2(Sequence const& seq) {
	SousSequence sseq = {0, 0, 0};
	int somme(0);
	size_t debut(0);
	for (size_t fin(0); fin < seq.size(); fin++) {
		somme += seq[fin];
		if (somme > sseq.somme) {
			sseq = {debut, fin, somme};
		}
		if (somme <= 0) {
			debut = fin + 1;
			somme = 0;
		}
	}
	return sseq;
}

int main() {
	Sequence seq = {11, 13, -4, 3, -26, 7, -13, 25, -2, 17, 5, -8, 1};

	SousSequence sseq = tranche_max_1(seq);
	cout << sseq.debut << " " << sseq.fin << " " << sseq.somme << endl;
	SousSequence sseq2 = tranche_max_2(seq);
	cout << sseq2.debut << " " << sseq2.fin << " " << sseq2.somme << endl;

	return 0;
}