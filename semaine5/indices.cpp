#include <iostream>
#include <vector>

using namespace std;

vector<int> elements_en_indice(vector<int> in) {
    vector<int> out(in.size() / 2);
    for (int i(0); i < in.size(); i += 2) {
		out[in[i + 1]] = in[i];
    }

	return out;
}

int main() {
    vector<int> A(6);
    A[0] = 4;
    A[1] = 2;
    A[2] = 8;
    A[3] = 0;
    A[4] = 7;
    A[5] = 1;
    vector<int> T = elements_en_indice(A);
    for (unsigned int i(0); i < T.size(); ++i) {
        cout << T[i] << " ";
    }
    cout << endl;
    return 0;
}