#include "simbolo.h"



Simbolo::Simbolo(string nome, int nivel, TipoRetorno tipoRetorno):
    nome(nome),nivel(nivel),tipoRetorno(tipoRetorno)
{
}

Simbolo::Simbolo():
    nome(""),nivel(0),tipoRetorno(SimboloVacuo)
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
