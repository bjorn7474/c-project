/*
 * calc.h
 *
 *  Created on: 23 dec 2013
 *      Author: Ägaren
 */

#ifndef CALC_H_
#define CALC_H_

/* Parametervärden för black & scholes - modellen.*/
struct params {
	double asset;
	double strike;
	int time;
	double volat;
	double intRate;
};

/* Optionspris för köp- respektive säljoption.*/
struct option_prices {
	double call;
	double put;

};

typedef struct params Params;
typedef struct option_prices Option_prices;

double *calc_CDF(); // Beräknar värden på den kumulativa normalfördelningen.
double *calc_d1_d2(); // Beräknar d1 resp. d2 för Black & Scholes - modellen.
double *getCallArr(); // Genererar serie med köpoptionspriser.
double *getPutArr(); // Genererar serie med säljoptionspriser.

void printCalc(double *nx, double *primNx, double *d1d2); // skriver ut resultaten i konsolfönstret
void genOptionSer(); // loop som genererar optionspriser för olika löptider.
void set_params(double a, double s, int t, double v, double r); // mutator - inparametrar är de angivna parameterarna för Black & Scholes.

Params getParams(); // Returnerar en struct med parametervärdena.

int getMaturity(); // Returnerar den initiala löptiden.

#endif /* CALC_H_ */
