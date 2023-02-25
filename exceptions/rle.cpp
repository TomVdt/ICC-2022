#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

int min(int a, int b) {
    return a < b ? a : b;
}

char to_char(int i) {
    // auto conversion go brr
    return (char)i;
}

int to_int(char c) {
    // auto conversion go brr
    return (int)(c & 255);
}

string generate_compressed(char c, int length, char flag) {
    if (c == flag) {
        string out("");
        for (int i = 0; i < length; i++) {
            out += flag;
            out += '\0';
        }
        return out;
    }

    if (length <= 0) {
        return "";
    }

    if (length < 3) {
        return string(length, c);
    }

    string out("");
    int sequence_length(min(255, length));
    out += c;
    out += flag;
    out += to_char(sequence_length);

    return out + generate_compressed(c, length - 255, flag);
}

string compress(string_view data, char flag = '#') {
    if (data.size() == 0) {
        return "";
    }

    string out("");
    int counter(1);
    char prev(data[0]);

    for (int i = 1; i < data.size(); i++) {
        if (data[i] == prev) {
            counter++;
        } else {
            out += generate_compressed(prev, counter, flag);
            counter = 1;
            prev = data[i];
        }
    }
    // Ne pas oublier la fin!
    out += generate_compressed(data[data.size() - 1], counter, flag);
    return out;
}

// returns the number of chars processed and modifies the output
int process_code(string_view code, string& out, char flag) {
    // can't have special char followed by non-zero char
    if (code[0] == flag && to_int(code[1]) != 0) {
        string error("");
        error = error + "Decomperror: flag `" + flag + "`";
        error = error + " character followed by incorrect character `" + code[1] + "`";
        throw error;
    }

    // special case flag 0
    if (code[0] == flag && to_int(code[1]) == to_int(flag)) {
        out += flag;
        return 2;
    }

    // now we can confirm there is something special
    // we will check for the case where the flag is in the middle
    // char flag length
    // if length is 0, there is a special char waiting, so simply process a char
    if (code[1] == flag && to_int(code[2]) != 0) {
        int nein = to_int(code[2]);
        out += string(to_int(code[2]), code[0]);
        return 3;
    }

    // nothing special, just return the first thing
    out += code[0];
    return 1;
}

string decompress(string_view rledata, char flag = '#') {
    string out("");

    if (rledata.size() == 0) {
        return out;
    }

    int i(0);
    while (i < rledata.size()) {
        // process in blocks of 3 chars (size of code block)
        string_view code(rledata.substr(i, 3));

        try {
            i += process_code(code, out, flag);
        } catch (const string& str) {
            cerr << "Encountered error while decompressing!" << endl
                 << str << endl
                 << "Decoded: " << out << endl
                 << "To decode: " << rledata.substr(i)
                 << endl;
            throw;
            // i++;
        }
    }

    return out;
}

void show_bytes(string_view str) {
    for (const auto& s : str) {
        cout << hex << (int)((char)s & 255) << " ";
    }
    cout << endl;
}

int main() {
    string original("aaaaaaabbbbbccccdedddeee");
    string compressed = compress(original, '\xff');
    string decompressed;
    try {
        decompressed = decompress("\xff\xff", '\xff');
    } catch (const string& str) {
        cerr << "Aborting." << endl;
        return 1;
    }
    cout << original << endl;
    show_bytes(compressed);
    cout << decompressed << endl;
    cout << "RATIO: " << (double)compressed.size() / (double)original.size() << endl;
    cout << "pogging? " << boolalpha << (original == decompressed) << endl;
    return 0;
}