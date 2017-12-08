#include "Variavel.h"

Variavel::Variavel(string nome, int nivel, TipoRetorno tipoRetorno) throw()
    : Simbolo(nome, nivel, tipoRetorno)
{
    //ctor
}

Variavel::Variavel():Simbolo()
{
}

Variavel::~Variavel()
{
    //dtor
}
