/*
 * calc.c
 *
 * Björn Hallström
 * Här görs alla matematiska beräkningar för att generera optionspriserna.
 * 2014-01-06
 */

#include "calc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static Params bs;
static int T;

double *call_arr;
double *put_arr;

#define Y 0.2316419
#define A1 0.319381530
#define A2 -0.356563782
#define A3 1.781477937
#define A4 -1.821255978
#define A5 1.330274429

#define tY 250.0

/**
 * mutator-funktion - lägger in alla nödvändiga parametervärden i en struct. Här allokeras även minne för köpoptions- och säljoptionsvektorn.
 * double a (underliggande tillgångspris)
 * double s (lösenpris)
 * int t (löptiden)
 * double v (volatiliteten)
 * double r (riskfria marknadsräntan)
 */
void set_params(double a, double s, int t, double v, double r) {

	printf("SET PARAMS a: %lf, s: %lf, t: %d, v: %lf, r: %lf\n", a, s, t, v, r);

	bs.asset = a;
	bs.strike = s;
	bs.time = t;
	bs.volat = v;
	bs.intRate = r;

	call_arr = malloc(bs.time * sizeof(double));
	put_arr = malloc(bs.time * sizeof(double));

	T = bs.time;
}


void print() {

	printf("asset price = %lf", bs.asset);

}


/**
 * Beräknar de kumulativa sannolikhetsvärdena som senare används för att kunna beräkna priset på en köp- respektive säljoption.
 * För att göra detta används hjälpfunktionen calc_d1_d2 som returnerar d1 respektive d2.
 * För att kunna beräkna värden för den kumulativa normalfördelningen görs en polynomial approximation.
 * see John C. Hull - Options and other derivates (third edition) sidan 243.
 * return *nx (returnernar en array som innehåller de kumulativa värdena - fyra stycken ( N(d1), N(-d1), N(d2), N(-d2) ).
 */
double *calc_CDF() {

	double *d1d2 = calc_d1_d2(); // functionen returnerar en vektor som innehåller d1 och d2
	double d1 = fabs(d1d2[0]); // temp. variabler för d1 och d2.
	double d2 = fabs(d1d2[1]);

	/* Beräkna N'(x) för d1 och d2*/
	double primNx[2];
	primNx[0] = (1 / sqrt (2 * M_PI)) *
				pow(M_E, -0.5 * ( pow(d1, 2)) );
	primNx[1] = (1 / sqrt (2 * M_PI)) *
					pow(M_E, -0.5 * ( pow(d2, 2)) );

	/* Beräkna k för d1 och d2 givet Y */
	double k[2];
	k[0] = 1 / (1 + Y * d1);
	k[1] = 1 / (1 + Y * d2);

	/* Gör en polynomial approxiamtion av N(x) givet definierade konstanter samt N'(x)*/
	double *nx = malloc(4 * sizeof(double)); // deklarera en array för nx och allokera minne därefter

	nx[0] = 1 - primNx[0] * ( A1 * k[0] + A2 * pow(k[0], 2) + A3 * pow(k[0], 3) + A4 * pow(k[0], 4) + A5 * pow(k[0], 5) ); //N(d1)
	nx[1] = 1 - nx[0]; //N(-d1)
	nx[2] = 1 - primNx[1] * ( A1 * k[1] + A2 * pow(k[1], 2) + A3 * pow(k[1], 3) + A4 * pow(k[1], 4) + A5 * pow(k[1], 5) ); //N(d2)
	nx[3] = 1 - nx[2]; //N(-d2)

	if (d1d2[0] < 0) {
		nx[0] = 1 - nx[0];
		nx[1] = 1 - nx[0]; // N(-d1)
	}

	if (d1d2[1] < 0) {
		nx[2] = 1 - nx[2];
		nx[3] = 1 - nx[2]; // N(-d2)
	}

	//printCalc(nx, primNx, d1d2);

	free(d1d2); // Frigör minne då d1 och d2 ej behövs längre
	d1d2 = NULL; // Undvik dangling pointer

	return nx;
}

/**
 * Beräknar d1 och d2 för Black&Sholes-ekvationen. Värdena lagras i en vektor.
 * return *d1d2
 */
double *calc_d1_d2() {

	double *d1d2 = malloc(2 * sizeof(double));

	d1d2[0] = ( (log (bs.asset / bs.strike)) + (bs.intRate + (pow(bs.volat, 2.0) /2.0)) * (bs.time / tY) ) /
		 (bs.volat * sqrt(bs.time / tY));

	d1d2[1] = ( (log (bs.asset / bs.strike)) + (bs.intRate - (pow(bs.volat, 2.0) /2.0)) * (bs.time / tY) ) /
			 (bs.volat * sqrt(bs.time / tY));

	return d1d2;
}

/**
 * Funktion som skriver ut beräknade värden för Black%&Scholes (används i testsammanhang)
 */
void printCalc(double *nx, double *primNx, double *d1d2) {

	printf("N(d1) %lf\nN(-d1) %lf\nN(d2) %lf\nN(-d2) %lf\n", nx[0], nx[1], nx[2], nx[3]);
	printf("primNx0: %lf\nprimNx1 %lf\n", primNx[0], primNx[1]);
	printf("d1 %lf\nd2: %lf\n", d1d2[0], d1d2[1]);
}

/**
 * Beräknar slutligen priset för en köpoption och säljoption. Lagrar dessa i en ny vektor som innehåller alla succesiva priser fram till lösen.
 */
void calcOption() {

	double *nx = calc_CDF();

	double call = nx[0] * bs.asset - nx[2] * bs.strike * pow(M_E, -bs.intRate * bs.time / tY);
	double put = nx[3] * bs.strike * pow(M_E, -bs.intRate * bs.time / tY) - nx[1] * bs.asset;

	call_arr[T - bs.time] = call;
	put_arr[T - bs.time] = put;

	free(nx); // Frigör minne då nx ej behövs längre.
	nx = NULL; // Undvik dangling pointer.
}


/**
 * Loopar optionspriser för alla löptidsdagar
 */
void genOptionSer() {

	int i;
	for (i = 0; i < T; i++) {
		calcOption();
		bs.time--;
	}
	//printSer();
}


/**
 * Returnerar array med köptionspriser
 */
double *getCallArr() {

	return call_arr;
}


/**
 * Returnerar array med säljoptionspriser
 */
double *getPutArr() {

	return put_arr;
}


/**
 * Returnerar löptid
 * return int T
 */
int getMaturity() {

	return T;
}
