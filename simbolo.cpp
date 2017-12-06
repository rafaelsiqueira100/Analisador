#include "simbolo.h"

#include "tiposimbolo.h"

Simbolo::Simbolo(string nome, int nivel, TipoRetorno tipoRetorno):
    this->nome(nome),this->nivel(nivel),this->tipoRetorno(tipoRetorno)
{
}

Simbolo::Simbolo():
    this->nome(""),this->nivel(0),this->tipoRetorno(SimboloVacuo)
{
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

/*TipoSimbolo Simbolo::getTipo()
{
    return this->tipo;
}*/

TipoRetorno Simbolo::getTipoRetorno(){
    return this->tipoRetorno;
}
