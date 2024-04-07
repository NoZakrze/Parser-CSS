#pragma once
#include <iostream>
using namespace std;

class Selektor
{
	friend class Sekcja;
private:
	char* nazwa;
	Selektor* poprzedni;
	Selektor* nastepny;
public:
	Selektor()
	{
		poprzedni = 0;
		nastepny = 0;
		nazwa = nullptr;
	}
	~Selektor()
	{
		delete[] nazwa;
	}
};