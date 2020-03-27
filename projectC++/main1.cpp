#include <iostream>
#include <vector>
#include <string>
#include "bank.h"
#include "communication.h"
#include "interfejsy_kont.h"
#include "external.h"
#include <ctime>
#include <cstdlib>
#include <fstream>

//dodac tworzenie konta do funkcji mainowych

using namespace std;

vector <Firma> firmy;
vector <Fundacja> fundacje;
vector <Klient> indywidualni;
vector <Pracownik> pracownicy;
vector <Admin> admini;



int main() {
	
	srand(static_cast<unsigned int>(time(nullptr))); //taki zapis eleimuje warning przy srand(time(NULL))
	wczytywanie_klient(indywidualni, zliczanie_linii_klienci());
	wczytywanie_firmy(firmy, zliczanie_linii_firmy());
	wczytywanie_fundacje(fundacje, zliczanie_linii_fundacje());
	wczytywanie_pracownik(pracownicy, zliczanie_linii_pracownicy());
	wczytywanie_admin(admini, zliczanie_linii_admini());

	ekran_startowy();
	
}

string znajdz_po_imieniu(int& numerek, string& imm, int& opcja) {


	if (opcja == 2) {
		for (pair<string, string> element : firmy[numerek].get_imie()) {
			string ksywa = element.first;
			string imie = element.second;

			if (imm == ksywa) {
				return imie;
			}
		}
	}
	else if (opcja == 5) {
		for (pair<string, string> element : fundacje[numerek].get_imie()) {
			string ksywa = element.first;
			string imie = element.second;

			if (imm == ksywa) {
				return imie;
			}
		}
	}
	cout << "Nie znaleziono takiej nazwy uzytkownika, sprobuj ponownie" << endl;				//sprawzic czy to konieczne
	return znajdz_po_imieniu(numerek, imm, opcja);

}

string znajdz_po_loginie(int& numerek, int& opcja) {

	cout << "Podaj swoja nazwe uzytkownika wspolniku: ";
	string imm;
	cin >> imm;

	if (opcja == 2) {
		for (pair<string, string> element : firmy[numerek].get_imie()) {
			string ksywa = element.first;
			string imie = element.second;

			if (imm == ksywa) {
				return ksywa;
			}
		}
	}
	else if (opcja == 5) {
		for (pair<string, string> element : fundacje[numerek].get_imie()) {
			string ksywa = element.first;
			string imie = element.second;

			if (imm == ksywa) {
				return ksywa;
			}
		}
	}
	cout << "Nie znaleziono takiej nazwy uzytkownika, sprobuj ponownie" << endl;
	return znajdz_po_loginie(numerek, opcja);

}

string interfejs_logowania(void) {


	cout << "BANK JPO - logowanie" << endl;
	cout << "Podaj ID: ";
	string ajdi;
	cin >> ajdi;

	return ajdi;
}

int znajdz_klienta(string& ID) {
	for (unsigned int i = 0; i < indywidualni.size(); i++) {
		if (indywidualni[i].get_ID() == ID) return i;
	}
	cout << "Nie znaleziono, sprobuj ponownie" << endl;
	cout << "Podaj ID jeszcze raz lub wpisz \"0\" aby powrocic" << endl;
	string tmp;
	cin >> tmp;

	if (tmp == "0") {
		return indywidualni.size();
	}

	return znajdz_klienta(tmp);
}

int znajdz_firme(string& ID) {
	for (unsigned int i = 0; i < firmy.size(); i++) {
		if (firmy[i].get_ID() == ID) return i;
	}
	cout << "Nie znaleziono, sprobuj ponownie" << endl;
	cout << "Podaj ID jeszcze raz lub wpisz \"0\" aby powrocic" << endl;
	string tmp;
	cin >> tmp;

	if (tmp == "0") {
		return firmy.size();
	}

	return znajdz_firme(tmp);
}

int znajdz_fundacje(string& ID) {
	for (unsigned int i = 0; i < fundacje.size(); i++) {
		
		if (fundacje[i].get_ID() == ID) return i;
	}
	cout << "Nie znaleziono, sprobuj ponownie" << endl;
	cout << "Podaj ID jeszcze raz lub wpisz \"0\" aby powrocic" << endl;
	string tmp;
	cin >> tmp;

	if (tmp == "0") {
		return fundacje.size();
	}
	return znajdz_fundacje(tmp);
}

