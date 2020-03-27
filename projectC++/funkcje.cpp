#include <iostream>
#include<string>
#include<vector>
#include"bank.h"


//zwraca numer w wektorze obiektow kont z danym ID
int znajdz_po_ID(vector<Admin>& admini, std::string wpisane_ID) {

	for (unsigned int i = 0; i < admini.size(); i++) {

		if (wpisane_ID == admini[i].get_ID()) {
			return i;
		}
	}

	return admini.size(); //to oznacza, ze nie znalieziono takiego ID
}

int znajdz_po_ID(vector<Pracownik>& pracownicy, std::string wpisane_ID) {

	for (unsigned int i = 0; i < pracownicy.size(); i++) {

		if (wpisane_ID == pracownicy[i].get_ID()) {
			return i;
		}
	}

	return pracownicy.size(); //to oznacza, ze nie znalieziono takiego ID
}

int znajdz_po_ID(vector<Klient>& klienci, std::string wpisane_ID) {

	for (unsigned int i = 0; i < klienci.size(); i++) {

		if (wpisane_ID == klienci[i].get_ID()) {
			return i;
		}
	}

	return klienci.size(); //to oznacza, ze nie znalieziono takiego ID
}

int znajdz_po_ID(vector<Firma>& firmy, std::string wpisane_ID) {

	for (unsigned int i = 0; i < firmy.size(); i++) {

		if (wpisane_ID == firmy[i].get_ID()) {
			return i;
		}
	}

	return firmy.size(); //to oznacza, ze nie znalieziono takiego ID
}

int znajdz_po_ID(vector<Fundacja>& fundacje, std::string wpisane_ID) {

	for (unsigned int i = 0; i < fundacje.size(); i++) {

		if (wpisane_ID == fundacje[i].get_ID()) {
			return i;
		}
	}

	return fundacje.size(); //to oznacza, ze nie znalieziono takiego ID
}

std::string losowanie_ID(int liczba_znakow/*, vector<Klient> klienci*/) {

	std::string numset = "0123456789"; //z tego zbioru beda losowane znaki
	std::string rand_ID;

	for (int i = 0; i < liczba_znakow; i++) {

		rand_ID += numset[(rand() % 10)];

	}

	return rand_ID;
}

std::string int_na_string(int liczba) {

	std::string numset = "0123456789";
	std::string wynik{};

	if (liczba == 0) {
		wynik = "0";
		}

	while (liczba > 0) {

		wynik += numset[liczba % 10];
		liczba /= 10;
	}
	

	return wynik;
}

int string_na_int(std::string napis) {

	int wynik{}, pot{};

	for (int i = napis.size() - 1; i >= 0; i--) {

		wynik += (napis[i] - 48) * potega(10, pot);

		pot++;

	}
	return wynik;
}

int potega(int podstawa, int wykladnik) {

	int wynik = 1;

	for (int i = 1; i <= wykladnik; i++) {
		wynik *= podstawa;
	}
	return wynik;
}

bool czy_tylko_cyfry(std::string wyraz) {

	for (auto i : wyraz) {
		
		if (i < '0' || i > '9') {
			return false;
		}
	}
	return true;
}

bool czy_tylko_litery_i_cyfry(std::string wyraz) {

	for (auto i : wyraz) {

		if ((i < '0' || i > '9') && (i < 'a' || i > 'z') && (i < 'A' || i > 'Z')) {
			return false;
		}
	}
	return true;
}

std::string na_male(std::string wyraz) { //zamiana tekstu na male litery

	for (auto i : wyraz) {

		if (i >= 'A' && i <= 'Z') {
			i += 'a' - 'A';
		}
	}
	return wyraz;
}

std::string pierwsza_duza(std::string wyraz) { //pierwsza litera duza, reszta male

	wyraz = na_male(wyraz);
	wyraz[0] -= 'a' - 'A';

	return wyraz;
}