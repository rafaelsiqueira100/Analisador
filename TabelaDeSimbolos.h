#ifndef TABELADESIMBOLOS_H_INCLUDED
#define TABELADESIMBOLOS_H_INCLUDED
#include "simbolo.h"
#include <list>
using namespace std;
class TabelaDeSimbolos{
private:
	list<Simbolo*> armazenador;
public:
    TabelaDeSimbolos();
	void guarde(Simbolo*);
	void eliminaNivel(int);
};
#endif
