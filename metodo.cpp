#include "metodo.h"
#include "simbolo.h"
#include "tiposimbolo.h"

Metodo::Metodo(string nome, int nivel, Simbolo* parametros, int quantosParametros, TipoSimbolo tipo) : Simbolo(nome, nivel, tipo)
{
    this->parametros        = parametros;
    this->quantosParametros = quantosParametros;
}

Metodo::~Metodo() { }


