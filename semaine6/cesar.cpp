#include <string.h>

#include <iostream>

using namespace std;

char decale(char c, char debut, int decalage) {
    while (decalage < 0) {
        decalage += 26;
    }
    return debut + (((c - debut) + decalage) % 26);
}

char code(char c, int d) {
    if (c >= 'a' && c <= 'z') {
        return decale(c, 'a', d);
    }
    if (c >= 'A' && c <= 'Z') {
        return decale(c, 'A', d);
    }
    return c;
}

string code(string str, int d) {
    string out;
    for (auto c : str) {
        char chr(code(c, d));
        out.push_back(chr);
    }
    return out;
}

string decode(string str, int d) {
    return code(str, -d);
}

int main() {
    return 0;
}