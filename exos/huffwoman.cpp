#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

struct Code {
    string_view key;
    double probability;
    string_view code;
};

struct Entity {
	vector<int> indicies;

};

typedef vector<Code> Codes;

bool contains(const Codes& codes, string_view str) {
    for (const auto& e : codes) {
        if (e.key == str) {
            return true;
        }
    }
    return false;
}

int count(string_view text, string_view key) {
    int count(0);
    for (int i(0); i < text.size() - key.size() + 1; i++) {
        bool found(true);

        for (int j(0); j < key.size(); j++) {
            found &= text[i + j] == key[j];
        }

        if (found) {
            count++;
            i += key.size() - 1;
        }
    }

    return count;
}

string add_prefix(string str, string prefix) {
	return prefix + str;
}

Codes initialize(string_view text) {
    Codes out;
    const double length(text.size());

    for (int i(0); i < length; i++) {
        string_view key(text.substr(i, 1));

        if (!contains(out, key)) {
            Code new_code;
            new_code.key = key;
            new_code.probability = count(text, key) / length;
            new_code.code = "";
            out.push_back(new_code);
        }
    }

    return out;
}

Codes huffwomanize(Codes& codes) {
	return codes;
}

void print_code(const Code& code) {
    cout << "`" << code.key << "`: probability "
         << code.probability << ", code: "
		 << code.code << endl;
}

void print_codes(const Codes& codes) {
    for (const auto& c : codes) {
        print_code(c);
    }
}

int main() {
    // cout << count("ABBABABAAAB", "AB") << endl;

    print_codes(initialize("LMAOOOOOOO"));

	// lmao as if i ever finished a project lol

    return 0;
}