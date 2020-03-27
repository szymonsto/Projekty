
#ifndef BANK_H

#define BANK_H

#include <iostream>

#include <vector>

#include <map>



using namespace std;

void kalkulator_kredytowy(void); //caly interfejs kalkulatora kredytowego

void kalkulator_lokat(void);	//caly interfejs kalkulatora lokat


class Konto { //klasa, z ktorej beda dziedziczyc klasy odpowiadajace za konkretne rodzaje kont
	   
protected: //jest protected, zeby dalo sie zrobic operator w klasach potomnych
	string m_ID;
	string m_password;	

public:

	//deklaracja konstruktor
	Konto(const string& ID, const string& password);


	//deklaracja gettery settery

	string get_ID(void) const { return m_ID; }
	string get_password(void) const { return m_password; }
	void set_ID(const string& ID);
	void set_password(const string& password);
	   
	//deklaracja metod

	bool logowanie(void);	//zawoera interfejs logowania; true oznacza poprawne logowanie
};


class Klient : public Konto { 
	/*Konto indywidualne
	Dostep do niego ma tylko jedna osoba (obiekt posiada jedno haso dostepu)	
	Definicje znajduja sie w pliku Klient.cpp
	*/

private:

	string m_imie;
	string m_nazwisko;
	long double m_saldo;	//posiadane srodki na koncie
	long double m_prog;		//kwota ustalana przez klienta od ktorej admin musi zatwierdzic przelew
	string m_message;		//przechowuje wiadomosc od pracownika

public:
	 	//konstruktor

	Klient(const string& ID, const string& password, const string& imie, const string& nazwisko, long double saldo, long double prog, string message);

	string get_imie(void) const { return m_imie; }
	string get_nazwisko(void) const { return m_nazwisko; }
	long double get_saldo(void) { return m_saldo; }
	long double get_prog(void) { return m_prog; }
	string get_message(void) const { return m_message; }

	Klient& operator= (const Klient& rhs) { //operator

		m_imie = rhs.m_imie;
		m_ID = rhs.m_ID;
		m_password = rhs.m_password;
		m_nazwisko = rhs.m_nazwisko;
		m_saldo = rhs.m_saldo;
		m_prog = rhs.m_prog;
		m_message = rhs.m_message;

		return *this;
	}
	
	void set_imie(string imie);
	void set_nazwisko(string nazwisko);
	void set_saldo(long double saldo);
	void set_prog(long double prog);
	void set_message(string message); 


	//metody

	bool logowanie(void);
	void show_message(void);
	void setting_treshold(void);			//interfejs do ustawiania progu
	void modifying_account(void);			//interfejs modyfikowania konta   
};


class Firma : public Konto {
	/*Konto indywidualne
	Dostep do niego ma wielu wspolnikow (dlatego hasla sa vectorem)
	Definicje znajduja sie w pliku Firma.cpp
	Zmiany sa mozliwe gdy wszyscy wspolnicy sie zgodza (przez glosowanie)
	Propozycja, nad ktora glosuja jest przechowywana w m_propozycja
	*/

private:
	string m_nazwa; //nazwa firmy
	long double m_saldo; //stan konta
	map <string, string> m_passwords; //hasla wspolnikow (kazdy ma swoje)
	map <string, string> m_imie; //imiona wspolnikow
	map <string, bool> m_zgody; //przechowuje zgody podczas glosowan ( np. przy wyborze progu)
	long double m_prog_admin;	//prog kwoty przelewu, przy ktorym admin musi zatwoerdzic przelew
	long double m_prog_wspolnik; //prog kwoty przelewu, przy ktorym wspolnicy musi zatwoerdzic przelew (do tego jest uzywane m_zgody)
	long double m_propozycja; //przechowuje propozycje nowego progu
	int m_opcja; 
	string m_message;		//przechowuje wiadomosc od pracownika

public:
	// konstruktor 

	Firma(const string& ID, const string& password, const string& nazwa, long double saldo,map<string, string> passwords, map<string, string> imie, long double prog_admin, long double prog_wspolnik, map<string,bool> zgody, long double propozycja, int opcja);

	//gettery i settery

	string get_nazwa(void) const;
	long double get_saldo(void);
	long double get_prog_admin(void);
	long double get_prog_wspolnik(void);
	map<string, string> get_passwords(void);
	map <string, string> get_imie(void);
	map <string, bool> get_zgody(void);
	long double get_propozycja(void);
	int get_opcja(void);
	string get_message(void) const { return m_message; }
	   
	void set_imie(map<string, string> &imie);
	void set_passwords(map<string, string> &passwords);
	void set_nazwa(string &nazwa);
	void set_saldo(long double &saldo);
	void set_prog_admin(long double &prog_admin);
	void set_prog_wspolnik(long double &prog_wspolnik);
	void set_zgody(map<string,bool> &zgody);
	void set_propozycja(long double &propozycja);
	void set_opcja(int& opcja);
	void set_message(string message) { m_message = message; }
	
