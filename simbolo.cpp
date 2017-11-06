#include "simbolo.h"

#include "tiposimbolo.h"

Simbolo::Simbolo(string nome, int nivel, TipoSimbolo tipo)
{
    this->nome  = nome;
    this->nivel = nivel;
    this->tipo  = tipo;
}

Simbolo::~Simbolo()
{
    this->nome  = "";
    this->nivel = 0;
}

string Simbolo::getNome()
{
    return this->nome;
}

int Simbolo::getNivel()
{
    return this->nivel;
}

TipoSimbolo Simbolo::getTipo()
{
    return this->tipo;
}
