#include <iostream>
#include <chrono>

using namespace std;

int main() {
    const auto now = chrono::system_clock::now();
    time_t tt = chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    int annee = local_tm.tm_year + 1900;

    int age;
    cout << "Quel est votre age (entier)" << endl;
    cin >> age;

    int ne(annee - age);
    cout << "Tu es ne.e en " << ne << endl;
    return 0;
}
