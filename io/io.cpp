#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void tree(size_t height, size_t segments) {
	segments--;
    size_t w(1);
	int max_w(height * 2 - 7 * segments);

	if (max_w <= 0) {
		return;
	}

	for (size_t i = 0; i < height; i++) {
		cout << setfill(' ') << setw(max_w / 2 - w / 2) << ' ' << setfill('*') << setw(w) << '*' << endl;
		w += 2;

		if (i > height / pow(2, segments)) {
			segments--;
			w -= 7;
		}
    }

	for (size_t i = 0; i < 5; i++)
	{
		cout << setfill(' ') << setw(3 * max_w / 8 + 4) << ' ' << setfill('#') << setw(max_w / 8) << '#' << endl;
	}
	
}

int main() {
	tree(32, 3);
    return 0;
}