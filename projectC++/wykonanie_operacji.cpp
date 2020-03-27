#include <iostream>
#include<string>
#include<vector>
#include"bank.h"




bool czy_zablokowane(vector<Admin>& admini, string ID) { 
	//funkcja sprawdza czy konto zostalo juz wczesniej zablokowane, zeby nie blokowac drugi raz i nie wysylac drugiego powaidomieni do admina
	
	for (auto j : admini) { //sprawdza wszystkie powiadomienia u wszystkich adminow
		for (auto i : j.get_notifications()) {
			if (i.tresc.find("Zablokowane konto") == 0) {

				if (i.tresc.find("I: " + ID)) {
					return true;
				}
			}
		}
	}
	return false;

}

bool czy_istnieje_ID(string ID, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje, vector<Pracownik>& pracownicy, vector<Admin>& admini) {

	//sprawdz czy istnieje podane ID

	for (auto i : klienci)
		if (i.get_ID() == ID)	return true;

	for (auto i : firmy)
		if (i.get_ID() == ID)	return true;

	for (auto i : fundacje)
		if (i.get_ID() == ID)	return true;

	for (auto i : pracownicy)
		if (i.get_ID() == ID)	return true;

	for (auto i : admini)
		if (i.get_ID() == ID)	return true;
	

	return false;
}
