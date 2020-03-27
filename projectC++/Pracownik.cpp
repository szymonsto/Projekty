#include <iostream>
#include <string>
#include <fstream>
#include"bank.h"

using std::cout;
using std::cin;
using std::endl;

void Pracownik::set_nazwisko(const string& nazwisko) { m_nazwisko = nazwisko; }
void Pracownik::set_notifications(powiadomienia notification) { m_notifications.push_back(notification); }

Pracownik::Pracownik(const string& ID, const string& password, const string& nazwisko) : Konto(ID, password), m_nazwisko{ nazwisko }{
}



void Pracownik::show_notifications_prac(void) {

	system("CLS");
	int iter{};		//numer iteracji w petli for (potrzebne przy wypisywaniu)
	char opcja_pow{};

	cout << "Powiadomienia:" << endl;

	for (auto i : m_notifications) {
		iter++;
		cout << iter << ". " << i.tresc << endl;
	}
	iter++;
	cout << iter << ". " << "Powrot" << endl;

	cout << "Wprowadz numer opcji :" << endl;
	cin >> opcja_pow;

	while (opcja_pow < '0' || opcja_pow > iter + '0') { //sprawdza czy opoprawnie wpisano opcje

		iter = 0;
		system("CLS");

		cout << "Powiadomienia:" << endl;

		for (auto i : m_notifications) {
			iter++;
			cout << iter << ". " << i.tresc << endl;
		}
		iter++;
		cout << iter << ". " << "Powrot" << endl
			<< "Wprowadz numer opcji :" << endl
			<< "Mozesz wprowadzic tylko cyfre z zakresu <0, " << iter << ">!" << endl;	//dodatkowy komunikat po wpisaniu do opcji innego znaku niz cyfra

		cin >> opcja_pow;
	}
	
}

void wpisywanie_do_pliku_pracownik(vector<Pracownik>& spis) {

	fstream plik("obiekty_pracownicy.txt");
	if (plik.is_open()) {
		for (unsigned int j = 0; j <= spis.size() - 1; j++) {
			plik << spis[j].get_ID() << "|" << spis[j].get_password() << "|" << spis[j].get_nazwisko() << "|end|\n";
		}
	}
	plik.close();
}

void wczytywanie_pracownik(vector<Pracownik>& spis, int iteracje) {

	vector <string> wektor;
	int pos = 0;
	string tmp;

	fstream plik("obiekty_pracownicy.txt");
	getline(plik, tmp);						//ta i dwie kolejne linijki - anty-pusty plik zabezpieczenie: eof() zwraca zero bo pusty plik traktuje jako plik bez pocz?tku i ko?ca
	plik.seekg(0);
	if (tmp.size() != 0) {
		for (int i = 0; i <= iteracje - 1; i++) {
			wektor.clear();
			pos = 0;
			if (plik.is_open()) {
				getline(plik, tmp);
				string tmp0;
				for (unsigned int j = 0; j < tmp.size(); j++) {
					tmp0.clear();
					if (tmp[pos] == 'e' and tmp[pos + 1] == 'n' and tmp[pos + 2] == 'd' and tmp[pos + 3] == '|') break;
					while (pos != tmp.size()) {
						tmp0 = tmp0 + tmp[pos];
						pos++;
						if (tmp[pos] == '|') {
							pos++;
							break;
						}
					}
					wektor.push_back(tmp0);
				}
			}
			Pracownik obiekt(wektor[0], wektor[1], wektor[2]);
			spis.push_back(obiekt);
		}
	}
	plik.close();
}

int zliczanie_linii_pracownicy(void) {
	int number_of_lines = 0;
	string line;
	fstream plik("obiekty_pracownicy.txt");


	while (getline(plik, line)) ++number_of_lines;
	return number_of_lines;
}