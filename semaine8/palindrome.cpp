#include <iostream>
#include <string>

using namespace std;

bool palindrome(const string& str, int i, int j) {
    // La chaine est vide
	if (i > j) {
        return true;
    }

    if (str[i] == str[j]) {
        return palindrome(str, i + 1, j - 1);
    } else {
		return false;
	}
}

bool palindrome(string str) {
    // La chaine est vide
	size_t n(str.size());
	if (n == 0) {
        return true;
    }

    if (str[0] == str[n - 1]) {
        return palindrome(str.substr(1, n - 2));
    } else {
		return false;
	}
}

bool primer(const string& str) {
	return palindrome(str, 0, str.size() - 1);
}

int main() {
	cout << palindrome("elle") << endl;
    return 0;
}