	//metody

	void ustawianie_progu(Firma &obiekt, string ksywa);			//interfejs do ustawiania progu
	bool logowanie(void);					//logowanie dla firm różni sie ze wzgledu na ilość osób z dostępem do konta 
	void modifying_account(string ksywa);			//interfejs modyfikowania konta
};



struct powiadomienia {						//do uzycia w klasach pracownik i admin
	int level{};
	std::string tresc = "";
};

class Pracownik : public Konto {			// trzeba dodac dodatkowe zabezpieczenia
	/*
	Otrzymuje i moze wysylac wiadomosci	
	*/

public: 
	std::string m_nazwisko;
	vector <powiadomienia> m_notifications;	//zawiera powiadomienia wraz z uwzględnieniem jego priorytetu
	Pracownik(const std::string& ID, const std::string& password, const std::string& nazwisko);
	std::string get_nazwisko(void) const { return m_nazwisko; }
	vector <powiadomienia> get_notifications(void) { return m_notifications; }
	void set_nazwisko(const std::string& nazwisko);
	void set_notifications(powiadomienia notification);

	//metody
	void show_notifications_prac(void); //nie wypisuje adminowych powaidomien 

};
class Fundacja : public Firma {

	/*
		wiele osob ma dostep do konta
		osoba, kotora nie posiada hasla ma dostep do informacji o stanie konta	
	*/


private:

	/*string m_nazwa; //nazwa fundacji
	long double m_saldo; //stan konta
	map <string, string> m_passwords; //zawiera hasla
	map <string, string> m_imie; 
	map<string, bool> m_zgody;
	long double m_prog_admin;
	long double m_prog_wspolnik;
	long double m_propozycja;
	int m_opcja;
	string m_message;		//przechowuje wiadomosc od pracownika*/
public:

	// konstruktor 
	Fundacja(const string& ID, const string& password, const string& nazwa, long double saldo, map<string, string> passwords, map<string, string> imie, long double prog_admin, long double prog_wspolnik, map<string, bool> zgody, long double propozycja, int opcja);
	//gettery i settery

	/*string get_nazwa(void) const;
	long double get_saldo(void);
	long double get_prog_admin(void);
	long double get_prog_wspolnik(void);
	long double get_propozycja(void);
	map <string, string> get_passwords(void);
	map <string, string> get_imie(void);
	map <string, bool> get_zgody(void);
	int get_opcja(void);
	string get_message(void) const { return m_message; }

	void set_imie(map<string, string>& imie);
	void set_passwords(map<string, string>& passwords);	
	void set_nazwa(string& nazwa);
	void set_saldo(long double& saldo);
	void set_prog_admin(long double& prog_admin);
	void set_prog_wspolnik(long double& prog_wspolnik);
	void set_zgody(map<string, bool>& zgody);
	void set_propozycja(long double& propozycja);
	void set_opcja(int& opcja);
	void set_message(string message) { m_message = message; }
	   
	//metody
	void ustawianie_progu(Fundacja& obiekt, string ksywa);			//interfejs do ustawiania progu*/
	bool logowanie(Fundacja &obiekt);					//logowanie dla firm różni sie ze wzgledu na ilość osób z dostępem do konta	
	//void modifying_account(string ksywa);			//interfejs modyfikowania konta
};


class Admin : public Pracownik {										//tu tez dodatkowe zabezpieczenia trzeba dodac
/*
	Otrzymuje wszystkie powaidomienia oprocz tych z waidomosciami
	Zatwierdza przelewy, tworzy konta, 
*/

public:

	vector<Klient> m_klienci_nowi; //zwaieraja obiekty do stworzenia
	vector<Firma> m_firmy_nowe;//zwaieraja obiekty do stworzenia		
	vector<Fundacja> m_fundacje_nowe;//zwaieraja obiekty do stworzenia

	Admin(const std::string& ID, const std::string& password, const std::string& nazwisko/*, vector<powiadomienia> notifications*/);

	//~Admin();



	bool transfer_approval(powiadomienia notification);		//zatwierdzanie operacji przelewy wysokogotówkowe

	bool give_back_control(powiadomienia notification);						//odblokowuje zablokowane konto	
	void creating_account_approval(int nr_powiadomienia, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje);

	bool modifying_account_approval(powiadomienia notification);		//zatwierdzanie modyfikacji konta


																		//zwraca kod z operacja jaka ma byc wykonana w mainie
	void show_notifications_adm(vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje);
};


void add_notification(std::string tresc, int level, vector<Pracownik>& pracownicy, vector<Admin>& admini);		//pojawiające sie powiadomienie jest dodawane do puli powiadomien rozdzielanych pomiedzy pracownikow

void add_notification(Firma obiekt, vector<Admin>& admini);

void add_notification(Fundacja obiekt, vector<Admin>& admini);

