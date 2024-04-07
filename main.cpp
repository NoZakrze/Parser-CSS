#include <iostream>
#include "ListaCSS.h"
using namespace std;
int main()
{
	ListaCSS* lista = new ListaCSS;
	lista->ParserCSS();
	delete lista;

	return 0;
}