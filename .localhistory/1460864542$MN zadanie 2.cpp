// ConsoleApplication2.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#define EPS 0.00001
using namespace std;
int sprawdz_linie();
void macierz(int z, double **tablica);
void czesciowa_zamiana(int n, double **tablica);
void eliminacja(int n, double **tablica);
void zeruj(int n, double **tablica);
void oblicz_rank(int n, double **tablica, int *rankA, int *rankU);
void licz(int n, double **tablica, int *rankA, int *rankU);

int main()
{
	CHUJ
	int rankA = 0, rankU = 0, n = 0;
	n = sprawdz_linie();
	if (n != -1)
	{
		double **tablica = new double *[n];
		for (int i = 0; i < n; i++)
			tablica[i] = new double[n];

		macierz(n, tablica);
		czesciowa_zamiana(n, tablica);
		eliminacja(n, tablica);
		zeruj(n, tablica);
		oblicz_rank(n, tablica, &rankA, &rankU);
		licz(n, tablica, &rankA, &rankU);
	}

	return 0;
}

int sprawdz_linie()
{
	fstream file;
	file.open("plik.txt", ios_base::in);
	if (file.is_open() == true)
	{
		int number_of_lines = 0;
		string line;
		while (getline(file, line)) number_of_lines++;

		file.close();

		return number_of_lines;
	}

	else cout << "Plik otworzony niepoprawnie!";
	return -1;
}

void macierz(int n, double **tablica)
{
	int i, j;

	fstream file;
	file.open("plik.txt", ios_base::in);
	//if (file.is_open() == true) cout << "PLIK OTWORZONY POPRAWNIE" << endl;

	for (i = 0; i < n; i++)
		for (j = 0; j < n + 1; j++)

			file >> tablica[i][j];
	cout << "Podana macierz :";

	for (i = 0; i < n; i++)
	{
		cout << endl;
		for (j = 0; j < n + 1; j++)
			cout << tablica[i][j] << "\t";
	}
}

void czesciowa_zamiana(int n, double **tablica)
{
	double temp = 0;
	int i, j;

	for (j = 0; j < n + 1; j++)
		for (i = j; i < n; i++)
		{
			if (tablica[i][j] > tablica[j][j])
			{
				for (int k = 0; k < n + 1; k++)
				{
					temp = tablica[i][k];
					tablica[i][k] = tablica[j][k];
					tablica[j][k] = temp;
				}
			}
		}

	/*cout << "\n\n Macierz po zamianie :";
	for (i = 0; i < n; i++)
	{
		cout << endl;
		for (j = 0; j < n + 1; j++)
			cout << tablica[i][j] << "\t";
	}*/
}

void eliminacja(int n, double **tablica)
{
	int i, j, k = 0;

	for (k = 0; k < n - 1; k++)
		for (i = n - 1; i > k; i--)
			for (j = n; j >= 0; j--)
				if (tablica[k][k] != 0)
					tablica[i][j] = tablica[i][j] - (tablica[k][j] * tablica[i][k]) / (tablica[k][k]);

	/*cout << "\n\n Macierz po eliminacji Gaussa:";
	for (i = 0; i < n; i++)
	{
		cout << "\n";
		for (j = 0; j < n + 1; j++)
			cout << tablica[i][j] << "\t";
	}*/
}

void zeruj(int n, double **tablica)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n + 1; j++)
			if (fabs(tablica[i][j]) < EPS) tablica[i][j] = 0;
	}

	/*cout << "\n Macierz WYZEROWANA :";
		for (i = 0; i < n; i++)
		{
			cout << endl;
			for (j = 0; j < n + 1; j++)
				cout << tablica[i][j] << "\t";
		}
*/
	cout << "\n \n";
}

void oblicz_rank(int n, double **tablica, int *rankA, int *rankU)
{
	int i, j = 0;;
	int licznik_pom1 = 0;
	int licznik_pom2 = 0;

	for (i = 0; i < n; i++)
	{
		j = 0;
		while ((tablica[i][j] == 0) && (j < n))
		{
			j++;
		}
		if (j == n) licznik_pom1++;
	}

	for (i = 0; i < n; i++)
	{
		j = 0;
		while ((tablica[i][j] == 0) && (j <= n))
		{
			j++;
		}

		if (j == n + 1) licznik_pom2++;
	}
	*rankA = n - licznik_pom1;
	*rankU = n - licznik_pom2;
}

void licz(int n, double **tablica, int *rankA, int *rankU)
{
	if ((*rankA == *rankU) && (*rankA >= n))
	{
		int i, j, k;
		double l;
		double *x = new double[n];

		//ZAMIANA
		x[n - 1] = tablica[n - 1][n] / tablica[n - 1][n - 1];
		for (k = n - 2; k >= 0; --k)
		{
			l = 0;
			for (j = n - 1; j > k; --j)
			{
				l += tablica[k][j] * x[j];
			}

			x[k] = (tablica[k][n] - l) / tablica[k][k];
		}

		//rozwiazania
		cout << "\n\nRozwiazaniami rownania sa :" << endl;
		for (i = 0; i < n; i++)
			cout << "x[" << i + 1 << "]=" << x[i] << endl;
	}

	else if ((*rankA == *rankU) && (*rankA < n)) cout << "UKLAD NIEOZNACZONY";
	else if (*rankA != *rankU) cout << "UKLAD SPRZECZNY";
}