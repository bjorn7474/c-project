/*
 * gui.h
 *
 *  Created on: 6 jan 2014
 *      Author: Ägaren
 */

#ifndef GUI_H_
#define GUI_H_

int error_check(const gchar **params, double *paramsD); // initierar flyttalsparametrarna för parametrarna (vid inmating text) samt felkontroll.
void printCallPutPrices(double *callArr, double *putArr, int tTM); // skriver ut samtliga köp- och säljoptionspriser i konsolfönstret
int gui();
void printToFile(double* callArr, int tTM);
void printToCSV(double* callArr, double* putArr, int tTM);
void update_text_view(double* callArr, double* putArr, int tTM, GtkTextBuffer* text_buffer);

#endif /* GUI_H_ */
