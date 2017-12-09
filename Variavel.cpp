#include "Variavel.h"
#include "simbolo.h"
Var::Var(string nome, int nivel, TipoRetorno tipoRetorno) throw()
    : Simbolo(nome, nivel, tipoRetorno)
{
    //ctor
}

Var::Var():Simbolo()
{
}

