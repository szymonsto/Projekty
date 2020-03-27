#include "interfejsy_kont.h"
#include "communication.h"
#include "bank.h"

using namespace std;



long double check_double(string j) {				//sprawdza, czy podana liczba moze byc stold'owana, jesli tak, to jest to robione
	
	int flaga = 0;
	for (unsigned int i = 0; i <= j.size() - 1; i++) {
		if (isdigit(j[i]) == false and j[i] != '.') {
			cout << "Podano niepoprawne wartosci" << endl;
			return 0;
		}
		else flaga++;
		if (flaga == j.size()) return stold(j);
	}
	return 0;
}


									// przel = przelacznik sprawdzajacy czy funkcja ma zwracac int dla switch-case czy dowolnego
int check_int(int przel) {			//funkcja proszaca o wpisanie liczby i sprawdza jej poprawnosc (nie tylko czy int sie pokrywa, ale czy to wgl jest int)
	int opcja = 99;		
	while (opcja <= -1 or opcja >= 9) {
		string opcja1;
		cin >> opcja1;
		if (opcja1.size() > 1 and przel == 1) cout << "Wpisane znaki nie sa poprawne, prosze wprowadzic jeszcze raz: ";
		else if (opcja1.size() > 1 and przel == 0) {
			for (unsigned int i=0; i < opcja1.size(); i++) {
				if (isdigit(opcja1[i]) == false) {
					cout << "Wpisana wartosc nie jest liczbowa" << endl;
					check_int(przel);
				}
				int opcja = stoi(opcja1);
				return opcja;
			}
		}
		else if (opcja1.size() == 1) {
			if (isdigit(opcja1[0]) == false) {
				cout << "Nie wpisano cyfry, prosze wprowadzic jeszcze raz: ";
			}
			else {
				int opcja = stoi(opcja1);
				if (przel == 1) {
					if (opcja <= -1 or opcja >= 9) {
						cout << "Wprowadzono niewlasciwa cyfre, prosze sprobowac jeszcze raz: ";
					}
					else return opcja;
				}
				else return opcja;
			}
		}
	}
	return 0;
}


