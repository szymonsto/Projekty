//funkcje maj¹ce na celu podjecie wspólnej decyzji wraz ze wspólnikami

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "bank.h"
#include "communication.h"

using namespace std;

//obsluga glosowan

void send_proposition(Firma &obiekt, string ksywa, int opcja) {
	long double kwota;
	cout << "Zaproponuj nowy limit wspolniczy: ";
	cin >> kwota;
	obiekt.set_propozycja(kwota);
	//wys³anie zapytania do wspólników
	map<string, bool> zgody = obiekt.get_zgody();
	zgody[ksywa] = true;
	obiekt.set_zgody(zgody);
	obiekt.set_opcja(opcja);
	cout << "Dlugosc map zgod wynosi: " << obiekt.get_zgody().size() << endl;
	system("pause");
}


void make_decision(Firma &obiekt, string ksywa) {

	string opcja;		
	cout << "Czy zgadzasz siê na kwote " << obiekt.get_propozycja() << " jako nowy limit?" << endl;
	cout << "1 - jesli tak" << endl;
	cout << "2 - jesli nie" << endl;
	cout << "Wybor: ";
	cin >> opcja;
	cout << "\n";
	if (opcja == "1") {
		map<string, bool> zgody = obiekt.get_zgody();
		zgody[ksywa] = true;
		obiekt.set_zgody(zgody);
	}
	else if (opcja == "2") {
		map<string, bool> zgody2 = obiekt.get_zgody();
		zgody2[ksywa] = false;
		obiekt.set_zgody(zgody2);
	}
	else {
		cout << "Podano niewlasciwy znak, wprowadz ponownie" << endl;
		make_decision(obiekt, ksywa);
	}
}


void checking_votes(Firma &obiekt, string tmp, string kwota0) {
	
	if (obiekt.get_zgody().size() == obiekt.get_imie().size()) {
		int flaga = 0;
		long double kwota1 = 0;
		int wpisz = 0;
		map<string, bool> pusty;
		pusty.clear();
		for (pair<string, bool> element : obiekt.get_zgody()) {			
			string typo = element.first;
			bool zgoda = element.second;
			if (zgoda == true) flaga++;
		}
		if (flaga == obiekt.get_imie().size() && obiekt.get_opcja() == 1) {
			cout << "Nowa kwota wspolnicza przeglosowana!" << endl;
			long double kwota = obiekt.get_propozycja();
			obiekt.set_prog_wspolnik(kwota);
			obiekt.set_propozycja(kwota1);
			obiekt.set_zgody(pusty);
		}
		else if (flaga == obiekt.get_imie().size() && obiekt.get_opcja()==2) {
			cout << "Nowa kwota adminowa przeglosowana!" << endl;
			long double kwota = obiekt.get_propozycja();
			obiekt.set_prog_admin(kwota);
			obiekt.set_propozycja(kwota1);
			obiekt.set_zgody(pusty);
		}
		else if (flaga == obiekt.get_imie().size() && obiekt.get_opcja() == 3) {
			cout << "Przelew wysokokwotowy zostal zatwierdzony! Prosba o jego realizacja zostala przekazana do pracownikow banku" << endl;			
			obiekt.set_zgody(pusty);		
		}
		else {
			cout << "Glosowanie zostalo odrzucone" << endl;
			obiekt.set_propozycja(kwota1);
			obiekt.set_zgody(pusty);
			obiekt.set_opcja(wpisz);
		}
	}
	
}


void make_decision(Fundacja& obiekt, string ksywa) {

	string opcja;			
	cout << "Czy zgadzasz siê na kwote " << obiekt.get_propozycja() << " jako nowy limit?" << endl;
	cout << "1 - jesli tak" << endl;
	cout << "2 - jesli nie" << endl;
	cout << "Wybor: ";
	cin >> opcja;
	cout << "\n";
	if (opcja == "1") {
		map<string, bool> zgody = obiekt.get_zgody();
		zgody[ksywa] = true;
		obiekt.set_zgody(zgody);
	}
	else if (opcja == "2") {
		map<string, bool> zgody2 = obiekt.get_zgody();
		zgody2[ksywa] = false;
		obiekt.set_zgody(zgody2);
	}
	else {
		cout << "Podano niewlasciwy znak, wprowadz ponownie" << endl;
		make_decision(obiekt, ksywa);
	}
}


void checking_votes(Fundacja& obiekt, string tmp, string kwota0) { 

	if (obiekt.get_zgody().size() == obiekt.get_imie().size()) {
		int flaga = 0;
		long double kwota1 = 0;
		int wpisz = 0;
		map<string, bool> pusty;
		pusty.clear();
		for (pair<string, bool> element : obiekt.get_zgody()) {
			string typo = element.first;
			bool zgoda = element.second;
			if (zgoda == true) flaga++;
		}
		if (flaga == obiekt.get_imie().size() && obiekt.get_opcja() == 1) {
			cout << "Nowa kwota wspolnicza przeglosowana!" << endl;
			long double kwota = obiekt.get_propozycja();
			obiekt.set_prog_wspolnik(kwota);
			obiekt.set_propozycja(kwota1);
			obiekt.set_zgody(pusty);
		}
		else if (flaga == obiekt.get_imie().size() && obiekt.get_opcja() == 2) {
			cout << "Nowa kwota adminowa przeglosowana!" << endl;
			long double kwota = obiekt.get_propozycja();
			obiekt.set_prog_admin(kwota);
			obiekt.set_propozycja(kwota1);
			obiekt.set_zgody(pusty);
		}
		else if (flaga == obiekt.get_imie().size() && obiekt.get_opcja() == 3) {
			cout << "Przelew wysokokwotowy zostal zatwierdzony! Prosba o jego realizacja zostala przekazana do pracownikow banku" << endl;
			obiekt.set_zgody(pusty);		
		}
		else {
			cout << "Glosowanie zostalo odrzucone" << endl;
			obiekt.set_propozycja(kwota1);
			obiekt.set_zgody(pusty);
			obiekt.set_opcja(wpisz);
		}
	}

}

