#include <iostream>
#include "bank.h"
#include <string>
#include "interfejsy_kont.h"
#include "communication.h"
#include <fstream>

using namespace std;



Firma::Firma(const string& ID, const string& password, const string& nazwa, long double saldo, map<string, string> passwords, map<string, string> imie, long double prog_admin, long double prog_wspolnik, map<string, bool> zgody, long double propozycja, int opcja) : Konto(ID, password), m_nazwa{ nazwa }, m_saldo{ saldo }, m_passwords{ passwords }, m_imie{ imie }, m_prog_admin{ prog_admin }, m_prog_wspolnik{ prog_wspolnik }, m_zgody{ zgody }, m_propozycja{ propozycja }, m_opcja{ opcja } {}



//gettery i settery
string Firma::get_nazwa(void) const { return m_nazwa; }
long double Firma::get_saldo(void) { return m_saldo; }
long double Firma::get_prog_admin(void) { return m_prog_admin; }
long double Firma::get_prog_wspolnik(void) { return m_prog_wspolnik; }
map <string, string> Firma::get_passwords(void) { return m_passwords; }
map <string, string> Firma::get_imie(void) { return m_imie; }
map <string, bool> Firma::get_zgody(void) { return m_zgody; }
long double Firma::get_propozycja(void) { return m_propozycja; }
int Firma::get_opcja(void) { return m_opcja; }

void Firma::set_imie(map<string, string> &imie) {
	string ksywa, wabisie;
	int flaga = 1;
	while (ksywa != "end") {
		cout << "Wspolnik nr: " << flaga << endl;
		cout << "Podaj nazwe u¿ytkownika: ";
		cin >> ksywa;
		if (imie.count(ksywa) == 0 && ksywa != "end") {
			cout << "Swietnie, taka jeszcze nie jest zajeta! \n Teraz podaj imie: ";
			cin >> wabisie;
			imie[ksywa] = wabisie;
		}
		else if (imie.count(ksywa) > 0 && ksywa != "end") {
			cout << "Niestety, ta nazwa jest juz zajeta, prosze wprowadzic inna: " << endl;
		}
		flaga++;
	}
	m_imie = imie;
}
void Firma::set_passwords(map<string, string> &passwords) { 
	string tmp;
	for (pair<string, string> element : get_imie()) {
		string nazwa = element.first;
		cout << "Dla wspolnika o nazwie uzytkownika: " << nazwa << " prosze wprowadzic haslo: ";
		cin >> tmp;
		passwords[nazwa] = tmp;
	}

	m_passwords = passwords; 
}
void Firma::set_nazwa(string &nazwa) { m_nazwa = nazwa; }
void Firma::set_saldo(long double &saldo) { m_saldo = saldo; }
void Firma::set_prog_admin(long double &prog_admin) { m_prog_admin = prog_admin; }
void Firma::set_prog_wspolnik(long double &prog_wspolnik) { m_prog_wspolnik = prog_wspolnik; }
void Firma::set_zgody(map<string, bool> &zgody) {m_zgody = zgody;}
void Firma::set_propozycja(long double &propozycja) { m_propozycja = propozycja; }
void Firma::set_opcja(int& opcja) { m_opcja = opcja; }
void Firma::ustawianie_progu(Firma &obiekt, string ksywa) {
	int opcja = 99;
	while (opcja != 3) {
		system("CLS");
		cout << "Witaj w panelu ustawiania limitow. Wybierz, ktory prog chcesz ustawic: " << endl;
		cout << "1. Prog wspolniczy" << endl;
		cout << "2. Prog adminowy" << endl;
		cout << "3. Wyjscie" << endl;
		cout << "Pamietaj, ze poddana glosowaniu moze byc tylko jedna propozycje na raz!" << endl;
		cout << "Wybor: ";
		cin >> opcja;
		if (opcja == 1) {
			if (obiekt.get_zgody().size() == 0) {
				send_proposition(obiekt, ksywa, opcja);
			}
			else cout << "Niestety, jest juz jedno odbywajace sie glosowanie" << endl;
			system("pause");
		}
		else if (opcja == 2) {
			if (obiekt.get_zgody().size() == 0) {
				send_proposition(obiekt, ksywa, opcja);
			}
			else cout << "Niestety, jest juz jedno odbywajace sie glosowanie" << endl;
			system("pause");
		}
		else if (opcja == 3) break;
		else cout << "Wybrano nieprawidlowy numer" << endl;
	}
}