void interfejs(Firma &obiekt, string ksywa, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje) {

	system("CLS");
	
	string msg, tmp, tmp1, tmp2;
	long double kwota;


	checking_votes(obiekt, tmp, tmp2);

	cout << "Witaj ponownie, " << obiekt.get_imie()[ksywa] << "!" << endl;
	cout << "Znajdujesz sie obecnie w dostepnym tylko dla Ciebie panelu zarz¹dzania kontem Firmy" << endl;
	cout << "Aby wybrac opcje prosze wpisac odpowiednia cyfre." << endl;
	cout << "1. Sprawdz saldo" << endl;
	cout << "2. Wyslij wiadomosc" << endl;
	cout << "3. Ustawianie progow" << endl;
	cout << "4. Dokonaj przelewu" << endl;
	cout << "5. Rzeczy wymagajace Twojej uwagi" << endl;
	cout << "6. Zmien dane lub usun konto" << endl;
	cout << "7. Wyswietl wiadomosc" << endl;
	cout << "8. Wyloguj sie" << endl;
	cout << "Wybor: ";

	
	int opcja = check_int(1);				//funkcja proszaca o wpisanie liczby i sprawdza jej poprawnosc (nie tylko czy int sie pokrywa, ale czy to wgl jest int)

	switch (opcja) {
	case 0: 
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
	case 1:
		system("CLS");
		cout << "Stan konta wynosi: " << obiekt.get_saldo() << " PLN" << endl;
		cout << "Wcisnij dowolny klawisz aby powrocic do menu glownego" << endl;
		system("pause");
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 2:
		cout << "jestes w wysylaniu wiadomosci 2" << endl;

		wyslij_waidomosc(obiekt, pracownicy, admini);

		system("pause");
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 3:
		system("CLS");
		obiekt.ustawianie_progu(obiekt, ksywa);
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 4:
		cout << "Podaj ID konta na ktore chcesz przelac pieniadze: ";
		cin >> tmp;
		while (czy_tylko_cyfry(tmp) == false) {

			system("CLS");
			cout << "Niepoprawnie wprowadzone ID. ID moze zawierac tylko cyfry. Sprobuj jeszce raz:" << endl;

			cin >> tmp;
		}
		cout << "Podaj imie i nazwisko osoby, do ktorej wysylasz pieniadze: ";
		cin >> tmp1;
		kwota = 0;
		while (kwota == 0) {
			cout << "Podaj kwote, ktora chcesz wyslac: ";
			cin >> tmp2;
			kwota = check_double(tmp2);
			if (kwota == 0) cout << "Wprowadzono niewlasciwe znaki" << endl;

			while (kwota > obiekt.get_saldo()) {

				cout << "Nie masz takich srodkow na koncie" << endl;
				cout << "Podaj kwote, ktora chcesz wyslac: ";
				cin >> tmp2;
				kwota = check_double(tmp2);
				if (kwota == 0) cout << "Wprowadzono niewlasciwe znaki" << endl;
			}
		}

		

		//funkcja na przelewy
		if (kwota >= obiekt.get_prog_wspolnik()) {
			if (obiekt.get_zgody().size() == 0) transfer_request(obiekt, ksywa, kwota, tmp);
			else {
				cout << "Niestety, podana kwota nie miesci sie w ustalonym limicie, a jednoczesnie odbywa sie juz glosowanie. \nNastapi powrot do menu glownego." << endl;
				system("pause");
				interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
			}
		}
		else if (kwota >= obiekt.get_prog_admin()) { 			//koniecznie chce podawac wartosci kwota0fir i ajidi0fir aby moc je wyczyscic pod nastepne glosowania!
			add_notification(("Przelew N: " + obiekt.get_ID() + " A: " + tmp + " K: " + tmp2), 1, pracownicy, admini);
			cout << "Przelew zostanie wyslany po zatwierdzeniu przez admina" << endl;
		}
		else{                         //jesli poprzednie ify niespelnione to zwykly transfer
		
			przelew_realizacja(obiekt, tmp, kwota, pracownicy, admini, klienci, firmy, fundacje);

					
		}
																								

		system("pause");
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 5:
		if (obiekt.get_zgody().size() >= 1 && obiekt.get_zgody().count(ksywa) == 0 && obiekt.get_opcja() == 1) {			// Jeœli mapa zgód nie jest pusta AND zalogowany wspólnik nie odda³ g³osu TO mu sie tu cos pojawi
			cout << "Oczekuje na Ciebie glosowanie w sprawie zmiany limitu wspolniczego" << endl;
			cout << "Dla przypomnienia: limit wspolniczy to kwota, od której przelew musi byc autoryzowany przez pozostalych wspolnikow." << endl;
			cout << "Za zmiana limitu opowiedzieli sie juz: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == true) cout << im_name << endl;
			}
			cout << "Przeciwko zdazyli opowiedziec sie: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == false) cout << im_name << endl;
			}
			make_decision(obiekt, ksywa);
		}
		else if (obiekt.get_zgody().size() >= 1 && obiekt.get_zgody().count(ksywa) == 0 && obiekt.get_opcja() == 2) {			// Jeœli mapa zgód nie jest pusta AND zalogowany wspólnik nie odda³ g³osu TO mu sie tu cos pojawi
			cout << "Oczekuje na Ciebie glosowanie w sprawie zmiany limitu adminowego" << endl;
			cout << "Dla przypomnienia: limit adminowy to kwota, od której przelew musi byc autoryzowany przez Administratora, tzn musi sie on skontaktowac z Firma w celu jego autoryzacji." << endl;
			cout << "Za zmiana limitu opowiedzieli sie juz: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == true) cout << im_name << endl;
			}
			cout << "Przeciwko zdazyli opowiedziec sie: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == false) cout << im_name << endl;
			}
			make_decision(obiekt, ksywa);
		}
		else if (obiekt.get_zgody().size() >= 1 && obiekt.get_zgody().count(ksywa) == 0 && obiekt.get_opcja() == 3) {			// Jeœli mapa zgód nie jest pusta AND zalogowany wspólnik nie odda³ g³osu TO mu sie tu cos pojawi
			cout << "Oczekuje na Ciebie glosowanie w sprawie wykonania przelewu o kwocie przekraczajacej limit" << endl;
			cout << "Za wyslaniem opowiedzieli sie juz: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == true) cout << im_name << endl;
			}
			cout << "Przeciwko zdazyli opowiedziec sie: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == false) cout << im_name << endl;
			}
			transfer_vote(obiekt, ksywa, tmp);
			interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		}
		else {
			cout << "Nie ma zadnych nowych akcji" << endl;
			system("pause");
			interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		}
		break;
	case 6:
		obiekt.modifying_account(ksywa);
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 7:
		cout << "Wiadomosc: " << endl
			<< obiekt.get_message() << endl;

		system("pause");
		ekran_startowy();
		break;
	case 8:
		cout << "Trwa wylogowanie" << endl;
		system("pause");
		ekran_startowy();
		break;
	}


}