void send_proposition(Fundacja& obiekt, string ksywa, int opcja) {
	long double kwota;
	cout << "Zaproponuj nowy limit wspolniczy: ";
	cin >> kwota;
	obiekt.set_propozycja(kwota);
	//wys³anie zapytania do wspólników
	map<string, bool> zgody = obiekt.get_zgody();
	zgody[ksywa] = true;
	obiekt.set_zgody(zgody);
	cout << "Dlugosc map zgod wynosi: " << obiekt.get_zgody().size() << endl;
	system("pause");
}

void transfer_vote(Firma& obiekt, string ksywa, string ajdi) {

	string opcja;				
	cout << "Zostal zarzadzony przelew powyzej przeznaczonej kwoty, czy zgadzasz sie, aby na konto o numerze ID: " << ajdi << " zostala przelana kwota w wysokosci: " << obiekt.get_propozycja() << "?" << endl;
	cout << "1 - jesli tak" << endl;
	cout << "2 - jesli nie" << endl;
	cout << "Wybor: ";
	cin >> opcja;
	cout << "\n";
	if (opcja == "1") {
		map<string, bool> zgody = obiekt.get_zgody();
		zgody[ksywa] = true;
		obiekt.set_zgody(zgody);
	}
	else if (opcja == "2") {
		map<string, bool> zgody2 = obiekt.get_zgody();
		zgody2[ksywa] = false;
		obiekt.set_zgody(zgody2);
	}
	else {
		cout << "Podano niewlasciwy znak, wprowadz ponownie" << endl;
		transfer_vote(obiekt, ksywa, ajdi);
	}

}

void transfer_vote(Fundacja& obiekt, string ksywa, string ajdi) {

	string opcja;			
	cout << "Zostal zarzadzony przelew powyzej przeznaczonej kwoty, czy zgadzasz sie, aby na konto o numerze ID: " << ajdi << " zostala przelana kwota w wysokosci: " << obiekt.get_propozycja() << "?" << endl;
	cout << "1 - jesli tak" << endl;
	cout << "2 - jesli nie" << endl;
	cout << "Wybor: ";
	cin >> opcja;
	cout << "\n";
	if (opcja == "1") {
		map<string, bool> zgody = obiekt.get_zgody();
		zgody[ksywa] = true;
		obiekt.set_zgody(zgody);
	}
	else if (opcja == "2") {
		map<string, bool> zgody2 = obiekt.get_zgody();
		zgody2[ksywa] = false;
		obiekt.set_zgody(zgody2);
	}
	else {
		cout << "Podano niewlasciwy znak, wprowadz ponownie" << endl;
		transfer_vote(obiekt, ksywa, ajdi);
	}

}

void transfer_request(Firma& obiekt, string ksywa, long double kwota, string ajdi) {
	obiekt.set_propozycja(kwota);
	//wys³anie zapytania do wspólników
	map<string, bool> zgody = obiekt.get_zgody();
	zgody[ksywa] = true;
	obiekt.set_zgody(zgody);
	system("pause");
}

void transfer_request(Fundacja& obiekt, string ksywa, long double kwota, string ajdi) {
	obiekt.set_propozycja(kwota);
	//wys³anie zapytania do wspólników
	map<string, bool> zgody = obiekt.get_zgody();
	zgody[ksywa] = true;
	obiekt.set_zgody(zgody);
	system("pause");
}

void wyslij_waidomosc(Klient& obiekt, vector<Pracownik>& pracownicy, vector<Admin>& admini) {
	string message1;
	cout << " Napisz wiadomoœæ: ";
	
	cin >> message1; 

	add_notification("Waidomosc od " + obiekt.get_ID() + " : " + message1, 0, pracownicy, admini);
}

void wyslij_waidomosc(Firma& obiekt, vector<Pracownik>& pracownicy, vector<Admin>& admini) {
	string message1;
	cout << " Napisz wiadomoœæ: ";

	cin >> message1;

	add_notification("Waidomosc od " + obiekt.get_ID() + " : " + message1, 0, pracownicy, admini);
}

void wyslij_waidomosc(Fundacja& obiekt, vector<Pracownik>& pracownicy, vector<Admin>& admini) {
	string message1;
	cout << " Napisz wiadomoœæ: ";

	cin >> message1;

	add_notification("Waidomosc od " + obiekt.get_ID() + " : " + message1, 0, pracownicy, admini);
}

void wyslij_waidomosc(string ID_adresata, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje) {
	string message1;
	cout << " napisz wiadomosc: ";

	cin >> message1;

	if (znajdz_po_ID(klienci, ID_adresata) != klienci.size()) { //gdy znaleziono takie ID

		klienci[znajdz_po_ID(klienci, ID_adresata)].set_message(message1);
	}
	if (znajdz_po_ID(firmy, ID_adresata) != firmy.size()) { //gdy znaleziono takie ID //trzeba dodac pole message w firmie i fundacji

		firmy[znajdz_po_ID(firmy, ID_adresata)].set_message(message1);
	}
	if (znajdz_po_ID(fundacje, ID_adresata) != fundacje.size()) { //gdy znaleziono takie ID

		fundacje[znajdz_po_ID(fundacje, ID_adresata)].set_message(message1);
	}



}

