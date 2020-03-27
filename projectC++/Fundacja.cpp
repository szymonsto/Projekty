#include <iostream>
#include <string> 
#include "bank.h"
#include "interfejsy_kont.h"
#include "communication.h"
#include <fstream>

using namespace std;

Fundacja::Fundacja(const string& ID, const string& password, const string& nazwa, long double saldo, map<string, string> passwords, map<string, string> imie, long double prog_admin, long double prog_wspolnik, map<string, bool> zgody, long double propozycja, int opcja) : Firma(ID, password, nazwa, saldo, passwords, imie, prog_admin, prog_wspolnik, zgody, propozycja, opcja) {}


void tworzenie_konta_fundacji(vector<Fundacja>& istniejace, vector<Pracownik>& pracownicy, vector<Admin>& admini) {

	int ajdi = rand() % 100 + 500;
	string ajdi1 = to_string(ajdi);

	for (unsigned int i = 0; i < istniejace.size(); i++) {
		if (istniejace[i].get_ID() == ajdi1) return tworzenie_konta_fundacji(istniejace, pracownicy, admini);
	}

	map<string, string> pusty;
	pusty.clear();
	map<string, string> pusta;
	pusta.clear();
	map<string, bool> puste_zgody;
	puste_zgody.clear();
	Fundacja obiekt("", "", "", 0, pusty, pusta, 0, 0, puste_zgody,0,0);
	obiekt.set_ID(ajdi1);
	system("CLS");
	cout << "Witaj w naszym banku, cieszymy sie ¿e wybrales konto wlasnie u nas! \n Prosze, wypelnij ponizszy formularz aby utworzyc konto: " << endl;
	cout << "Podaj nazwe firmy: ";
	string nazwa;
	cin >> nazwa;
	obiekt.set_nazwa(nazwa);
	cout << "Teraz wprowadz haslo: ";
	string pass;
	cin >> pass;
	obiekt.set_password(pass);
	system("CLS");
	cout << "Teraz podaj nazwy wspolnikow zrzeszonych w firmie postepujac zgodnie z informacjami wyswietlanymi na ekranie. Aby zakonczyc wpisywanie nalezy w miejscu 'podaj nazwe' wpisac komende 'end'" << endl;
	obiekt.set_imie(pusta);
	cout << "Pora utworzyc hasla dla poszczegolnych wspolnikow" << endl;
	cout << "Prosze postepowac zgodnie z ponizszymi instrukcjami" << endl;
	obiekt.set_passwords(pusty);
	system("CLS");


	cout << "Stworzono konto o numerze ID: " << obiekt.get_ID() << "\n o nazwie: " << obiekt.get_nazwa() << "\n o hasle: " << obiekt.get_password() << endl;
	cout << "Ponadto, imiona wspolnikow to: " << endl;
	for (pair<string, string> element : obiekt.get_imie()) {
		string ksywa = element.first;
		string wabisie = element.second;
		cout << wabisie << " o nazwie uzytkownika: " << ksywa << endl;
	}

	system("pause");
	system("CLS");

	add_notification(obiekt, admini); 

}

bool Fundacja::logowanie(Fundacja& obiekt) {
	int proba = 3;
	while (proba > 0) {
		string pass;
		cout << "Jesli jestes osoba z zewnatrz i chcesz skorzystac z publicznej informacji o finansach Fundacji wpisz 'saldo'.\nJesli jestes pracownikiem podaj swoje haslo." << endl;
		cout << "Podaj has³o: ";
		cin >> pass;
		if (pass == get_password()) return true;
		else if (pass == "saldo") {
			system("CLS");
			cout << "Stan konta wynosi: " << obiekt.get_saldo() << " PLN" << endl;
			cout << "Wcisnij dowolny klawisz aby powrocic do menu glownego" << endl;
			system("pause");
			exit(0);
		}
		else {
			proba--;
			cout << "Logowanie nieudane." << endl;
		}
	}
	cout << "Przekroczono dozwolon¹ iloœæ b³êdnych logowañ, konto zosta³o zablokowane. Aby je odblokowac nale¿y skontaktowaæ siê z Administratorem." << endl;
	return false;
}

void wpisywanie_do_pliku_fundacje(vector<Fundacja>& spis) {
	vector<string> ksywki;

	map<string, bool> pusta;

	fstream plik ("obiekty_fundacje.txt");
	if (plik.is_open()) {
		for (unsigned int j = 0; j < spis.size(); j++) {
			ksywki.clear();
			for (pair<string, string> element : spis[j].get_imie()) {
				string jeden = element.first;
				string dwa = element.second;
				ksywki.push_back(jeden);
			}

			plik << spis[j].get_ID() << "|" << spis[j].get_password() << "|" << spis[j].get_nazwa() << "|" << spis[j].get_saldo() << "|";
			for (unsigned int i1 = 0; i1 < spis[j].get_passwords().size(); i1++) {
				plik << ksywki[i1] << "$" << spis[j].get_passwords()[ksywki[i1]] << "%";
				if (i1 == spis[j].get_passwords().size() - 1) plik << "###|";
			}
			for (unsigned int i2 = 0; i2 < spis[j].get_imie().size(); i2++) {
				plik << ksywki[i2] << "$" << spis[j].get_imie()[ksywki[i2]] << "%";
				if (i2 == spis[j].get_imie().size() - 1) plik << "###|";
			}
			plik << spis[j].get_prog_admin() << "|" << spis[j].get_prog_wspolnik() << "|";
			if (spis[j].get_opcja() != 1 && spis[j].get_opcja() != 2) plik << "pusta_mapa_zgod|";
			else {
				for (unsigned int i3 = 0; i3 < spis[j].get_zgody().size(); i3++) {
					plik << ksywki[i3] << "$" << spis[j].get_zgody()[ksywki[i3]] << "%";
					if (i3 == spis[j].get_zgody().size() - 1) plik << "###|";
				}
			}
			plik << spis[j].get_propozycja() << "|" << spis[j].get_opcja() << "|";
			if (spis[j].get_message().size() == 0) plik << "brak wiadomosci" << "|end|";
			else plik << spis[j].get_message() << "|end|";
			plik << "\n";
		}

	}
	plik.close();
}

