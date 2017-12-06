#ifndef METODO_H_INCLUDED
#define METODO_H_INCLUDED

#include "simbolo.h"

class Metodo : public Simbolo
{
private:
    Simbolo* parametros;
    //colocar depois ponteiro para método pai
    int quantosParametros;
public:
     Metodo(string, int, Simbolo*, int, TipoRetorno)throw();
    ~Metodo();

    Simbolo getParametro(int);
	int getQuantosParametros();
};

#endif // METODO_H_INCLUDED
