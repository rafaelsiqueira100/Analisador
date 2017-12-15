#include "Variavel.h"
#include "simbolo.h"
//#include "stdafx.h"
Var::Var(string nome, int nivel, TipoRetorno tipoRetorno) throw()
    : Simbolo(nome, nivel, tipoRetorno)
{
    //ctor
}

Var::Var():Simbolo()
{
}

