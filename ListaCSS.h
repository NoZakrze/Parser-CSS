#pragma once
#include <iostream>
#include "Wezel.h"
#define SELEKTORY 1
#define ATRYBUTY_W 2
#define ATRYBUTY_N 3
#define CSS 0
#define KOMENDY 1
using namespace std;

class ListaCSS 
{
private:
	Wezel* pierwszy;
	int bloki,zywe_bloki;
	char tmp[BUFFER],tmp2[BUFFER],komenda1[BUFFER], komenda2[BUFFER], komenda;
public:
	ListaCSS()
	{
		pierwszy = 0;
		bloki = zywe_bloki = 0;
	}
	Wezel* GetPierwszy()
	{
		return pierwszy;
	}
	~ListaCSS()
	{
		Wezel* obecny = pierwszy;
		Wezel* kolejny = nullptr;
		while (obecny != nullptr)
		{
			kolejny = obecny->nastepny;
			delete obecny;
			obecny = kolejny;
		}
	}
	void DodajWezel();
	void UsunWezel(int a);
	void ParserCSS();
	void NowySelektor(char* t, int i,int rozmiar);
	void NowyAtrybut(char* t, char* t2, int n, int rozmiar, int rozmiar2);
	int StringNaInt(char* t);
	bool CzyInt(char* t);
	void WykonajKomende(char* t1, char t, char* t2);
	
};