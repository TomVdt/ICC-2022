#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void sapin_rec(ofstream& file, size_t segments, size_t height, size_t width) {
    if (segments > 1) {
        // file << setw();
        sapin_rec(file, segments - 1, height / 2, width / 2);
    	height = height / 2;
    }

    size_t w(height > width ? height - width : 1);
    for (size_t i(0); i < height; i++) {
        for (size_t j(0); j < w; j++) {
            file << "*";
        }
        w += 2;
        if (i < height - 1) {
            file << "\n";
        }
    }
}

bool sapin(ofstream& file, size_t segments = 2, size_t height = 32, size_t width = 16) {
    sapin_rec(file, segments, height, width);
    file << endl;
    return true;
}

int main() {
    string fname;
    cout << "Votre sapin, dans quel fichier mon cher? ";
    cin >> ws;
    getline(cin, fname);

	size_t s(0), h(0), l(0);
	cout << "segments, hauteur, largeur? ";
	cin >> s >> h >> l;

    ofstream file(fname);
    if (file.fail()) {
        cout << "Impossible de creer / ecrire dans le fichier" << endl;
        return 1;
    }

    sapin(file, s, h, l);

    file.close();

    return 0;
}
