#include "metodo.h"
#include "simbolo.h"
//#include "stdafx.h"
Metodo::Metodo(string nome, int nivel, Simbolo *parametros, int quantosParametros, TipoRetorno tipoRetorno) throw()
    : Simbolo(nome, nivel, tipoRetorno)
{
    this->parametros = parametros;
    this->quantosParametros = quantosParametros;
}

Metodo::~Metodo() {}

Simbolo Metodo::getParametro(int indice)
{
    return *(parametros + indice);
}
int Metodo::getQuantosParametros()
{
    return this->quantosParametros;
}