void ekran_startowy(void) {
	system("CLS");
	int recon;
	cout << "Witaj wedrowcze, wybierz sposrod dostepnych opcji: " << endl;
	cout << "1. Zaloguj sie\n2. Zaloz konto\n3. Kalkulator kredytowy\n4. Kalkulator lokat \n5. Wyjdz" << endl;
	cout << "Podaj opcje: ";
	recon = check_int(1);

	switch (recon) {
	case 1:
		cout << "Wybierz rodzaj konta " << endl;
		cout << "1. Klient indywidualny \n2. Firmowe \n3. Pracownik \n4. Admin \n 5. Fundacja \n6. Cofnij" << endl;
		recon = check_int(1);
		switch (recon) {
		case 1:
			zaloguj_do_klienta();
			break;
		case 2:
			zaloguj_do_firmy(recon);
			break;
		case 3:
			zaloguj_do_pracownika();
			break;
		case 4:
			zaloguj_do_admina();
			break;
		case 5:
			zaloguj_do_fundacji(recon);
			break;
		case 6:
			ekran_startowy();
			break;
		}
		ekran_startowy();
		break;
	case 2:
		int wybor;
		system("CLS");
		cout << "Wybierz rodzaj konta, ktory chcesz utworzyc:\n1. Klient indywidualny\n2. Konto firmowe\n3. Konto Fundacji\n4. Powrot\nWybor: ";
		wybor = check_int(1);
		switch (wybor) {
		case 1:
			tworzenie_konta_klienta(indywidualni, pracownicy, admini);
			ekran_startowy();
			break;
		case 2:
			tworzenie_konta_firmowego(firmy, pracownicy, admini);
			ekran_startowy();
			break;
		case 3:
			tworzenie_konta_fundacji(fundacje, pracownicy, admini);
			ekran_startowy();
			break;
		case 4:
			ekran_startowy();
			break;
		}
		break;
	case 3:
		kalkulator_kredytowy();
		ekran_startowy();
		break;
	case 4:
		kalkulator_lokat();
		ekran_startowy();
		break;
	case 5:
		wpisywanie_do_pliku_klient(indywidualni);
		wpisywanie_do_pliku_firma(firmy);
		wpisywanie_do_pliku_fundacje(fundacje);
		wpisywanie_do_pliku_pracownik(pracownicy);
		wpisywanie_do_pliku_admin(admini);
		exit(0);
	}
}

void zaloguj_do_klienta(void) {
	string tymcz = interfejs_logowania();
	int numerek = znajdz_klienta(tymcz);
	int flaga = 3;
	if (numerek != indywidualni.size()) { //to znaczy, ze nie wybrano opcji powrot
		

		if (indywidualni[numerek].logowanie() == true) {
			interfejs(indywidualni[numerek], pracownicy, admini, indywidualni, firmy, fundacje);
		}
		else { //blokowanie konta po nieudanym logowaniu

			indywidualni[znajdz_po_ID(indywidualni, tymcz)].set_password(losowanie_ID(8)); //zmiana hasla klienta

			if (czy_zablokowane(admini, tymcz) == false) { //sprawdz czy konto jest juz zablokowane
				add_notification("Zablokowane konto I: " + tymcz + " P: " + indywidualni[znajdz_po_ID(indywidualni, tymcz)].get_password(), 3, pracownicy, admini); //wyslanie nowego hasla do admina

			}
			cout << endl << "Konto zostalo zablokowane, aby odblokowac skontaktuj sie z administratorem" << endl;
			system("pause");
			ekran_startowy();
		}
	}
}

