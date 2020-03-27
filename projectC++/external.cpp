#include "bank.h"
#include "interfejsy_kont.h"
#include <cmath>
#include <math.h>

void kalkulator_kredytowy(void) {
	system("CLS");
	int tmp1 = 0, tmp2 = 0;
	double rrso = 9.37;
	double opro = 9.50;
	double prowizja = 1.25;
	double do_splaty, tmp = 0;
	string kwota;
	double rata0, rata1;

	cout << "Witaj w opcji wyliczen kredytowych. W naszym banku prowizja wynosi " << prowizja << "%, a oprocentowanie " << opro << "%. Postepuj zgodnie z ponizszymi instrukcjami" << endl;
	cout << "Podaj kwote pozyczki: ";
	cin >> kwota;
	tmp = check_double(kwota);
	while (tmp == 0) {
		cout << "Podaj kwote pozyczki: ";
		cin >> kwota;
		tmp = check_double(kwota);
	}
	cout << "Podaj okres (wyrazony w miesiacach), na ktory chcesz rozlozyc splate (minimum 12 miesiecy): ";
	
		tmp1 = check_int(0);
	
	while (tmp1 < 12){
		cout << "Podaj okres (wyrazony w miesiacach), na ktory chcesz rozlozyc splate (minimum 12 miesiecy): ";
		
			tmp1 = check_int(0);
		
	}
	cout << "Podaj czestotliwosc splacania kredytu (ilosc platnych rat na rok): ";
	
		tmp2 = check_int(0);
	

	while (tmp2 < 1) {
		cout << "Podaj czestotliwosc splacania kredytu (ilosc platnych rat na rok) musi byc wieksza od 1: ";
		tmp2 = check_int(0);
	}

	double ciag = (tmp2 / (tmp2 + (opro / 100)));
	double ciag1 = pow(ciag, tmp2 * (double(tmp1 / 12.0)));
	rata0 = (tmp * (opro/100)) / (tmp2*(1-ciag1));
	rata1 = rata0 + rata0 * (prowizja/100);
	do_splaty = rata1 * tmp2 * (double(tmp1 / 12.0));
	cout << "Rata wyniesie: " << rata1 << "\nCalkowity kwota do splaty wyniesie: " << do_splaty << endl;
	system("pause");
}

void kalkulator_lokat(void) {
	long double V0, V, r, r1; //po kolei: kapita³ pocz¹tkowy, kapita³ koñcowy,  roczna stopa procentowa
	string V0w, rw, r1w, mw, nw;
	long long m, n; //liczba kapitalizacji w roku, liczba lat do konca kredutu
	system("CLS");
	cout << "Wprowadz dane: " << endl;
	cout << "Kapital poczatkowy: ";
	cin >> V0w;
	V0 = check_double(V0w);

	cout << "Liczba kapitalizacji w roku: ";
	
	m = check_int(0);

	cout << "Liczba lat do konca: ";
	
	n = check_int(0);
	cout << "Roczna stopa procentowa: ";
	cin >> rw;
	r = check_double(rw);
	r1 = r / 100;
	long double potega = pow(1 + (r1 / m), (m * n));
	V = V0 * potega;

	cout << "Kapital koncowy wyniesie: " << V << endl;
	system("pause");
}