/*
/**
 * Bj�rn Hallstr�m
 * main - h�r anropas GUI
 * 2014-01-06
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "gui.h"


int main(int argc, char* argv[]) {

	gtk_init(&argc, &argv);

	gui();

	return 0;
}

