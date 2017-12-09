#ifndef VARIAVEL_H
#define VARIAVEL_H
#include "simbolo.h"
using namespace std;
class Variavel : public Simbolo
{
public:
     Variavel(string, int, TipoRetorno)throw();
     Variavel();

};

#endif // VARIAVEL_H