void add_notification(Klient obiekt, vector<Admin>& admini);

																												//tu tez bedzie kierowanie do odpowieniego pracownika (3.)

int znajdz_po_ID(vector<Klient>& klienci, std::string wpisane_ID); //po wpisaniu ID bedzie zwracalo pozycje w vectorze, na ktorej jest ta osoba/firma/pracownik

int znajdz_po_ID(vector<Firma>& firmy, std::string wpisane_ID);

int znajdz_po_ID(vector<Pracownik>& pracownicy, std::string wpisane_ID);

int znajdz_po_ID(vector<Admin>& admini, std::string wpisane_ID);

int znajdz_po_ID(vector<Fundacja>& fundacje, std::string wpisane_ID);

std::string losowanie_ID(int liczba_znakow); //uzwyane w funckji void prosba_o_stworzenie_konta(int opcja_submenu)

void wykonanie_operacji(std::string kod_operacji, vector<Klient>& klienci); //wykonuje dzialamnie zatwierdzone przez admina (tworzenie konta/ kasowanie konta/ przelew /...)

//void wyslij_przelew(std::string wpisane_ID, vector<Pracownik>& pracownicy, vector<Admin>& admini);

std::string int_na_string(int liczba);

int string_na_int(std::string napis);

int potega(int podstawa, int wykladnik);

bool czy_zablokowane(vector<Admin>& admini, std::string ID); //funkcja sprawdza czy konto zostalo juz wczesniej zablokowane, zeby nie blokowac drugi raz i nie wysylac drugiego powaidomieni do admina

bool czy_istnieje_ID(std::string ID, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje, vector<Pracownik>& pracownicy, vector<Admin>& admini);	//sprawdz czy istnieje podane ID

bool czy_tylko_cyfry(std::string wyraz);	//sprawdza czy wyraz sklada sie tylko z cyfr

bool czy_tylko_litery_i_cyfry(std::string wyraz);	//sprawdza czy wyraz sklada sie tylko z liter lub cyfr

std::string na_male(std::string wyraz);		//zamienia wyraz na male litery

std::string pierwsza_duza(std::string wyraz);	//zamienia pierwsza litere wyrazu na duza


//tu tez bedzie kierowanie do odpowieniego pracownika (3.)



void tworzenie_konta_firmowego(vector<Firma> &istniejace, vector<Pracownik>& pracownicy, vector<Admin>& admini);

void tworzenie_konta_fundacji(vector <Fundacja> & istniejace, vector<Pracownik>& pracownicy, vector<Admin>& admini);

void tworzenie_konta_klienta(vector <Klient>& istniejace, vector<Pracownik>& pracownicy, vector<Admin>& admini);

void wpisywanie_do_pliku_klient(vector < Klient> & spis);

void wpisywanie_do_pliku_firma(vector<Firma>& spis);

void wpisywanie_do_pliku_fundacje(vector<Fundacja>& spis);

void wczytywanie_firmy(vector<Firma>& firmy, int iteracje);

void wczytywanie_fundacje(vector<Fundacja>& fundacje, int iteracje);

void wczytywanie_klient(vector<Klient>& spis, int iteracje);

void wpisywanie_do_pliku_pracownik(vector<Pracownik>& spis);

void wpisywanie_do_pliku_admin(vector<Admin>& spis);

void wczytywanie_admin(vector<Admin>& spis, int iteracje);

void wczytywanie_pracownik(vector<Pracownik>& spis, int iteracje);

int zliczanie_linii_pracownicy(void);

int zliczanie_linii_admini(void);

string znajdz_po_imieniu(int& numerek, string& imm, int& opcja);
string znajdz_po_loginie(int& numerek, int& opcja);
string interfejs_logowania(void);
void zaloguj_do_klienta(void);
void zaloguj_do_firmy(int& opcja);
void zaloguj_do_fundacji(int& opcja);
void ekran_startowy(void);
int znajdz_firme(string& ID);
int znajdz_fundacje(string& ID);
int zliczanie_linii_klienci(void);
int zliczanie_linii_firmy(void);
int zliczanie_linii_fundacje(void);		// switch-case ani ify nie chcialy wspolpracowac z fstream: switch-case zwracal bledy, ify ignorowaly przypisujac zawsze 0
void zaloguj_do_admina(void);
void zaloguj_do_pracownika(void);

void wyslij_waidomosc(Klient& obiekt, vector<Pracownik>& pracownicy, vector<Admin>& admini); //to jest w pliku communication.cpp (na koncu pliku)
void wyslij_waidomosc(Firma& obiekt, vector<Pracownik>& pracownicy, vector<Admin>& admini);
void wyslij_waidomosc(Fundacja& obiekt, vector<Pracownik>& pracownicy, vector<Admin>& admini);
void wyslij_waidomosc(string ID_adresata, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje);

void wykonaj_przelew_admin(string adres_nadawcy, string adres_adresata, long double kwota); //w main1.cpp

#endif