#include <iostream>
#include "Sekcja.h"
using namespace std;

void Sekcja::Dodaj_Atrybut(char* nazwa, char* wartosc,int rozmiar, int rozmiar2)
{
	char* war;
	war = new char[rozmiar+2];
	int i = 0;
	int k = rozmiar - 1,k1=rozmiar2-1;
	while (nazwa[k] == ' ')
	{
		nazwa[k] = '\0';
		k--;
	}
	while (wartosc[k1] == ' ')
	{
		wartosc[k1] = '\0';
		k1--;
	}
	while (nazwa[i] != '\0')
	{
		war[i] = nazwa[i];
		i++;
	}
	war[i] = '\0';
	char* war2;
	war2 = new char[rozmiar2+2];
	int j = 0;
	while (wartosc[j] != '\0')
	{
		war2[j] = wartosc[j];
		j++;
	}
	war2[j] = '\0';
	Atrybut* nowy = new Atrybut;
	nowy->nazwa = war;
	nowy->wartosc = war2;
	bool flag = 1;
	if (pierwszy_A == 0)
	{
		pierwszy_A = nowy;
		licznik_A++;
	}
	else
	{
		Atrybut* tmp = pierwszy_A;
		while (tmp->nastepny != 0)
		{
			if (Porownaj_napis(tmp->nazwa, nowy->nazwa) == true)
			{
				tmp->wartosc = war2;
				nowy->wartosc = NULL;
				delete nowy;
				flag = 0;
				break;
			}
			tmp = tmp->nastepny;
		}
		if (flag==1 && Porownaj_napis(tmp->nazwa, nowy->nazwa) == true)
		{
			tmp->wartosc = war2;
			nowy->wartosc = NULL;
			delete nowy;
			flag = 0;
		}
		if (flag == 1)
		{
			tmp->nastepny = nowy;
			nowy->poprzedni = tmp;
			licznik_A++;
		}
	}
}
void Sekcja::Dodaj_Selektor(char* nazwa,int rozmiar)
{
	char* war;
	war = new char[rozmiar+2];
	int i = 0;
	int k = rozmiar - 1;
	while (nazwa[k] == ' ')
	{
		nazwa[k] = '\0';
		k--;
	}
	while (nazwa[i] != '\0')
	{
		war[i] = nazwa[i];
		i++;
	}
	war[i] = '\0';
	Selektor* nowy = new Selektor;
	nowy->nazwa = war;
	if (pierwszy_S == NULL)
	{
		pierwszy_S = nowy;
	}
	else
	{
		Selektor *tmp = pierwszy_S;
		while (tmp->nastepny != 0)
		{
			tmp = tmp->nastepny;
		}
		tmp->nastepny = nowy;
		nowy->poprzedni = tmp;
	}
	licznik_S++;
}
bool Sekcja::Porownaj_napis(char* t, char* t2)
{
	int i = 0;
	while (t[i] != '\0' && t2[i] != '\0')
	{
		if (t[i] != t2[i])
			return false;
		i++;
	}
	if (t[i] != '\0' || t2[i] != '\0')
		return false;
	return true;
}
void Sekcja::Usun_Wszystkie_Atrybuty()
{
		Atrybut* obecny = pierwszy_A;
		Atrybut* kolejny = 0;
		while (obecny!= 0)
		{
			kolejny = obecny->nastepny;
			delete obecny;
			obecny = kolejny;
		}
}
void Sekcja::Usun_Wszystkie_Selektory()
{
	Selektor* obecny = pierwszy_S;
	Selektor* kolejny = nullptr;

	while (obecny != nullptr)
	{
		kolejny = obecny->nastepny;
		delete obecny;
		obecny = kolejny;
	}
}
void Sekcja::Usun_Atrybut(int i,char* nazwa)
{
		if (Porownaj_napis(nazwa,pierwszy_A->nazwa)==true)
		{
			Atrybut* tmp = pierwszy_A;
			if (tmp->nastepny == NULL)
			{
				pierwszy_A = NULL;
				delete tmp;
			}
			else
			{
				pierwszy_A = tmp->nastepny;
				pierwszy_A->poprzedni = 0;
				delete tmp;
			}
			licznik_A--;
			cout << i << ",D," << nazwa << " == " << "deleted" << endl;
		}
		else
		{
			Atrybut* tmp = pierwszy_A;
			bool usun = 0;
			while (tmp->nastepny)
			{
				if (Porownaj_napis(nazwa, tmp->nastepny->nazwa) == true)
				{
					usun = 1;
					break;
				}
				tmp = tmp->nastepny;
			}
			if (usun == 1)
			{
				if (tmp->nastepny->nastepny == NULL)
				{
					delete tmp->nastepny;
					tmp->nastepny = 0;
				}
				else
				{
					Atrybut* usuwany = tmp->nastepny;
					tmp->nastepny = usuwany->nastepny;
					usuwany->nastepny->poprzedni = tmp;
					delete usuwany;
				}
				licznik_A--;
				cout <<i<<",D,"<<nazwa<<" == "<<"deleted" << endl;
			}
		}
}
void Sekcja::Wypisz_Selektor(int i, int j)
{
	if (j <= licznik_S)
	{
		Selektor* tmp = pierwszy_S;
		int licz = 1;
		while (tmp && licz < j)
		{
			tmp = tmp->nastepny;
			licz++;
		}
		cout <<i<<","<<"S"<<","<<j<<" == "<< tmp->nazwa << endl;
	}
}
void Sekcja::Wypisz_Atrybut(int i, char* nazwa)
{
	Atrybut* tmp = pierwszy_A;
		while (tmp)
		{
			if (Porownaj_napis(tmp->nazwa, nazwa) == true)
			{
				cout << i << "," << "A" << "," << nazwa << " == " << tmp->wartosc << endl;
				break;
			}
			tmp = tmp->nastepny;
		}
}
bool Sekcja::Istnieje_Atrybut(char* nazwa)
{
	Atrybut* tmp = pierwszy_A;
	while (tmp)
	{
		if (Porownaj_napis(nazwa, tmp->nazwa) == true)
		{
			return true;
		}
		tmp = tmp->nastepny;
	}
	return false;
}
bool Sekcja::Istnieje_Selektor(char* nazwa)
{
	Selektor* tmp = pierwszy_S;
	while (tmp)
	{
		if (Porownaj_napis(nazwa, tmp->nazwa) == true)
		{
			return true;
		}
		tmp = tmp->nastepny;
	}
	return false;
}
void Sekcja::Wartosc_Atrybutu(char* nazwa,char* nazwa_S)
{
	Atrybut* tmp = pierwszy_A;
	while (tmp)
	{
		if (Porownaj_napis(nazwa, tmp->nazwa) == true)
		{
			cout << nazwa_S << ",E," << nazwa << " == " << tmp->wartosc << endl;
		}
		tmp = tmp->nastepny;
	}
}