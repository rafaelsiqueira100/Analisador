#include "Variavel.h"
#include "simbolo.h"
Variavel::Variavel(string nome, int nivel, TipoRetorno tipoRetorno) throw()
    : Simbolo(nome, nivel, tipoRetorno)
{
    //ctor
}

Variavel::Variavel():Simbolo()
{
}