void zaloguj_do_firmy(int& opcja) {
	string tymcz = interfejs_logowania();
	int numerek = znajdz_firme(tymcz);
	int flaga = 3;
	if (numerek != firmy.size()) { //to znaczy, ze nie wybrano opcji powrot
	

		if (firmy[numerek].logowanie() == true) {
			string tmp4 = znajdz_po_loginie(numerek, opcja);
			string tmp0 = znajdz_po_imieniu(numerek, tmp4, opcja);
			cout << "Witaj " << tmp0 << "! Podaj swoje haslo (haslo: " << firmy[numerek].get_passwords()[tmp4] << "): ";
			while (flaga != 0) {
				string tmp1;
				cin >> tmp1;
				if (tmp1 == firmy[numerek].get_passwords()[tmp4]) {
					cout << "Logowanie udane!" << endl;
					interfejs(firmy[numerek], tmp4, pracownicy, admini, indywidualni, firmy, fundacje); ////////////////////blad !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					flaga = 0;
				}
				else {
					flaga--;
					cout << "Haslo bledne. Ilosc pozostalych prob: " << flaga << endl;
				}

				if (flaga == 0 && tmp1 != firmy[numerek].get_passwords()[tmp4]) {
					

					//blokowanie konta po nieudanym logowaniu
					firmy[znajdz_po_ID(firmy, tymcz)].set_password(losowanie_ID(8)); //zmiana hasla klienta

					if (czy_zablokowane(admini, tymcz) == false) { //sprawdz czy konto jest juz zablokowane
						add_notification("Zablokowane konto I: " + tymcz + " P: " + firmy[znajdz_po_ID(firmy, tymcz)].get_password(), 3, pracownicy, admini); //wyslanie nowego hasla do admina
						
					}
					cout << endl << "Konto zostalo zablokowane, aby odblokowac skontaktuj sie z administratorem" << endl;
					system("pause");
					ekran_startowy();

				}
			}

		}
	}
}

void zaloguj_do_fundacji(int& opcja) {
	string zzz = interfejs_logowania();
	int numerek = znajdz_fundacje(zzz);
	int flaga = 3;
	if (numerek != fundacje.size()) { //to znaczy, ze nie wybrano opcji powrot
		

		if (fundacje[numerek].logowanie(fundacje[numerek]) == true) {
			string tmp = znajdz_po_loginie(numerek, opcja);
			string tmp0 = znajdz_po_imieniu(numerek, tmp, opcja);
			cout << "Witaj " << tmp0 << "! Podaj swoje haslo (haslo: " << fundacje[numerek].get_passwords()[tmp] << "): ";
			while (flaga != 0) {
				string tmp1;
				cin >> tmp1;
				if (tmp1 == fundacje[numerek].get_passwords()[tmp]) {
					cout << "Logowanie udane!" << endl;
					interfejs(fundacje[numerek], tmp, pracownicy, admini, indywidualni, firmy, fundacje);	
					flaga = 0;
				}
				else {
					flaga--;
					cout << "Haslo bledne. Ilosc pozostalych prob: " << flaga << endl;
				}

				if (flaga == 0 && tmp1 != fundacje[numerek].get_passwords()[tmp]) {
					cout << "Wykorzystano limit logowan, powrot do menu glownego" << endl;

					//blokowanie konta po nieudanym logowaniu

					indywidualni[znajdz_po_ID(fundacje, zzz)].set_password(losowanie_ID(8)); //zmiana hasla klienta

					if (czy_zablokowane(admini, zzz) == false) { //sprawdz czy konto jest juz zablokowane
						add_notification("Zablokowane konto I: " + zzz + " P: " + fundacje[znajdz_po_ID(fundacje, zzz)].get_password(), 3, pracownicy, admini); //wyslanie nowego hasla do admina
						cout << "wysylanie informacji do admina" << endl;
					}
					cout << endl << "Konto zostalo zablokowane, aby odblokowac skontaktuj sie z administratorem" << endl;
					system("pause");
					ekran_startowy();


				}
			}

		}
	}
}

int zliczanie_linii_klienci(void) {
	int number_of_lines = 0;
	string line;
	fstream plik("obiekty_klienci.txt");


	while (getline(plik, line)) ++number_of_lines;
	return number_of_lines;
}

int zliczanie_linii_firmy(void) {
	int number_of_lines = 0;
	string line;
	fstream plik("obiekty_firma.txt");


	while (getline(plik, line)) ++number_of_lines;
	return number_of_lines;
}

int zliczanie_linii_fundacje(void) {
	int number_of_lines = 0;
	string line;
	fstream plik("obiekty_fundacje.txt");


	while (getline(plik, line)) ++number_of_lines;
	return number_of_lines;
}



