#include <iostream>
#include "bank.h"
#include "interfejsy_kont.h"
#include <string>
#include <fstream>

using namespace std; 


Klient::Klient(const string& ID, const string& password, const string& imie, const string& nazwisko, long double saldo, long double prog, string message) :Konto(ID, password), m_imie{ imie }, m_nazwisko{ nazwisko }, m_saldo{ saldo }, m_prog{ prog }, m_message{ message }
{}


void Klient::setting_treshold(void) {
	long double kwota;
	cout << "Panel ustawiania limitu kwoty, do której transakcje nie s¹ autoryzowane przez pracowników banku." << endl;
	cout << "Podaj kwotê: ";
	cin >> kwota;
	m_prog = kwota;
}


void Klient::modifying_account(void) {
	int flaga=99;
	while (flaga != 0) {
		system("CLS");
		if (flaga == 5) break;
		cout << "Witaj w panelu zmian danych. Oto mozliwe opcje: " << endl;
		cout << "1. Zmien imie" << endl;
		cout << "2. Zmien nazwisko" << endl;
		cout << "3. Zmien limit przelewow" << endl;
		cout << "4. Zmien haslo" << endl;
		cout << "5. Powrot" << endl;
		cout << "Wybierz opcje: ";
		flaga = check_int(1);
		string tmp;
		switch (flaga) {
		case 0:	break;
		case 1:
			cout << "Podaj nowe imie: ";
			cin >> tmp;
			m_imie = tmp;
			break;
		case 2:
			cout << "Podaj nowe nazwisko: ";
			cin >> tmp;
			m_nazwisko = tmp;
			break;
		case 3:
			setting_treshold();
			break;
		case 4:
			cout << "Wprowadz nowe has³o: ";
			cin >> tmp;
			Konto::set_password(tmp);
			break;
		}
		if (flaga == 5) break;
		if (flaga <= -1 or flaga >= 6) cout << "Wybrano nieprawidlowy numer, wprowadz jeszcze raz";
	}
}

bool Klient::logowanie(void) {
	int proba = 3;
	while (proba > 0) {
		string pass;
		cout << "Podaj haslo: ";
		cin >> pass;
		if (pass == get_password()) return true;
		else {
			proba--;
			cout << "Logowanie nieudane." << endl;
		}
	}	
	return false;
}

void Klient::show_message(void) {
	if (m_message.size() == 0) {
		cout << "Nie masz nowych wiadomosci" << endl;
		m_message = "brak wiadomosci";
	}
	else {
		cout << "Ostatnia wiadomosc: " << endl;
		cout << m_message << endl;
	}
}

void Klient::set_imie(string imie) { m_imie = imie; }
void Klient::set_nazwisko(string nazwisko) { m_nazwisko = nazwisko; }
void Klient::set_saldo(long double saldo) { m_saldo = saldo; }
void Klient::set_prog(long double prog) { m_prog = prog; }
void Klient::set_message(string message) { m_message = message; }

void wczytywanie_klient(vector<Klient>& spis, int iteracje) {

	vector <string> wektor;
	int pos = 0;
	string tmp;

	fstream plik("obiekty_klienci.txt");
	getline(plik, tmp);						//ta i dwie kolejne linijki - anty-pusty plik zabezpieczenie: eof() zwraca³ zero bo pusty plik traktuje jako plik bez pocz¹tku i koñca z jakiegoœ powodu
	plik.seekg(0);
	if (tmp.size() != 0) {
		for (int i = 0; i <= iteracje-1; i++) {
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
			Klient obiekt(wektor[0], wektor[1], wektor[2], wektor[3], stold(wektor[4]), stold(wektor[5]), wektor[6]);
			spis.push_back(obiekt);
		}
	}
	plik.close();
}

void wpisywanie_do_pliku_klient(vector<Klient>& spis) {

	fstream plik("obiekty_klienci.txt");
	if (plik.is_open()) {
		for (unsigned int j = 0; j <= spis.size()-1; j++) {
			plik << spis[j].get_ID() << "|" << spis[j].get_password() << "|" << spis[j].get_imie() << "|" << spis[j].get_nazwisko() << "|";
			plik << spis[j].get_saldo() << "|" << spis[j].get_prog() << "|" << spis[j].get_message() << "|end|\n";
		}
	}
	plik.close();
}


void tworzenie_konta_klienta(vector<Klient>& istniejace, vector<Pracownik>& pracownicy, vector<Admin>& admini) {

	int ajdi = rand() % 100 + 100;
	string ajdi1 = to_string(ajdi);

	for (unsigned int i = 0; i < istniejace.size(); i++) {
		if (istniejace[i].get_ID() == ajdi1) return tworzenie_konta_klienta(istniejace, pracownicy, admini);
	}

	Klient obiekt("", "", "", "", 0, 0, "");
	obiekt.set_ID(ajdi1);
	system("CLS");
	cout << "Witaj w naszym banku, cieszymy sie ¿e wybrales konto wlasnie u nas! \n Prosze, wypelnij ponizszy formularz aby utworzyc konto: " << endl;
	cout << "Podaj swoje imie: ";
	string nazwa;
	cin >> nazwa;
	obiekt.set_imie(nazwa);
	system("CLS");
	cout << "Podaj nazwisko: ";
	nazwa.clear();
	cin >> nazwa;
	obiekt.set_nazwisko(nazwa);
	system("CLS");
	cout << "Teraz wprowadz haslo: ";
	string pass;
	cin >> pass;
	obiekt.set_password(pass);
	system("CLS");
	obiekt.set_message("brak wiadomosci");


	cout << "Stworzono konto o numerze ID: " << obiekt.get_ID() << "\nimie wlasciciela: " << obiekt.get_imie() << "\nnazwisko wlasciciela: " << obiekt.get_nazwisko() << "\n o hasle: " << obiekt.get_password() << endl;
	system("pause");
	system("CLS");

	add_notification(obiekt, admini);

}