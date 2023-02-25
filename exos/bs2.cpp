#include <vector>
#include <cmath>

typedef vector<vector<double>> Matrice;

Matrice align(Matrice C) {
	if (C.empty()) {
		throw "ptdr t con";
	}

	int n = c.size();
	int m = c[0].size();

	for (const auto& ligne : C) {
		if (ligne.size() != m) {
			throw "t'es encore plus con";
		}
	}

	Matrice M(n+1, vector<double>(m+1, 0.0));

	for (int i(0); i <= n; i++) {
		M[i][0] = 0.0;
	}
	for (int j(0); j <= m; j++) {
		M[0][j] = 0.0;
	}

	for (int i(1); i <= n; i++) {
		for (int j(1); j <= m; j++) {
			M[i][j] = C[i-1][j-1] + max(M(i, j-1), M(i-1, j), M(i-1, j-1));
		}
	} 

}

int main() {

	return 0;
}
