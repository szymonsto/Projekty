#include <iostream>
#include<string>
#include<vector>
#include"bank.h"

using std::cout;
using std::cin;
using std::endl;

int min_powiadomien(vector<Pracownik>& pracownicy) { //zwraca numer w wektorze przcownikow, dla ktorego jest najmniej powiadomien (, zeby sprawiedzliwie rozdzielac powiadomienia)
	
	unsigned int min_pow = ((pracownicy[0]).get_notifications()).size();
	int iter_min_pow{};
	
	for (unsigned int i = 0; i < pracownicy.size(); i++) {

		if (min_pow > (pracownicy[i].get_notifications()).size()) {
			min_pow = (pracownicy[i].get_notifications()).size();
			iter_min_pow = (int) i;
		}
	}
	
	return iter_min_pow;
}
int min_powiadomien(vector<Admin>& admini) {//zwraca numer w wektorze adminow, dla ktorego jest najmniej powiadomien (, zeby sprawiedzliwie rozdzielac powiadomienia)
	
	unsigned int min_pow = ((admini[0]).get_notifications()).size();
	int iter_min_pow{};

	for (unsigned int i = 0; i < admini.size(); i++) {

		if (min_pow > (admini[i].get_notifications()).size()) {
			min_pow = (admini[i].get_notifications()).size();
			iter_min_pow = (int) i;
		}
	}
	
	return iter_min_pow;
}

//dodawanie powaidomien i rozdzielanie powiadomien
void add_notification(string tresc, int level, vector<Pracownik> &pracownicy, vector<Admin> &admini) {

	powiadomienia powiadomienie;
	powiadomienie.level = level;
	powiadomienie.tresc = tresc;
	
	try {

		if (level < 0 || level > 4) throw "Level musi zawierac sie w przedziale <0, 4>";

		if (level == 0) {
			pracownicy[min_powiadomien(pracownicy)].set_notifications(powiadomienie);

		}
		else {
			admini[min_powiadomien(admini)].set_notifications(powiadomienie);
		}
	}
	catch (const char* ex) {
		cerr << ex << endl;
	}
	
	 
}

void add_notification(Firma obiekt, vector<Admin>& admini) {

	powiadomienia powiadomienie;
	powiadomienie.level = 2; //2 lvl to tworzenie konta
	powiadomienie.tresc = "Tworzenie konta: I: " + obiekt.get_ID() + " R: 2" + " N: " + na_male(obiekt.get_nazwa()) + " M: " + int_na_string((int)(admini[(unsigned int) min_powiadomien(admini)].m_firmy_nowe.size())); //I -> identyfikator, P -> haslo, R -> rodzaj konta (1->klient), M -> miejsce w wektorze nowych kont=> to bedzie potrzebne w klasie admin do tworzenia konta
	
	admini[(unsigned int) min_powiadomien(admini)].m_firmy_nowe.push_back(obiekt);
	admini[(unsigned int) min_powiadomien(admini)].set_notifications(powiadomienie);
	
}
void add_notification(Fundacja obiekt, vector<Admin>& admini) {

	powiadomienia powiadomienie;
	powiadomienie.level = 2; //2 lvl to tworzenie konta
	powiadomienie.tresc = "Tworzenie konta: I: " + obiekt.get_ID() + " R: 5" + " N: " + na_male(obiekt.get_nazwa()) + " M: " + int_na_string((int)(admini[(unsigned int) min_powiadomien(admini)].m_fundacje_nowe.size())); //I -> identyfikator, P -> haslo, R -> rodzaj konta (1->klient), M -> miejsce w wektorze nowych kont=> to bedzie potrzebne w klasie admin do tworzenia konta


	admini[(unsigned int) min_powiadomien(admini)].m_fundacje_nowe.push_back(obiekt);
	admini[(unsigned int) min_powiadomien(admini)].set_notifications(powiadomienie);

}

void add_notification(Klient obiekt, vector<Admin>& admini) {

	powiadomienia powiadomienie;
	powiadomienie.level = 2; //2 lvl to tworzenie konta
	powiadomienie.tresc = "Tworzenie konta: I: " + obiekt.get_ID() + " R: 1" + " N: " + na_male(obiekt.get_imie()) + " M: " + int_na_string((int)(admini[(unsigned int)min_powiadomien(admini)].m_klienci_nowi.size())); //I -> identyfikator, P -> haslo, R -> rodzaj konta (1->klient), M -> miejsce w wektorze nowych kont=> to bedzie potrzebne w klasie admin do tworzenia konta

	admini[(unsigned int)min_powiadomien(admini)].m_klienci_nowi.push_back(obiekt);
	admini[(unsigned int)min_powiadomien(admini)].set_notifications(powiadomienie);

}