void interfejs(Fundacja& obiekt, string ksywa, vector<Pracownik> &pracownicy, vector<Admin> &admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje) {

	system("CLS");
	int opcja = 99;
	string msg,tmp, tmp1, tmp2;
	long double kwota;

	checking_votes(obiekt, tmp, tmp2);

	cout << "Witaj ponownie, " << obiekt.get_imie()[ksywa] << "!" << endl;
	cout << "Znajdujesz sie obecnie w dostepnym tylko dla Ciebie panelu zarz¹dzania kontem Fundacji" << endl;
	cout << "Aby wybrac opcje prosze wpisac odpowiednia cyfre." << endl;
	cout << "1. Sprawdz saldo" << endl;
	cout << "2. Wyslij wiadomosc" << endl;
	cout << "3. Ustawianie progow" << endl;
	cout << "4. Dokonaj przelewu" << endl;
	cout << "5. Rzeczy wymagajace Twojej uwagi" << endl;	
	cout << "6. Zmien dane." << endl;
	cout << "7. Wyswietl wiadomosc" << endl;
	cout << "8. Wyloguj sie" << endl;
	cout << "Wybor: ";

	opcja = check_int(1);				//funkcja proszaca o wpisanie liczby i sprawdza jej poprawnosc (nie tylko czy int sie pokrywa, ale czy to wgl jest int)

	switch (opcja) {
	case 1:
		system("CLS");
		cout << "Stan konta wynosi: " << obiekt.get_saldo() << " PLN" << endl;
		cout << "Wcisnij dowolny klawisz aby powrocic do menu glownego" << endl;
		system("pause");
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 2:
	
		wyslij_waidomosc(obiekt, pracownicy, admini);

		system("pause");
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 3:
		system("CLS");
		obiekt.ustawianie_progu(obiekt, ksywa);
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 4:
		cout << "Podaj ID konta na ktore chcesz przelac pieniadze: ";
		cin >> tmp;
		while (czy_tylko_cyfry(tmp) == false) {

			system("CLS");
			cout << "Niepoprawnie wprowadzone ID. ID moze zawierac tylko cyfry. Sprobuj jeszce raz:" << endl;

			cin >> tmp;
		}
		cout << "Podaj imie i nazwisko osoby, do ktorej wysylasz pieniadze: ";
		cin >> tmp1;
		cout << "Podaj kwote, ktora chcesz przelac: ";
		cin >> tmp2;
		kwota = 0;
		while (kwota == 0) {
			cout << "Podaj kwote, ktora chcesz wyslac: ";
			cin >> tmp2;
			kwota = check_double(tmp2);
			if (kwota == 0) cout << "Wprowadzono niewlasciwe znaki" << endl;
			while (kwota > obiekt.get_saldo()) {

				cout << "Nie masz takich srodkow na koncie" << endl;
				cout << "Podaj kwote, ktora chcesz wyslac: ";
				cin >> tmp2;
				kwota = check_double(tmp2);
				if (kwota == 0) cout << "Wprowadzono niewlasciwe znaki" << endl;
			}
		}
		
		 //funkcja na przelewy
		if (kwota >= obiekt.get_prog_wspolnik()) {
			if (obiekt.get_zgody().size() == 0) transfer_request(obiekt, ksywa, kwota, tmp);
			else {
				cout << "Niestety, podana kwota nie miesci sie w ustalonym limicie, a jednoczesnie odbywa sie juz glosowanie. \nNastapi powrot do menu glownego." << endl;
				system("pause");
				interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
			}
		}
		else if (kwota >= obiekt.get_prog_admin()) { 			//koniecznie chce podawac wartosci kwota0fir i ajidi0fir aby moc je wyczyscic pod nastepne glosowania!
			add_notification(("Przelew N: " + obiekt.get_ID() + " A: " + tmp + " K: " + tmp2), 1, pracownicy, admini);
			cout << "Przelew zostanie wyslany po zatwierdzeniu przez admina" << endl;
		}
		else {                         //jesli poprzednie ify niespelnione to zwykly transfer

			przelew_realizacja(obiekt, tmp, kwota, pracownicy, admini, klienci, firmy, fundacje);


		}

		system("pause");
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 5:
		if (obiekt.get_zgody().size() >= 1 && obiekt.get_zgody().count(ksywa) == 0 && obiekt.get_opcja() == 1) {			// Jeœli mapa zgód nie jest pusta AND zalogowany wspólnik nie odda³ g³osu TO mu sie tu cos pojawi
			cout << "Oczekuje na Ciebie glosowanie w sprawie zmiany limitu wspolniczego" << endl;
			cout << "Dla przypomnienia: limit wspolniczy to kwota, od której przelew musi byc autoryzowany przez pozostalych wspolnikow." << endl;
			cout << "Za zmiana limitu opowiedzieli sie juz: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == true) cout << im_name << endl;
			}
			cout << "Przeciwko zdazyli opowiedziec sie: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == false) cout << im_name << endl;
			}
			make_decision(obiekt, ksywa);
			interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		}
		else if (obiekt.get_zgody().size() >= 1 && obiekt.get_zgody().count(ksywa) == 0 && obiekt.get_opcja() == 2) {			// Jeœli mapa zgód nie jest pusta AND zalogowany wspólnik nie odda³ g³osu TO mu sie tu cos pojawi
			cout << "Oczekuje na Ciebie glosowanie w sprawie zmiany limitu adminowego" << endl;
			cout << "Dla przypomnienia: limit adminowy to kwota, od której przelew musi byc autoryzowany przez Administratora, tzn musi sie on skontaktowac z Firma w celu jego autoryzacji." << endl;
			cout << "Za zmiana limitu opowiedzieli sie juz: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == true) cout << im_name << endl;
			}
			cout << "Przeciwko zdazyli opowiedziec sie: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == false) cout << im_name << endl;
			}
			make_decision(obiekt, ksywa);
			interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		}
		else if (obiekt.get_zgody().size() >= 1 && obiekt.get_zgody().count(ksywa) == 0 && obiekt.get_opcja() == 3) {			// Jeœli mapa zgód nie jest pusta AND zalogowany wspólnik nie odda³ g³osu TO mu sie tu cos pojawi
			cout << "Oczekuje na Ciebie glosowanie w sprawie wykonania przelewu o kwocie przekraczajacej limit" << endl;
			cout << "Za wyslaniem opowiedzieli sie juz: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == true) cout << im_name << endl;
			}
			cout << "Przeciwko zdazyli opowiedziec sie: " << endl;
			for (pair<string, bool> element : obiekt.get_zgody()) {
				string im_name = element.first;
				bool zgoda = element.second;
				if (zgoda == false) cout << im_name << endl;
			}
			transfer_vote(obiekt, ksywa, tmp);
			interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		}
		else {
			cout << "Nie ma zadnych nowych akcji" << endl;
			system("pause");
			interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		}
		break;
	case 6:
		obiekt.modifying_account(ksywa);
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 7:
		cout << "Wiadomosc: " << endl
			<< obiekt.get_message() << endl;

		system("pause");
		interfejs(obiekt, ksywa, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 8:
		cout << "Trwa wylogowanie" << endl;
		system("pause");
		ekran_startowy();
		break;
	}
	
}





