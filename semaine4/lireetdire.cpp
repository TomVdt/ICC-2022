#include <iostream>
#include <string>
#include <cmath>
#include "infint.h"
using namespace std;

int separer_chiffre_gauche(int& nombre)
{
  int dix(1);
  int temp(nombre);
  while (temp >= 10) {
    dix  *= 10;
    temp /= 10;
  }
  nombre %= dix;
  return temp;
}

int separer_chiffre_gauche(InfInt& nombre)
{
  int n(nombre.numberOfDigits());
  string str_nb(nombre.toString());
  int left(stoi(str_nb.substr(0, 1)));
  if (n > 1) {
    nombre = str_nb.substr(1, n-1);
  } else {
    nombre = InfInt(0);
  }
  return left;
}

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

void ajouter_chiffre_droit(int& nombre, int chiffre)
{
  nombre = nombre * 10 + chiffre;
}

void ajouter_chiffre_droit(InfInt& nombre, int chiffre)
{
  nombre = nombre * 10 + chiffre;
}

void dire_chiffre(int& nombre, int repetitions_chiffre, int chiffre)
{
  ajouter_chiffre_droit(nombre, repetitions_chiffre);
  ajouter_chiffre_droit(nombre, chiffre);
}

void dire_chiffre(InfInt& nombre, int repetitions_chiffre, int chiffre)
{
  ajouter_chiffre_droit(nombre, repetitions_chiffre);
  ajouter_chiffre_droit(nombre, chiffre);
}

int lire_et_dire(int nombre)
{
  int new_nombre(0);
  int repetitions(1);
  int prev_gauche = separer_chiffre_gauche(nombre);
  do {
    int new_gauche = separer_chiffre_gauche(nombre);
    if (prev_gauche == new_gauche) {
      repetitions++;
    } else {
      dire_chiffre(new_nombre, repetitions, prev_gauche);
      repetitions = 1;
    }
    prev_gauche = new_gauche;
  } while (prev_gauche != 0);

  return new_nombre;
}

InfInt lire_et_dire(InfInt nombre)
{
  InfInt new_nombre(0);
  int repetitions(1);
  int prev_gauche = separer_chiffre_gauche(nombre);
  do {
    int new_gauche = separer_chiffre_gauche(nombre);
    if (prev_gauche == new_gauche) {
      repetitions++;
    } else {
      dire_chiffre(new_nombre, repetitions, prev_gauche);
      repetitions = 1;
    }
    prev_gauche = new_gauche;
  } while (prev_gauche != 0);

  return new_nombre;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void repeter_lire_et_dire(int& nombre, int fois)
{
  while (nombre > 0 && fois-- > 0) {
    cout << nombre << endl;
    nombre = lire_et_dire(nombre);
  }
}

void repeter_lire_et_dire(InfInt& nombre, int fois)
{
  while (fois-- > 0) {
    // cout << nombre << endl;
    nombre = lire_et_dire(nombre);
  }
}

int main(int argc, char** argv)
{
  int nombre(1);
  int fois(1);
  if (argc == 3) {
    nombre = atoi(argv[1]);
    fois = atoi(argv[2]);

  } else {
    cout << "Nombre de départ et nombre de répétitions: ";
    cin >> nombre >> fois;
  }

  InfInt magic(nombre);
  repeter_lire_et_dire(magic, fois);
  cout << magic << endl;
  return 0;
}