bool Firma::logowanie(void) {
	int proba = 3;
	while (proba > 0) {
		string pass;
		cout << "Podaj has³o: ";
		cin >> pass;
		if (pass == get_password()) return true;
		else {
			proba--;
			cout << "Logowanie nieudane." << endl;
		}
	}
	cout << "Przekroczono dozwolon¹ iloœæ b³êdnych logowañ, konto zosta³o zablokowane. Aby je odblokowac nale¿y skontaktowaæ siê z Administratorem." << endl;
	return false;
}

void Firma::modifying_account(string ksywa) {
	int flaga = 99;
	while (flaga != 0) {
		system("CLS");
		if (flaga == 4) break;
		cout << "Witaj w panelu zmian danych. Oto mozliwe opcje: " << endl;
		cout << "1. Zmien imie" << endl;
		cout << "2. Zmien login" << endl;
		cout << "3. Zmien haslo" << endl;
		cout << "4. Powrot" << endl;
		cout << "Wybierz opcje: ";
		flaga = check_int(1);
		string tmp;
		switch (flaga) {
		case 1:
			cout << "Podaj nowe imie: ";
			cin >> tmp;
			m_imie[ksywa] = tmp;
			break;
		case 2:
			cout << "Podaj nowy login: ";
			cin >> tmp;
			for (pair<string, string> element : m_imie) {
				if (element.first == ksywa) {
					element.first = tmp;
					cout << "Nowy login to: " << element.first << endl;
				}
			}
			break;
		case 3:
			cout << "Podaj nowe haslo: ";
			cin >> tmp;
			m_passwords[ksywa] = tmp;
			break;
		}
		if (flaga == 4) break;
		if (flaga <= -1 or flaga >= 5) cout << "Wybrano nieprawidlowy numer, wprowadz jeszcze raz";
	}
}

void wpisywanie_do_pliku_firma(vector<Firma>& spis) {
	vector<string> ksywki;
	
	map<string, bool> pusta;
	
	fstream plik("obiekty_firma.txt");
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
			if(spis[j].get_message().size()==0) plik << "brak wiadomosci" << "|end|";
			else plik << spis[j].get_message() << "|end|";
			plik << "\n";
		}

	}
		plik.close();
}


void tworzenie_konta_firmowego(vector<Firma> &istniejace, vector<Pracownik>& pracownicy, vector<Admin>& admini) {
	
	int ajdi = rand() % 100  + 200;
	string ajdi1 = to_string(ajdi);

	for (unsigned int i = 0; i < istniejace.size(); i++) {
		if (istniejace[i].get_ID() == ajdi1) return tworzenie_konta_firmowego(istniejace, pracownicy, admini);
	}

	map<string, string> pusty;
	pusty.clear();
	map<string, string> pusta;
	pusta.clear();
	map<string, bool> puste_zgody;
	puste_zgody.clear();
	Firma obiekt("", "", "", 0, pusty, pusta, 0, 0, puste_zgody,0,0);
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
	system("CLS");
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



void wczytywanie_firmy(vector<Firma> & firmy, int iteracje) {
	map<string, string> map_imie;
	map<string, string> map_pass;
	map<string, bool> map_zgody;
	vector <string> wektor;
	int pos = 0;
	string tmp;

	fstream plik("obiekty_firma.txt");
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

			Firma obiekt(wektor[0], wektor[1], wektor[2], stold(wektor[3]), map_pass, map_imie, stold(wektor[6]), stold(wektor[7]), map_zgody, stold(wektor[9]), stoi(wektor[10]));
			obiekt.set_message(wektor[11]);
			firmy.push_back(obiekt);
		}
	}
	plik.close();
}