void interfejs(Klient& obiekt, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje) {

	system("CLS");
	int opcja = 99;
	string msg, ID_adresata, tmp1, tmp2;
	long double kwota;

	cout << "Witaj ponownie, " << obiekt.get_imie() << "!" << endl;
	cout << "Znajdujesz sie obecnie w dostepnym tylko dla Ciebie panelu zarz¹dzania swoim kontem osobistym." << endl;
	cout << "Aby wybrac opcje prosze wpisac odpowiednia cyfre." << endl;
	cout << "1. Sprawdz saldo" << endl;
	cout << "2. Skontaktuj sie z pracownikiem" << endl;
	cout << "3. Opcje konta" << endl;
	cout << "4. Dokonaj przelewu" << endl;
	cout << "5. Rzeczy wymagajace Twojej uwagi" << endl;
	cout << "6. Wyloguj sie" << endl;
	cout << "Wybor: ";

	opcja = check_int(1);				//funkcja proszaca o wpisanie liczby i sprawdza jej poprawnosc (nie tylko czy int sie pokrywa, ale czy to wgl jest int)

	switch (opcja) {
	case 1:
		system("CLS");
		cout << "Stan konta wynosi: " << obiekt.get_saldo() << " PLN" << endl;
		cout << "Wcisnij dowolny klawisz aby powrocic do menu glownego" << endl;
		system("pause");
		interfejs(obiekt, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 2:
		system("CLS");
		wyslij_waidomosc(obiekt, pracownicy, admini);
		interfejs(obiekt, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 3:
		system("CLS");
		obiekt.modifying_account();
		interfejs(obiekt, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 4:
		system("CLS");
		cout << "Podaj ID konta na ktore chcesz przelac pieniadze: ";
		cin >> ID_adresata;
		while (czy_tylko_cyfry(ID_adresata) == false) {

			system("CLS");
			cout << "Niepoprawnie wprowadzone ID. ID moze zawierac tylko cyfry. Sprobuj jeszce raz:" << endl;

			cin >> ID_adresata;
		}
		cout << "Podaj imie i nazwisko osoby, do ktorej wysylasz pieniadze: ";
		cin >> tmp1;
		kwota = 0;
		while (kwota == 0) {
			cout << "Podaj kwote, ktora chcesz wyslac: ";
			cin >> tmp2;
			kwota = check_double(tmp2);
			if (kwota == 0) cout << "Wprowadzono niewlasciwe znaki" << endl;
			while (kwota > obiekt.get_saldo()) {

				cout << "Nie masz takich srodkow na koncie" << endl;
				cout << "Podaj kwote, ktora chcesz wyslac: ";
				cin >> tmp2;
				kwota = check_double(tmp2);
				if (kwota == 0) cout << "Wprowadzono niewlasciwe znaki" << endl;
			}
		}
		
		if (kwota >= obiekt.get_prog()) { 			//koniecznie chce podawac wartosci kwota0fir i ajidi0fir aby moc je wyczyscic pod nastepne glosowania!
			add_notification(("Przelew N: " + obiekt.get_ID() + " A: " + ID_adresata + " K: " + tmp2), 1, pracownicy, admini);
			cout << "Przelew zostanie wyslany po zatwierdzeniu przez admina" << endl;
		}
		else {                         //jesli poprzednie ify niespelnione to zwykly transfer

			przelew_realizacja(obiekt, ID_adresata, kwota, pracownicy, admini, klienci, firmy, fundacje);


		}
		system("pause");
		interfejs(obiekt, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 5:
		obiekt.show_message();
		system("pause");
		interfejs(obiekt, pracownicy, admini, klienci, firmy, fundacje);
		break;
	case 6:
		ekran_startowy();
		break;
	}
}


void przelew_realizacja(Firma &obiekt, string adres_adresata, long double kwota, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje) {

	long double aktualne_saldo_odbiorcy;
	long double aktualne_saldo_nadawcy = obiekt.get_saldo();

	if (znajdz_po_ID(klienci, adres_adresata) != klienci.size()) { //gdy znaleziono takie ID //trzeba dodac pole message w firmie i fundacji

	aktualne_saldo_odbiorcy = klienci[znajdz_po_ID(klienci, adres_adresata)].get_saldo() + kwota;
	aktualne_saldo_nadawcy -= kwota;
	klienci[znajdz_po_ID(klienci, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);
	obiekt.set_saldo(aktualne_saldo_nadawcy);

	cout << endl << "Przelew zostal zrealizowany" << endl;
	}
	else if (znajdz_po_ID(firmy, adres_adresata) != firmy.size()) { //gdy znaleziono takie ID //trzeba dodac pole message w firmie i fundacji

		aktualne_saldo_odbiorcy = firmy[znajdz_po_ID(firmy, adres_adresata)].get_saldo() + kwota;
		aktualne_saldo_nadawcy -= kwota;
		firmy[znajdz_po_ID(firmy, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);
		obiekt.set_saldo(aktualne_saldo_nadawcy);

		cout << endl << "Przelew zostal zrealizowany" << endl;
	}
	else if (znajdz_po_ID(fundacje, adres_adresata) != fundacje.size()) { //gdy znaleziono takie ID //trzeba dodac pole message w firmie i fundacji

		aktualne_saldo_odbiorcy = fundacje[znajdz_po_ID(fundacje, adres_adresata)].get_saldo() + kwota;
		aktualne_saldo_nadawcy -= kwota;
		fundacje[znajdz_po_ID(fundacje, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);
		obiekt.set_saldo(aktualne_saldo_nadawcy);

		cout << endl << "Przelew zostal zrealizowany" << endl;
	}
	else {
		cout << endl << "Nie ma konta o takim ID" << endl;
	}
}

void przelew_realizacja(Fundacja &obiekt, string adres_adresata, long double kwota, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje) {

	long double aktualne_saldo_odbiorcy;
	long double aktualne_saldo_nadawcy = obiekt.get_saldo();

	if (znajdz_po_ID(klienci, adres_adresata) != klienci.size()) { //gdy znaleziono takie ID //trzeba dodac pole message w firmie i fundacji

		aktualne_saldo_odbiorcy = klienci[znajdz_po_ID(klienci, adres_adresata)].get_saldo() + kwota;
		aktualne_saldo_nadawcy -= kwota;
		klienci[znajdz_po_ID(klienci, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);
		obiekt.set_saldo(aktualne_saldo_nadawcy);

		cout << endl << "Przelew zostal zrealizowany" << endl;
	}
	else if (znajdz_po_ID(firmy, adres_adresata) != firmy.size()) { //gdy znaleziono takie ID //trzeba dodac pole message w firmie i fundacji

		aktualne_saldo_odbiorcy = firmy[znajdz_po_ID(firmy, adres_adresata)].get_saldo() + kwota;
		aktualne_saldo_nadawcy -= kwota;
		firmy[znajdz_po_ID(firmy, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);
		obiekt.set_saldo(aktualne_saldo_nadawcy);

		cout << endl << "Przelew zostal zrealizowany" << endl;
	}
	else if (znajdz_po_ID(fundacje, adres_adresata) != fundacje.size()) { //gdy znaleziono takie ID //trzeba dodac pole message w firmie i fundacji

		aktualne_saldo_odbiorcy = fundacje[znajdz_po_ID(fundacje, adres_adresata)].get_saldo() + kwota;
		aktualne_saldo_nadawcy -= kwota;
		fundacje[znajdz_po_ID(fundacje, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);
		obiekt.set_saldo(aktualne_saldo_nadawcy);

		cout << endl << "Przelew zostal zrealizowany" << endl;
	}
	else {
		cout << endl << "Nie ma konta o takim ID" << endl;
	}
}

void przelew_realizacja(Klient &obiekt, string adres_adresata, long double kwota, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje) {

	long double aktualne_saldo_odbiorcy;
	long double aktualne_saldo_nadawcy = obiekt.get_saldo();

	if (znajdz_po_ID(klienci, adres_adresata) != klienci.size()) { //gdy znaleziono takie ID //trzeba dodac pole message w firmie i fundacji

		aktualne_saldo_odbiorcy = klienci[znajdz_po_ID(klienci, adres_adresata)].get_saldo() + kwota;
		aktualne_saldo_nadawcy -= kwota;
		klienci[znajdz_po_ID(klienci, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);
		obiekt.set_saldo(aktualne_saldo_nadawcy);

		cout << endl << "Przelew zostal zrealizowany" << endl;
	}
	else if (znajdz_po_ID(firmy, adres_adresata) != firmy.size()) { //gdy znaleziono takie ID //trzeba dodac pole message w firmie i fundacji

		aktualne_saldo_odbiorcy = firmy[znajdz_po_ID(firmy, adres_adresata)].get_saldo() + kwota;
		aktualne_saldo_nadawcy -= kwota;
		firmy[znajdz_po_ID(firmy, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);
		obiekt.set_saldo(aktualne_saldo_nadawcy);

		cout << endl << "Przelew zostal zrealizowany" << endl;
	}
	else if (znajdz_po_ID(fundacje, adres_adresata) != fundacje.size()) { //gdy znaleziono takie ID //trzeba dodac pole message w firmie i fundacji

		aktualne_saldo_odbiorcy = fundacje[znajdz_po_ID(fundacje, adres_adresata)].get_saldo() + kwota;
		aktualne_saldo_nadawcy -= kwota;
		fundacje[znajdz_po_ID(fundacje, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);
		obiekt.set_saldo(aktualne_saldo_nadawcy);

		cout << endl << "Przelew zostal zrealizowany" << endl;
	}
	else {
		cout << endl << "Nie ma konta o takim ID" << endl;
	}
}

void przelew_realizacja(string adres_nadawcy, string adres_adresata, long double kwota, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje) {

	long double aktualne_saldo_odbiorcy;
	long double aktualne_saldo_nadawcy;
	bool czy_przelew_poprawnie_zrealizowany = false;
	
	if (znajdz_po_ID(klienci, adres_adresata) != klienci.size()) { //gdy znaleziono takie ID //zmiana salda odbiorcy

		aktualne_saldo_odbiorcy = klienci[znajdz_po_ID(klienci, adres_adresata)].get_saldo() + kwota;
		klienci[znajdz_po_ID(klienci, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);
		czy_przelew_poprawnie_zrealizowany = true;
	}
	else if (znajdz_po_ID(firmy, adres_adresata) != firmy.size()) { //gdy znaleziono takie ID //zmiana salda odbiorcy

		aktualne_saldo_odbiorcy = firmy[znajdz_po_ID(firmy, adres_adresata)].get_saldo() + kwota;
		
		firmy[znajdz_po_ID(firmy, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);	
		czy_przelew_poprawnie_zrealizowany = true;
	}
	else if (znajdz_po_ID(fundacje, adres_adresata) != fundacje.size()) { //gdy znaleziono takie ID //zmiana salda odbiorcy

		aktualne_saldo_odbiorcy = fundacje[znajdz_po_ID(fundacje, adres_adresata)].get_saldo() + kwota;
		
		fundacje[znajdz_po_ID(fundacje, adres_adresata)].set_saldo(aktualne_saldo_odbiorcy);	
		czy_przelew_poprawnie_zrealizowany = true;
	}
	else {
		cout << endl << "Nie ma konta adresata o takim ID" << endl;
	}


	if (czy_przelew_poprawnie_zrealizowany) {
		if (znajdz_po_ID(klienci, adres_nadawcy) != klienci.size()) { //gdy znaleziono takie ID //zmiana salda odbiorcy

			aktualne_saldo_nadawcy = klienci[znajdz_po_ID(klienci, adres_nadawcy)].get_saldo() - kwota;
			klienci[znajdz_po_ID(klienci, adres_nadawcy)].set_saldo(aktualne_saldo_nadawcy);

			cout << endl << "Przelew zostal zrealizowany" << endl;
		}
		else if (znajdz_po_ID(firmy, adres_nadawcy) != firmy.size()) { //gdy znaleziono takie ID //zmiana salda odbiorcy

			aktualne_saldo_nadawcy = firmy[znajdz_po_ID(firmy, adres_nadawcy)].get_saldo() - kwota;

			firmy[znajdz_po_ID(firmy, adres_nadawcy)].set_saldo(aktualne_saldo_nadawcy);

			cout << endl << "Przelew zostal zrealizowany" << endl;
		}
		else if (znajdz_po_ID(fundacje, adres_nadawcy) != fundacje.size()) { //gdy znaleziono takie ID //zmiana salda odbiorcy

			aktualne_saldo_nadawcy = fundacje[znajdz_po_ID(fundacje, adres_nadawcy)].get_saldo() - kwota;

			fundacje[znajdz_po_ID(fundacje, adres_nadawcy)].set_saldo(aktualne_saldo_nadawcy);

			cout << endl << "Przelew zostal zrealizowany" << endl;
		}
		else {
			cout << endl << "Nie ma konta nadawcy o takim ID" << endl;
		}
	}
}