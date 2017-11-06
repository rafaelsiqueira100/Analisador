#ifndef SIMBOLO_H_INCLUDED
#define SIMBOLO_H_INCLUDED

#include <string>
#include "tiposimbolo.h"

using namespace std;

class Simbolo
{
private:
    string nome;
    int    nivel;
    TipoSimbolo tipo;
public:
     Simbolo(string, int, TipoSimbolo);
    ~Simbolo();

    string getNome();
    int    getNivel();
    TipoSimbolo getTipo();
};

#endif // SIMBOLO_H_INCLUDED
