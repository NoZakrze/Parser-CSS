#include <iostream>
#include "ListaCSS.h"
using namespace std;

void ListaCSS::DodajWezel()
{
	Wezel* nowy = new Wezel;

	if (pierwszy == 0)
	{
		pierwszy = nowy;
	}
	else
	{
		Wezel* tmp = pierwszy;
		while (tmp->nastepny)
		{
			tmp = tmp->nastepny;
		}
		tmp->nastepny = nowy;
		nowy->poprzedni = tmp;
	}
}
void ListaCSS::UsunWezel(int a)
{
	if (a == 1)
	{
		Wezel* tmp = pierwszy;
		if (tmp->nastepny == NULL)
		{
			pierwszy = NULL;
			delete tmp;
		}
		else
		{
			pierwszy = tmp->nastepny;
			pierwszy->poprzedni = 0;
			delete tmp;
		}
	}
	else if (a >= 2)
	{
		int index = 1;
		Wezel* tmp = pierwszy;
		while (tmp)
		{
			if ((index + 1) == a)
				break;
			index++;
			tmp = tmp->nastepny;
		}
		if (tmp->nastepny->nastepny == NULL)
		{
			delete tmp->nastepny;
			tmp->nastepny = 0;
		}
		else
		{
			Wezel* usuwany = tmp->nastepny;
			tmp->nastepny = usuwany->nastepny;
			usuwany->nastepny->poprzedni = tmp;
			delete usuwany;
		}
	}
	if (bloki >= T)
		bloki = bloki - T;
	else
		bloki = 0;
}
void ListaCSS::ParserCSS()
{
	char s;
	tmp[0] = '\0';
	tmp2[0] = '\0';
	int i = 0,j=0;
	int flaga = SELEKTORY, wczytywanie = CSS;
	while (cin.get(s))
	{
		if (wczytywanie == CSS)
		{
			if (s >= 'a' && s <= 'z')
			{
				if (flaga != ATRYBUTY_N)
				{
					tmp[i] = s;
					i++;
				}
				else
				{
					tmp2[j] = s;
					j++;
				}
			}
			else if (s == ' ')
			{
				if (flaga != ATRYBUTY_N)
				{
					if (i == 0)
						continue;
					else
					{
						tmp[i] = s;
						i++;
					}
				}
				else
				{
					if (j == 0)
						continue;
					else
					{
						tmp2[j] = s;
						j++;
					}
				}
			}
			else if (s == '\n')
			{
				continue;
			}
			else if (s == '{')
			{
				if (i != 0)
				{
					tmp[i] = '\0';
					NowySelektor(tmp, bloki,i);
					i = 0;
				}
				flaga = ATRYBUTY_N;
			}
			else if (s == ':' && flaga!=SELEKTORY)
			{
				if (j != 0)
				{
					tmp2[j] = '\0';
				}
				flaga = ATRYBUTY_W;
			}
			else if (s == ';')
			{
				if (i != 0)
				{
					tmp[i] = '\0';
					NowyAtrybut(tmp2, tmp, bloki,j,i);
					i = 0;
					j = 0;
				}
				flaga = ATRYBUTY_N;
			}
			else if (s == ',' && flaga == SELEKTORY)
			{
				if (i != 0)
				{
					tmp[i] = '\0';
					NowySelektor(tmp, bloki,i);
					i = 0;
				}
			}
			else if (s == '}')
			{
				if (i != 0)
				{
					tmp[i] = '\0';
					NowyAtrybut(tmp2, tmp, bloki,j,i);
					i = 0;
					j = 0;
				}
				flaga = SELEKTORY;
				bloki++;
				zywe_bloki++;
			}
			else if (s < ' ')
			{
				continue;
			}
			else if (flaga != ATRYBUTY_N)
			{
				tmp[i] = s;
				i++;
			}
			else
			{
				tmp2[j] = s;
				j++;
			}
			if (tmp[0] == '?' && tmp[1] == '?' && tmp[2] == '?' && tmp[3] == '?')
			{
				wczytywanie = KOMENDY;
				i = 0;
				tmp[0] = '/0';
			}
		}
		else if(wczytywanie == KOMENDY)
		{
			if (s != '\n' && s!='\r' && s!=EOF)
			{
				tmp[i] = s;
				i++;
			    if (s == '?' && i == 1)
			    {
					cout << "? == " << zywe_bloki << endl;
					i = 0;
			    }
			}
			else if (s == '\n' && i == 0)
				continue;
			else
			{
				tmp[i] = '\0';
				i = 0;
				if (tmp[0] == '*')
				{
					wczytywanie = CSS;
					i = 0;
				}
				else 
				{
					while (tmp[i] != ',')
					{
						komenda1[i] = tmp[i];
						i++;
					}
					komenda1[i] = '\0';
					i++;
					komenda = tmp[i];
					i += 2;
					int j = 0;
					while (tmp[i] != '\0')
					{
						komenda2[j] = tmp[i];
						i++;
						j++;
					}
					komenda2[j] = '\0';
					WykonajKomende(komenda1, komenda, komenda2);
					i = 0;
				}
			}
		}
	}
}
void ListaCSS::NowySelektor(char* t, int n,int rozmiar)
{
	int wezel, blok;
	wezel = n / T;
	blok = (n % T);
	int licznik = 0;
	Wezel* temp = pierwszy;
	if (temp == NULL)
	{
		DodajWezel();
		temp = pierwszy;
	}
	else
	{
		bool koniec = 1;
		while (koniec)
		{
			if (temp->nastepny)
			{
				temp = temp->nastepny;
			}
			else
				koniec = 0;
			licznik++;
		}
		if (licznik < wezel + 1)
		{
			DodajWezel();
			temp = pierwszy;
			koniec = 1;
			while (koniec)
			{
				if (temp->nastepny)
				{
					temp = temp->nastepny;
				}
				else
					koniec = 0;
			}
		}
	}
	temp->tab[blok]->Dodaj_Selektor(t,rozmiar);	
}
void ListaCSS::NowyAtrybut(char* t, char* t2, int n,int rozmiar,int rozmiar2)
{
	int wezel, blok;
	wezel = n / T;
	blok = (n % T);
	int licznik = 0;
	Wezel* temp = pierwszy;
	if (temp == NULL)
	{
		DodajWezel();
		temp = pierwszy;
	}
	else
	{
		bool koniec = 1;
		while (koniec)
		{
			if (temp->nastepny)
			{
				temp = temp->nastepny;
			}
			else
				koniec = 0;
			licznik++;
		}
		if (licznik < wezel + 1)
		{
			DodajWezel();
			temp = pierwszy;
			koniec = 1;
			while (koniec)
			{
				if (temp->nastepny)
				{
					temp = temp->nastepny;
				}
				else
					koniec = 0;
			}
		}
	}
	temp->tab[blok]->Dodaj_Atrybut(t,t2,rozmiar,rozmiar2);
	temp->zajete[blok] = 1;
}
int ListaCSS::StringNaInt(char* t)
{
	int wynik = 0,i=0;
	while (t[i] != '\0')
	{
		int tmp = t[i] - 48;
		wynik = wynik * 10 + tmp;
		i++;
	}
	return wynik;
}
bool ListaCSS::CzyInt(char* t)
{
	int i = 0;
	while (t[i] != '\0')
	{
		if (t[i] < '0' || t[i]>'9')
			return false;
		i++;
	}
	return true;
}
void ListaCSS::WykonajKomende(char* t1, char t, char* t2)
{
	if (CzyInt(t1) == true)
	{
		int numer_S = StringNaInt(t1);
		if (numer_S <= zywe_bloki)
		{
			Wezel* temp = pierwszy;
			int licz_wezly = 1;
			int g = numer_S, licznik = 0, indeks=0;
			while (temp)
			{
				for (int i = 0; i < T; i++)
				{
					indeks = i;
					if (temp->zajete[i] == 1)
						licznik++;
					if (licznik == numer_S)
						break;
				}
				if (licznik == numer_S)
					break;
				temp = temp->nastepny;
				licz_wezly++;
			}
			if (t == 'S' && t2[0] == '?')
			{
				cout << t1 << "," << "S" << "," << "?" << " == " << temp->tab[indeks]->licznik_S << endl;
			}
			else if (t == 'A' && t2[0] == '?')
			{
				cout << t1 << "," << "A" << "," << "?" << " == " << temp->tab[indeks]->licznik_A << endl;
			}
			else if (t == 'S')
			{
				int j = StringNaInt(t2);
				temp->tab[indeks]->Wypisz_Selektor(numer_S, j);
			}
			else if (t == 'A')
			{
				temp->tab[indeks]->Wypisz_Atrybut(numer_S, t2);
			}
			else if (t == 'D')
			{
				bool usun_sekcje = 1, usun_atrybut = 0;
				if (t2[0] != '*')
				{
					usun_atrybut = 1;
					temp->tab[indeks]->Usun_Atrybut(numer_S,t2);
					if (temp->tab[indeks]->licznik_A > 0)
						usun_sekcje = 0;
				}
				if (usun_sekcje == 1)
				{
					Sekcja* usuwana = temp->tab[indeks];
					delete usuwana;
					temp->zajete[indeks] = 0;
					zywe_bloki--;
					bool usun_wezel = 1;
					for (int i = 0; i < T; i++)
					{
						if (temp->zajete[i] == 1)
							usun_wezel = 0;
					}
					if (usun_wezel == 1)
					{
						UsunWezel(licz_wezly);
					}
					if(usun_atrybut==0)
						cout <<t1<<","<<t<<","<<t2<<" == "<<"deleted"<< endl;
				}
			}
		}
	}
	else if (t == 'A')
	{
		int wynik = 0;
		Wezel* temp = pierwszy;
		int g = bloki;
		while (temp)
		{
			for (int i = 0; i < T && i < g; i++)
			{
				if (temp->zajete[i] == 1 && temp->tab[i]->Istnieje_Atrybut(t1) == true)
					wynik++;
			}
			g = g - T;
			temp = temp->nastepny;
		}
		cout << t1 << ",A,? == " << wynik << endl;
	}
	else if (t == 'S')
	{
		int wynik = 0;
		Wezel* temp = pierwszy;
		int g = bloki;
		while (temp)
		{
			for (int i = 0; i < T && i < g; i++)
			{
				if (temp->zajete[i] == 1 && temp->tab[i]->Istnieje_Selektor(t1) == true)
					wynik++;
			}
			g = g - T;
			temp = temp->nastepny;
		}
		cout << t1 << ",S,? == " << wynik << endl;
	}
	else if (t == 'E')
	{
		Wezel* tmp = pierwszy;
		while (tmp->nastepny)
		{
			tmp = tmp->nastepny;
		}
		bool flaga = 0;
		while (tmp && flaga==0)
		{
			for (int i = T - 1; i >= 0; i--)
			{
				if (tmp->zajete[i] == 1)
				{
					if (tmp->tab[i]->Istnieje_Selektor(t1) == true)
					{
						if (tmp->tab[i]->Istnieje_Atrybut(t2) == true)
						{
							tmp->tab[i]->Wartosc_Atrybutu(t2, t1);
							flaga = 1;
							break;
						}
					}
				}
			}
			tmp = tmp->poprzedni;
		}
	}
}