#include "metodo.h"
#include "simbolo.h"
#include "tiposimbolo.h"

Metodo::Metodo(string nome, int nivel, Simbolo* parametros, int quantosParametros, TipoSimbolo tipo, TipoRetorno tipoRetorno) : Simbolo(nome, nivel, tipo, tipoRetorno)
{
    this->parametros        = parametros;
    this->quantosParametros = quantosParametros;
}

Metodo::~Metodo() { }


