#include "metodo.h"
#include "simbolo.h"
#include "tiposimbolo.h"

Metodo::Metodo(string nome, int nivel, Simbolo* parametros, int quantosParametros) : Simbolo(nome, nivel, Vacuo)
{
    this->parametros        = parametros;
    this->quantosParametros = quantosParametros;
}

Metodo::~Metodo() { }


