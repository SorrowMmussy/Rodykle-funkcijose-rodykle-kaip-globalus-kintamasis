/*==============================================================
Denas Kinderis
Kovo 20, 2017
Integralas f(x) reziuose [a,b]
metodas: Monte-Carlo metodas
----------------------------------------------------------------
ivedimas:
f   - paprasta lygtis (iveda vartotojas)
a,b - 2 taškai intervalo, kuri iveda vartotojas
n   - skaicius atsitiktiniu tasku xi
output:
r      - integralo atsakymas
errest - paklaida (estimated error)
================================================================*/
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

double int_mc1(double(*)(double), double&, double, double, int);
double f(double);

int main()
{
	double a, b, mc, errest;
	int i, n;
	int ntimes;
	const double pi = 3.1415926;

	cout.precision(6);
	cout.setf(ios::fixed | ios::showpoint);

	/* Pradine informacija */
	cout << "Iveskite a: ";
	cin >> a;
	cout << "Iveskite b: ";
	cin >> b;
	cout << "Iveskite n: ";
	cin >> n;

	ntimes = 16;

	cout << "    Taskai   " << "Integralas  " << " Paklaida" << endl;

	/* step 2: Metame N atsitiktiniu tasku i nurodyta grafiko vietove */
	for (i = 0; i <= ntimes; i = i + 1)
	{
		mc = int_mc1(f, errest, a, b, n);

		cout << setw(10) << n << setw(12) << mc << setw(12) << errest << endl;

		n = n * 2;
	}

	system("pause");
	return 0;
}

/*
*  Integravimo funkcija
*/
double f(double x)
{
	const double pi = 3.1415926;
	double y;
	//PASTABA: Programa naudos SINX kaip pradine funkcijos reiksme. Pakeiskite y variantus i funkcija kurios norite ar reikia.
	y = sin(x);
	//y = cos(x);
	//   y = x;
	//    y = 2.0*sqrt(x)/((x+1.0)*(x+1.0));
	//    y = 0.2/(pow((x-6.0),2.0) + 0.02);
	//    y = x*cos(10.0*pow(x,2.0))/(pow(x,2.0) + 1.0);
	//    y = sqrt(x)/(x*x + 1.0);
	//y = sin(pi*x*x)/((x-pi)*(x-pi)+1);
	return y;
}
double int_mc1(double(*f)(double), double& errest, double a, double b, int n)
{
	double r, x, u, f2s, fs;
	/* kintamieji fs ir f2s naudojami integralo paklaidai skaiciuoti */

	srand(time(NULL));

	fs = 0.0;
	f2s = 0.0;

	for (int i = 1; i <= n; i = i + 1)
	{
		u = 1.0*rand() / (RAND_MAX + 1); /* atsitiktinis skaicius nuo 0.0 iki 1.0 */
		x = a + (b - a)*u;
		fs = fs + f(x);
		f2s = f2s + f(x)*f(x);
	}
	r = fs*(b - a) / n;
	/* integralo paklaida */
	fs = fs / n;
	f2s = f2s / n;
	errest = (b - a)*sqrt((f2s - fs*fs) / n);
	return r;
}