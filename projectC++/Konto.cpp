#include <iostream>
#include<string>
#include"bank.h"

using std::cout;
using std::cin;
using std::endl;




bool Konto::logowanie(void) { 

	std::string password_wpisane{};
	int liczba_prob{ 3 }; //zadana liczba prob logowania

	while (liczba_prob > 0) {
	
		cout << "Password :" << endl;
		cin >> password_wpisane;

		password_wpisane = na_male(password_wpisane);

		while (czy_tylko_litery_i_cyfry(password_wpisane) == false) {

			system("CLS");
			cout << "Niepoprawnie wprowadzone haslo. haslo moze zawierac tylko litery i cyfry. Sprobuj jeszce raz" << endl
				<< "Password :" << endl;
			cin >> password_wpisane;
		}

		system("CLS"); //czyszczenie konsoli

		if (password_wpisane == m_password) {		//gdy wprowadzono poprawne has³o funkcja zwraca true (logowanie pomyœlne)
			cout << "Logowanie pomyslne." << endl;
			return true;
		}
		else {
			cout << "Blad logowania. Prosze spawdzic poprawnosc danych." << endl;
			liczba_prob--; //gdy wprowadzono z³e has³o liczba prób jest zmniejszana o jeden
		}
	}

	cout << "Przekroczono liczbe prob logowania. Konto zostaje zablokowane. W celu odblokowania prosze skontaktowac sie z administratorem." << endl;
	return false;		//jeœli pêtla while zosta³a zakoñczona to znaczy, ¿e wykorzystano wszystkie próby logowania (zablokowanie konta)
}

Konto::Konto(const std::string& ID, const std::string& password) : m_ID{ ID }, m_password{ password }{

	   	 
}

void Konto::set_ID(const std::string& ID) { m_ID = ID; }
void Konto::set_password(const std::string& password) { m_password = password; }