#include "bank.h"

using namespace std;


void make_decision(Firma& obiekt, string ksywa);
void checking_votes(Firma &obiekt, string tmp, string kwota0);
void send_proposition(Firma& obiekt, string ksywa, int opcja);

void make_decision(Fundacja& obiekt, string ksywa);
void checking_votes(Fundacja& obiekt, string tmp, string kwota0);
void send_proposition(Fundacja& obiekt, string ksywa, int opcja);

void transfer_request(Fundacja& obiekt, string ksywa, long double kwota, string ajdi);
void transfer_request(Firma& obiekt, string ksywa, long double kwota, string ajdi);
void transfer_vote(Fundacja& obiekt, string ksywa, string ajdi);
void transfer_vote(Firma& obiekt, string ksywa, string ajdi);