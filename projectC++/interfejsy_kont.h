#include <iostream>
#include <string>
#include "bank.h"

using namespace std;



//void interfejs(Firma& obiekt, string ksywa, vector<Pracownik>& pracownicy, vector<Admin>& admini);
void interfejs(Firma& obiekt, string ksywa, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje);

void interfejs(Fundacja& obiekt, string ksywa, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje);
void interfejs(Klient& obiekt, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje);
int check_int(int przel);
long double check_double(string j);

void przelew_realizacja(Klient &obiekt, string adres_adresata, long double kwota, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje);
void przelew_realizacja(Firma &obiekt, string adres_adresata, long double kwota, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje);
void przelew_realizacja(Fundacja &obiekt, string adres_adresata, long double kwota, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje);
void przelew_realizacja(string adres_nadawcy, string adres_adresata, long double kwota, vector<Pracownik>& pracownicy, vector<Admin>& admini, vector<Klient>& klienci, vector<Firma>& firmy, vector<Fundacja>& fundacje);