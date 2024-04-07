#pragma once
#include <iostream>
#define BUFFER 128
using namespace std;

class Atrybut
{
	friend class Sekcja;
private:
	char* nazwa;
	char* wartosc;
	Atrybut* poprzedni;
	Atrybut* nastepny;
public:
	Atrybut()
	{
		poprzedni = 0;
		nastepny = 0;
		nazwa = new char[BUFFER];
		wartosc = new char[BUFFER];
	}
	~Atrybut()
	{
		delete[] nazwa;
		delete[] wartosc;
	}
};