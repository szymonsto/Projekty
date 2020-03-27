#include <iostream>
#include<string>
#include <fstream>
#include"bank.h"

using std::cout;
using std::cin;
using std::endl;



Admin::Admin(const string& ID, const string& password, const string& nazwisko) : Pracownik(ID, password, nazwisko) {
}

bool Admin::transfer_approval(powiadomienia notification) { 

	string decyzja{};

	cout << "Szczegoly operacji:" << endl
		<< notification.tresc << endl
		<< "Czy potwierdzasz transakcje? (y/n)" << endl;

	cin >> decyzja;

 

	if (decyzja == "y") return true;
	else return false;

}

void Admin::creating_account_approval(int nr_powiadomienia, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje) {

	string decyzja{}, ID_nowego_konta{};

	ID_nowego_konta = m_notifications[nr_powiadomienia].tresc.substr((m_notifications[nr_powiadomienia].tresc).find("I:", 0) + 3, 3); //(notification.tresc).find("I", 0) + 2 -> sluzy do wskazania poczatki ID w tresci powiadomienia

	int pozycja = string_na_int(m_notifications[nr_powiadomienia].tresc.substr(m_notifications[nr_powiadomienia].tresc.find("M:", 0) + 3, 1)); //pozycja obiektu w vectorze obiektow do stworzenia (m_klienci_nowi, ...)

	cout << "Szczegoly operacji:" << endl
		<< m_notifications[nr_powiadomienia].tresc << endl
		<< "Czy potwierdzasz stworzenie nowego konta o ID " << ID_nowego_konta << "? (y/n)" << endl;

	cin >> decyzja;

	if (decyzja == "y") { //tworzenie konta
		if (string_na_int(m_notifications[nr_powiadomienia].tresc.substr(m_notifications[nr_powiadomienia].tresc.find("R:", 0) + 3, 1)) == 1) {
			klienci.push_back(m_klienci_nowi[pozycja]);
			m_klienci_nowi.erase(m_klienci_nowi.begin() + pozycja);
		}
		if (string_na_int(m_notifications[nr_powiadomienia].tresc.substr(m_notifications[nr_powiadomienia].tresc.find("R:", 0) + 3, 1)) == 2) {
			firmy.push_back(m_firmy_nowe[pozycja]);
			m_firmy_nowe.erase(m_firmy_nowe.begin() + pozycja);
		}
		if (string_na_int(m_notifications[nr_powiadomienia].tresc.substr(m_notifications[nr_powiadomienia].tresc.find("R:", 0) + 3, 1)) == 5) {
			fundacje.push_back(m_fundacje_nowe[pozycja]);
			m_fundacje_nowe.erase(m_fundacje_nowe.begin() + pozycja);
		}
			   
		cout << endl << "Konto zostalo stworzone" << endl;
	}
	else {
		cout << endl << "Konto nie zostalo stworzone" << endl;
	}
	m_notifications.erase(m_notifications.begin() + nr_powiadomienia);

}


bool Admin::modifying_account_approval(powiadomienia notification) {

	string decyzja{};

	cout << "Szczegoly operacji:" << endl
		<< notification.tresc << endl
		<< "Czy potwierdzasz usuniecie konta? (y/n)" << endl;

	cin >> decyzja;

	if (decyzja == "y") return true;
	else return false;


}

bool Admin::give_back_control(powiadomienia notification) {

	string decyzja{};

	cout << "Szczegoly operacji:" << endl
		<< notification.tresc << endl
		<< "Czy odblokowanie usuniecie konta? (y/n)" << endl;

	cin >> decyzja;

	if (decyzja == "y") return true;
	else return false;



}



void Admin::show_notifications_adm(vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje) {

	system("CLS");
	int iter{};		//numer iteracji w petli for (potrzebne przy wypisywaniu)
	std::string tresc{};
	char opcja_pow{};

	cout << "Powiadomienia:"  << endl;

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

	if ((((int)opcja_pow) - ((int)'0')) != iter) {	//return ""; //jesli funkcja zwroci taka wartosc to oznacza, ze wybrano powrot

		tresc = m_notifications[(((int)opcja_pow) - ((int)'0')) - 1].tresc;

		switch (m_notifications[(((int)opcja_pow) - ((int)'0')) - 1].level)  //tu jest (i - 1) poniweaz numeracja w vectorze jest od 0, a wypisywane numery sa od 1
		{
		case 1:
			system("CLS");
			cout << "BANK JPO - zatwierdzanie transferu" << endl << endl;

			if (transfer_approval(m_notifications[(((int)opcja_pow) - ((int)'0')) - 1])) {

				wykonaj_przelew_admin(tresc.substr(tresc.find("N:", 0) + 3, 3), tresc.substr(tresc.find("A:", 0) + 3, 3), stold(tresc.substr(tresc.find("K:", 0) + 3, tresc.size() - tresc.find("K:", 0) - 2)));

				m_notifications.erase(m_notifications.begin() + (((int)opcja_pow) - ((int)'0')) - 1);			 //kasowanie powiadomienia
			}
			
			break;

		case 2:
			system("CLS");
			cout << "BANK JPO - tworzenie konta" << endl << endl;

			creating_account_approval((((int)opcja_pow) - ((int)'0')) - 1, klienci, firmy, fundacje);

			break;

		case 3:
			system("CLS");
			cout << "BANK JPO - odblokowanie konta" << endl << endl;

			if (give_back_control(m_notifications[(((int)opcja_pow) - ((int)'0')) - 1])) {

				m_notifications.erase(m_notifications.begin() + (((int)opcja_pow) - ((int)'0')) - 1);

				
			}

			break;

		case 4:
			system("CLS");
			cout << "BANK JPO - modyfikacja konta" << endl << endl;

			if (modifying_account_approval(m_notifications[(((int)opcja_pow) - ((int)'0')) - 1])) {

				m_notifications.erase(m_notifications.begin() + (((int)opcja_pow) - ((int)'0')) - 1);			
			}

			break;
		default:			
			break;
		}
	}

}

void wpisywanie_do_pliku_admin(vector<Admin>& spis) {

	fstream plik("obiekty_admini.txt");
	if (plik.is_open()) {
		for (unsigned int j = 0; j <= spis.size() - 1; j++) {
			plik << spis[j].get_ID() << "|" << spis[j].get_password() << "|" << spis[j].get_nazwisko() << "|end|\n";
		}
	}
	plik.close();
}

void wczytywanie_admin(vector<Admin>& spis, int iteracje) {

	vector <string> wektor;
	int pos = 0;
	string tmp;


	fstream plik("obiekty_admini.txt");
	getline(plik, tmp);						//ta i dwie kolejne linijki - anty-pusty plik zabezpieczenie: eof() zwraca? zero bo pusty plik traktuje jako plik bez pocz?tku i ko?ca z jakiego? powodu
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
			Admin obiekt(wektor[0], wektor[1], wektor[2]);
			spis.push_back(obiekt);
		}
	}
	plik.close();
}


int zliczanie_linii_admini(void) {
	int number_of_lines = 0;
	string line;
	fstream plik("obiekty_admini.txt");


	while (getline(plik, line)) ++number_of_lines;
	return number_of_lines;
}