void wczytywanie_fundacje(vector<Fundacja>& fundacje, int iteracje) {
	map<string, string> map_imie;
	map<string, string> map_pass;
	map<string, bool> map_zgody;
	vector <string> wektor;
	int pos = 0;
	string tmp;

	fstream plik("obiekty_fundacje.txt");
	getline(plik, tmp);						//ta i dwie kolejne linijki - anty-pusty plik zabezpieczenie: eof() zwraca³ zero bo pusty plik traktuje jako plik bez pocz¹tku i koñca z jakiegoœ powodu
	plik.seekg(0);
	if (tmp.size() != 0) {
		for (int i = 0; i <= iteracje - 1; i++) {
			wektor.clear();
			map_imie.clear();
			map_pass.clear();
			map_zgody.clear();
			pos = 0;
			if (plik.is_open()) {

				getline(plik, tmp);
				string tmp0;
				for (unsigned int j = 0; j < tmp.size(); j++) {
					tmp0.clear();
					if (tmp[pos] == 'e' and tmp[pos + 1] == 'n' and tmp[pos + 2] == 'd' and tmp[pos + 3] == '|') {
						break;
					}
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

			string map1, map2;
			map1 = wektor[4];
			map2 = wektor[5];
			vector <string> v_imie, v_haslo, v_zgody;
			v_imie.clear();
			v_haslo.clear();
			v_zgody.clear();

			pos = 0;
			string tmp0;
			for (unsigned int j = 0; j < map1.size(); j++) {
				tmp0.clear();
				if (map1[pos] == '#' and map1[pos + 1] == '#' and map1[pos + 2] == '#') break;
				while (pos != map1.size()) {
					tmp0 = tmp0 + map1[pos];
					pos++;
					if (map1[pos] == '%' or map1[pos] == '$') {
						pos++;
						break;
					}
				}
				v_imie.push_back(tmp0);
			}

			pos = 0;
			tmp0.clear();
			for (unsigned int j = 0; j < map2.size(); j++) {
				tmp0.clear();
				if (map2[pos] == '#' and map2[pos + 1] == '#' and map2[pos + 2] == '#') break;
				while (pos != map2.size()) {
					tmp0 = tmp0 + map2[pos];
					pos++;
					if (map2[pos] == '%' or map2[pos] == '$') {
						pos++;
						break;
					}
				}
				v_haslo.push_back(tmp0);
			}

			for (unsigned int i = 0; i < v_haslo.size(); i = i + 2) {
				string ksywa = v_imie[i];
				string imie = v_imie[i + 1];
				map_pass[ksywa] = imie;
			}

			for (unsigned int i = 0; i < v_imie.size(); i = i + 2) {
				string ksywa = v_haslo[i];
				string imie = v_haslo[i + 1];
				map_imie[ksywa] = imie;
			}

			if (wektor[8] == "pusta_mapa_zgod") map_zgody.clear();
			else if (wektor[8] != "pusta_mapa_zgod") {
				pos = 0;
				tmp0.clear();
				for (unsigned int j = 0; j < wektor[8].size(); j++) {
					tmp0.clear();
					if (wektor[8][pos] == '#' and wektor[8][pos + 1] == '#' and wektor[8][pos + 2] == '#') break;
					while (pos != wektor[8].size()) {
						tmp0 = tmp0 + wektor[8][pos];
						pos++;
						if (wektor[8][pos] == '%' or wektor[8][pos] == '$') {
							pos++;
							break;
						}
					}
					v_zgody.push_back(tmp0);
				}
			}

			for (unsigned int i = 0; i < v_zgody.size(); i = i + 2) {
				string ksywa = v_zgody[i];
				string tru = v_zgody[int(i + 1)];
				bool zgoda = (tru == "1");
				map_zgody[ksywa] = zgoda;
			}

			Fundacja obiekt(wektor[0], wektor[1], wektor[2], stold(wektor[3]), map_pass, map_imie, stold(wektor[6]), stold(wektor[7]), map_zgody, stold(wektor[9]), stoi(wektor[10]));
			obiekt.set_message(wektor[11]);
			fundacje.push_back(obiekt);
		}
	}
	plik.close();
}