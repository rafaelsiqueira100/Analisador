#ifndef SIMBOLO_H_INCLUDED
#define SIMBOLO_H_INCLUDED

#include <string>
#include "tiposimbolo.h"
#include "TipoRetorno.h"
using namespace std;

class Simbolo
{
private:
   string nome;
   int    nivel;
   //TipoSimbolo tipo;
   TipoRetorno tipoRetorno;
public:
     Simbolo(string, int,  TipoRetorno);
    ~Simbolo();

    string getNome();
    int    getNivel();
   // TipoSimbolo getTipo();
    TipoRetorno getTipoRetorno();
};

#endif // SIMBOLO_H_INCLUDED