void zaloguj_do_admina() {

	string wpisane_ID, ID_usun;
	char opcja_submenu = '0';
	string kod_operacji, ID_adresata;


	cout << "BANK JPO - logowanie" << endl << endl;

	cout << "Podaj ID :" << endl;
	cin >> wpisane_ID;

	while (czy_tylko_cyfry(wpisane_ID) == false) {

		system("CLS");
		cout << "Niepoprawnie wprowadzone ID. ID moze zawierac tylko cyfry. Sprobuj jeszce raz" << endl
			<< "Podaj ID :" << endl;
		cin >> wpisane_ID;
	}

	while (czy_istnieje_ID(wpisane_ID, indywidualni, firmy, fundacje, pracownicy, admini) == false && wpisane_ID != "0") {

		system("CLS");
		cout << "Nie ma takiego ID sprobuj jescze raz lub wpisz \"0\" aby wrocic do main menu" << endl
			<< "Podaj ID :" << endl;
		cin >> wpisane_ID;
	}

	if (wpisane_ID != "0") { //powrot do main menu

		if (admini[znajdz_po_ID(admini, wpisane_ID)].logowanie()) {	//jezeli zalogowano sie pomyslnie		


			while (opcja_submenu != '4') {

				opcja_submenu = '0';

				system("CLS");
				cout << "Zalogowano jako " << admini[znajdz_po_ID(admini, wpisane_ID)].get_nazwisko() << endl << endl
					<< "1. Wyswietl powiadomienia" << endl
					<< "2. Wyslij wiadomosc" << endl
					<< "3. Usun konto"<<endl
					<< "4. Wyloguj" << endl
					<< "Wprowadz numer opcji :" << endl;

				cin >> opcja_submenu;

				while (opcja_submenu < '0' || opcja_submenu >'4') { //sprawdza czy opoprawnie wpisano opcje

					system("CLS");
					cout << "Zalogowano jako " << admini[znajdz_po_ID(admini, wpisane_ID)].get_nazwisko() << endl << endl
						<< "1. Wyswietl powiadomienia" << endl
						<< "2. Wyslij wiadomosc" << endl
						<< "3. Usun konto"<<endl
						<< "4. Wyloguj" << endl
						<< "Wprowadz numer opcji :" << endl
						<< "Mozesz wprowadzic tylko cyfre z zakresu <0, 4>!" << endl;	//dodatkowy komunikat po wpisaniu do opcji innego znaku niz cyfra

					cin >> opcja_submenu;
				}

				switch (((int)opcja_submenu) - ((int)'0'))
				{
				case 1:

					admini[znajdz_po_ID(admini, wpisane_ID)].show_notifications_adm(indywidualni, firmy, fundacje);

					system("pause");

					break;

				case 2:
					system("CLS");

					cout << "Wysylanie wiadomosci" << endl
						<< "Pwrowadz ID adresata" << endl;
					cin >> ID_adresata;

					wyslij_waidomosc(ID_adresata, pracownicy, admini, indywidualni, firmy, fundacje);

					system("pause");
					

					break;
				case 3:
					cout << "Wprowadz ID konta, ktore chcesz usunac:" << endl;
					cin >> ID_usun;

					if (znajdz_po_ID(indywidualni, ID_usun) != indywidualni.size()) { //gdy istnieje takie ID
						indywidualni.erase(indywidualni.begin() + znajdz_po_ID(indywidualni, ID_usun)); // usuwa konto
						cout << endl << "Usunieto konto" << endl;
					}
					else if (znajdz_po_ID(firmy, ID_usun) != firmy.size()) { //gdy istnieje takie ID
						firmy.erase(firmy.begin() + znajdz_po_ID(firmy, ID_usun)); // usuwa konto
						cout << endl << "Usunieto konto" << endl;
					}
					else if (znajdz_po_ID(fundacje, ID_usun) != fundacje.size()) { //gdy istnieje takie ID
						fundacje.erase(fundacje.begin() + znajdz_po_ID(fundacje, ID_usun)); // usuwa konto
						cout << endl << "Usunieto konto" << endl;
					}
					else {
						cout << endl << "NIe ma konta o takim ID" << endl;
					}
					system("pause");
					break;

				default:
					ekran_startowy();
					break;
				}


			}
		}
	}
}



