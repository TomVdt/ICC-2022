#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <iomanip>

using namespace std;

template<typename T>
void clean_cin(T& valeur, const T& mini, const T& maxi) {
	T var(valeur);
	bool valide(true);
	do {
		cout << "Valeur stp: ";
		cin >> var;
		valide = true;
		if (cin.fail()) {
			cout << "AAAAAAAAAAAAAA" << endl;
			cin.clear();
			cin.ignore();
			valide = false;
		}
	} while ((var < mini || var > maxi) && !valide);
	valeur = var;
}

string* read_file(const string& fname) {
	string* out = new string();

	ifstream file(fname);
	if (file.fail()) {
		cout << "where file?" << endl;
		file.close();
		return nullptr;
	}

	// read ze vucking file
	string word;
	while (getline(file, word)) {
		out->append(word + "\n");
	}

	if (not file.eof()) {
		cout << "fucky wucky" << endl;
		file.close();
		return nullptr;
	}

	file.close();
	return out;
}

int main() {
	double test(0);
	clean_cin(test, -5.0, 69.0);
	cout << test << endl;

	string* filecontents(read_file("test.txt"));
	if (filecontents != nullptr) {
		cout << *filecontents << endl;
	}
	delete filecontents;

	return 0;
}
