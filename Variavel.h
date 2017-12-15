#ifndef VARIAVEL_H
#define VARIAVEL_H
#include "simbolo.h"
//#include "stdafx.h"
using namespace std;
class Var : public Simbolo
{
public:
     Var(string, int, TipoRetorno)throw();
     Var();
};

#endif // VARIAVEL_H
