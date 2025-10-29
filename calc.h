/*
 * calc.h
 *
 *  Created on: 23 dec 2013
 *      Author: �garen
 */

#ifndef CALC_H_
#define CALC_H_

/* Parameterv�rden f�r black & scholes - modellen.*/
struct params {
	double asset;
	double strike;
	int time;
	double volat;
	double intRate;
};

/* Optionspris f�r k�p- respektive s�ljoption.*/
struct option_prices {
	double call;
	double put;

};

typedef struct params Params;
typedef struct option_prices Option_prices;

double *calc_CDF(); // Ber�knar v�rden p� den kumulativa normalf�rdelningen.
double *calc_d1_d2(); // Ber�knar d1 resp. d2 f�r Black & Scholes - modellen.
double *getCallArr(); // Genererar serie med k�poptionspriser.
double *getPutArr(); // Genererar serie med s�ljoptionspriser.

void printCalc(double *nx, double *primNx, double *d1d2); // skriver ut resultaten i konsolf�nstret
void genOptionSer(); // loop som genererar optionspriser f�r olika l�ptider.
void set_params(double a, double s, int t, double v, double r); // mutator - inparametrar �r de angivna parameterarna f�r Black & Scholes.

Params getParams(); // Returnerar en struct med parameterv�rdena.

int getMaturity(); // Returnerar den initiala l�ptiden.

#endif /* CALC_H_ */
