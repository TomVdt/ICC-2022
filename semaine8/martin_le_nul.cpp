#include <iostream>
#include <string>

using namespace std;

bool palin_le_lapin(string chaine) {
	int n(chaine.size());

	if (n <= 1) 
		return true;
	else if (chaine.front() == chaine.back())
		return palin_le_lapin(chaine.substr(1,n-2));
	else return false;


}




int main() {
	cout << palin_le_lapin("");
    return 0;
}