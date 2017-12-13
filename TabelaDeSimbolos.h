#ifndef TABELADESIMBOLOS_H_INCLUDED
#define TABELADESIMBOLOS_H_INCLUDED
#include "simbolo.h"
#include "metodo.h"
#include <list>
#include <string.h>
using namespace std;



class TabelaDeSimbolos{
private:
	list<Simbolo*> armazenador;
public:
    TabelaDeSimbolos();
	void guarde(Simbolo*);
	void guardeMetodo(Metodo*);
	bool encontrar(string, Simbolo*);
	void eliminaNivel(int);
};
#endif
