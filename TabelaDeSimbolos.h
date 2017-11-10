#ifndef TABELADESIMBOLOS_H_INCLUDED
#define TABELADESIMBOLOS_H_INCLUDED
#include "simbolo.h"
using namespace std;
class TabelaDeSimbolos{
private:
	List<Simbolo*> armazenador;
public:
	void guarde(Simbolo);
	void eliminaNivel(int);
};