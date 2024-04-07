#pragma once
#include <iostream>
#include "Atrybut.h"
#include "Selektor.h"
using namespace std;

class Sekcja
{
	friend class Wezel;
	friend class ListaCSS;
private:
	Atrybut* pierwszy_A;
	Selektor* pierwszy_S;
	int licznik_A, licznik_S;
public:
	Sekcja()
	{
		pierwszy_A = 0;
		pierwszy_S = 0;
		licznik_A = licznik_S = 0;
	}
	~Sekcja()
	{
		Usun_Wszystkie_Atrybuty();
		Usun_Wszystkie_Selektory();
	}
	void Dodaj_Atrybut(char* nazwa,char* wartosc,int rozmiar,int rozmiar2);
	void Dodaj_Selektor(char* nazwa, int rozmiar);
	bool Porownaj_napis(char* t, char* t2);
	void Usun_Wszystkie_Atrybuty();
	void Usun_Wszystkie_Selektory();
	void Usun_Atrybut(int i,char* nazwa);
	void Wypisz_Selektor(int i, int j);
	void Wypisz_Atrybut(int i, char* nazwa);
	bool Istnieje_Selektor(char* nazwa);
	bool Istnieje_Atrybut(char* nazwa);
	void Wartosc_Atrybutu(char* nazwa,char* nazwa_S);
};