void zaloguj_do_pracownika(void) {

	char opcja_submenu = '0';
	string kod_operacji;
	std::string ID_adresata{};
	string kwota{};
	string wpisane_ID;
	bool czy_poprawnie_wpisane = false; //czy poprawnie wpisano ID
	

	cout << "BANK JPO - logowanie" << endl << endl;

	cout << "Podaj ID :" << endl;
	cin >> wpisane_ID;

	while (czy_tylko_cyfry(wpisane_ID) == false) {

		system("CLS");
		cout << "Niepoprawnie wprowadzone ID. ID moze zawierac tylko cyfry. Sprobuj jeszce raz" << endl
			<< "Podaj ID :" << endl;
		cin >> wpisane_ID;
	}

	while (czy_istnieje_ID(wpisane_ID, indywidualni, firmy, fundacje, pracownicy, admini) == false && wpisane_ID != "0") {

		system("CLS");
		cout << "Nie ma takiego ID sprobuj jescze raz lub wpisz \"0\" aby wrocic do main menu" << endl
			<< "Podaj ID :" << endl;
		cin >> wpisane_ID;
	}

	if (wpisane_ID != "0") { //powrot do main menu



		if (pracownicy[znajdz_po_ID(pracownicy, wpisane_ID)].logowanie()) {	//jezeli zalogowano sie pomyslnie

			opcja_submenu = '0';

			while (opcja_submenu != '4') {

				opcja_submenu = '0';

				system("CLS");
				cout << "Zalogowano jako " << pracownicy[znajdz_po_ID(pracownicy, wpisane_ID)].get_nazwisko() << endl << endl
					<< "1. Wyswietl powiadomienia" << endl
					<< "2. Wyslij wiadomosc" << endl
					<< "3. Przyjmij wplate na konto" << endl
					<< "4. Wyloguj" << endl
					<< "Wprowadz numer opcji :" << endl;

				cin >> opcja_submenu;

				while (opcja_submenu < '0' || opcja_submenu >'4') { //sprawdza czy opoprawnie wpisano opcje

					system("CLS");
					cout << "Zalogowano jako " << pracownicy[znajdz_po_ID(pracownicy, wpisane_ID)].get_nazwisko() << endl << endl
						<< "1. Wyswietl powiadomienia" << endl
						<< "2. Wyslij wiadomosc" << endl
						<< "3. Przyjmij wplate na konto" << endl
						<< "4. Wyloguj" << endl
						<< "Wprowadz numer opcji :" << endl
						<< "Mozesz wprowadzic tylko cyfre z zakresu <0, 4>!" << endl;	//dodatkowy komunikat po wpisaniu do opcji innego znaku niz cyfra

					cin >> opcja_submenu;
				}

				switch (((int)opcja_submenu) - ((int)'0'))
				{
				case 1:

					pracownicy[znajdz_po_ID(pracownicy, wpisane_ID)].show_notifications_prac();

					system("pause");
					break;

				case 2:
					system("CLS");

					cout << "Wysylanie wiadomosci" << endl
						<< "Pwrowadz ID adresata" << endl;
					cin >> ID_adresata;

					wyslij_waidomosc(ID_adresata, pracownicy, admini, indywidualni, firmy, fundacje);

					system("pause");

					break;

				case 3:
					while (czy_poprawnie_wpisane == false) {
						system("CLS");
						cout << "Wplata na konto" << endl << endl
							<< "Podaj ID konta :" << endl;
						cin >> ID_adresata;

						if (znajdz_po_ID(indywidualni, ID_adresata) != indywidualni.size()) { //gdy znaleziono takie ID //zmiana salda odbiorcy
							czy_poprawnie_wpisane = true;
						}
						else if (znajdz_po_ID(firmy, ID_adresata) != firmy.size()) { //gdy znaleziono takie ID //zmiana salda odbiorcy
							czy_poprawnie_wpisane = true;
						}
						else if (znajdz_po_ID(fundacje, ID_adresata) != fundacje.size()) { //gdy znaleziono takie ID //zmiana salda odbiorcy
							czy_poprawnie_wpisane = true;
						}
						else {
							czy_poprawnie_wpisane = false;
							cout << "Nie ma takiego ID" << endl;
							system("pause");
						}
					}
					
					cout << endl << "Podaj wplacona kwote :" << endl;
					cin >> kwota;

					while (czy_tylko_cyfry(kwota) == false) {

						cout << endl << "Podaj wplacona kwote (moze zawierac tylko cyfry) :" << endl;
						cin >> kwota;



					}



					indywidualni[znajdz_po_ID(indywidualni, ID_adresata)].set_saldo(indywidualni[znajdz_po_ID(indywidualni, ID_adresata)].get_saldo() + stold(kwota));	//tu trzeba bedzie zamienic na operator "+" !!!!!!!!!!!!!!!!						   

					system("pause");

					break;

				default:
					ekran_startowy();
					break;
				}



			}
		}
	}
	
}

void wykonaj_przelew_admin(string adres_nadawcy, string adres_adresata, long double kwota) {

	przelew_realizacja(adres_nadawcy, adres_adresata, kwota, pracownicy, admini, indywidualni, firmy, fundacje);
}