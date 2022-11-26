#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Player {
    string name;
    int score;
    int fails;
};

const string STAGES[13] = {
	"1      \n   \n   \n   \n______",
	"2      \n  |\n  |\n  |\n__|___",
	"3      \n  |\n  |\n  |\n_/|___",
	"4 _____\n  |\n  |\n  |\n_/|\\__",
	"5 _____\n  |\n  |\n  |\n_/|\\__",
	"6 _____\n  |\n  |\n  |\n_/|\\__",
	"7 _____\n  |\n  |\n  |\n_/|\\__",
	"8 _____\n  |\n  |\n  |\n_/|\\__",
	"9 _____\n  |\n  |\n  |\n_/|\\__",
	"10_____\n  |\n  |\n  |\n_/|\\__",
	"11_____\n  |\n  |\n  |\n_/|\\__",
	"12_____\n  |\n  |\n  |\n_/|\\__",
	"13_____\n  |\n  |\n  |\n_/|\\___"
};

void ask_player_name(Player& p, int i) {
    cout << "Player " << i << " name: ";
    cin >> p.name;
}

string ask_word() {
    string word;
    cout << "Enter a word: ";
    cin >> word;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    return word;
}

char ask_letter(const Player& p, int i) {
    char c;
    do {
        cout << "Player " << p.name << " (" << i << ") proposes a letter: ";
        cin >> c;
    } while ( !(('a' <= c && c >= 'z') || ('A' <= c && c >= 'Z')) );

	if ( 'A' <= c && c <= 'Z') {
		c = c - 'A' + 'a';
	}

	return c;
}

vector<Player> prepare_game() {
    vector<Player> players;

    int i(0);
    do {
        cout << "Number of players: ";
        cin >> i;
    } while (i < 2);

    for (int j(0); j < i; j++) {
        Player p = {"", 0, 0};
        ask_player_name(p, j + 1);
        players.push_back(p);
    }

    return players;
}

vector<int> find_all(const string& str, char c) {
	vector<int> indices;
	for (int i(0); i < str.size(); i++) {
		if (str[i] == c) {
			indices.push_back(i);
		}
	}
	return indices;
}

bool all(const vector<bool>& v) {
	bool b(true);
	for (auto i : v) {
		b = b & i;
	}
	return b;
}

void show_word_progress(const string& str, const vector<bool>& known) {
    for (int i(0); i < str.size(); i++) {
		cout << (known[i] ? str[i] : '.');
	}
	cout << endl;
}

int main() {
    vector<Player> players(prepare_game());

    string word_to_guess("");
    vector<bool> uncovered;

    for (int i(0); i < players.size(); i++) {
        Player& p(players[i]);
        cout << "Player " << p.name << " (" << i + 1 << ") 's turn to ask a word." << endl;

        word_to_guess = ask_word();
        uncovered.clear();
        for (int i(0); i < word_to_guess.size(); i++) {
            uncovered.push_back(false);
        }

		bool is_done(false);
		int j(0);
        while ( !is_done ) {
            if (j != i) {
                // guessing time!
				cout << "Word: ";
                show_word_progress(word_to_guess, uncovered);

                char letter(ask_letter(players[j], j + 1));

				vector<int> matches(find_all(word_to_guess, letter));

				for (auto index : matches) {
					uncovered[index] = true;
				}

				if (matches.empty()) {
					players[j].fails++;
					cout << "Wrong! " << endl;
					cout << STAGES[players[j].fails - 1] << endl;
				} else {
					players[j].score++;
					cout << "Nice! " << endl;
				}

				if (players[j].fails >= 13) {
					is_done = true;
					cout << players[j].name << " lost!" << endl;
				} else if (all(uncovered)) {
					is_done = true;
					cout << players[j].name << " guessed the right word!" << endl;
				}
            }

			j = (j + 1) % players.size();
        }

		cout << "The rigth word was " << word_to_guess << "!" << endl;
    }

	cout << endl << "The game is over." << endl << "Results:" << endl;
	for (auto p : players) {
		cout << "Player " << p.name;
		if (p.fails < 13) {
			cout << " is still alive with " << p.score << " points!";
		} else {
			cout << " has been hung!";
		}
		cout << endl;
	}
}
