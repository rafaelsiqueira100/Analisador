#include "simbolo.h"



Simbolo::Simbolo(string nome, int nivel, TipoRetorno tipoRetorno):
    nome(nome),nivel(nivel),tipoRetorno(tipoRetorno)
{
}

Simbolo::Simbolo():
    nome(""),nivel(0),tipoRetorno(SimboloVacuo)
{
}
Simbolo& Simbolo::operator=(const Simbolo& outro){
this->nome = outro.getNome();
this->nivel = outro.getNivel();
this->tipoRetorno = outro.getTipoRetorno();
return *this;
}

Simbolo::~Simbolo()
{
    this->nome  = "";
    this->nivel = 0;
}

string Simbolo::getNome() const
{
    return this->nome;
}

int Simbolo::getNivel() const
{
    return this->nivel;
}

/*TipoSimbolo Simbolo::getTipo()
{
    return this->tipo;
}*/

TipoRetorno Simbolo::getTipoRetorno() const{
    return this->tipoRetorno;
}
