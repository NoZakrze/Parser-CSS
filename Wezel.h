#pragma once
#include <iostream>
#include "Sekcja.h"
using namespace std;
#define T 8

class Wezel
{
	friend class ListaCSS;
private:
	Sekcja** tab = new Sekcja*[T];
	bool zajete[T];
	Wezel* poprzedni;
	Wezel* nastepny;
	int licznik, licznik_zajetych;
public:
	Wezel()
	{
		poprzedni = 0;
		nastepny = 0;
		licznik = licznik_zajetych = 0;
		for (int i = 0; i < T; i++)
		{
			zajete[i] = false;
			tab[i] = new Sekcja;
		}
	}
	~Wezel()
	{
		for (int i = 0; i < T; i++)
		{
			if (zajete[i] == 1)
				delete tab[i];
		}
		delete[] tab;
	}
};