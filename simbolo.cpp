#include "simbolo.h"
//#include "stdafx.h"
Simbolo::Simbolo(std::string nome, int nivel, TipoRetorno tipoRetorno) : nome(nome), nivel(nivel), tipoRetorno(tipoRetorno), tipoSimbolo(TipoVariavel),
quantosParametros(0), parametros(nullptr)
{
}
Simbolo::Simbolo(string nome, int nivel, Simbolo *parametros, int quantosParametros, TipoRetorno tipoRetorno) throw()
    : nome(nome), nivel(nivel), tipoRetorno(tipoRetorno)
{
     this->tipoSimbolo = TipoMetodo;
     this->quantosParametros = quantosParametros;
     this->parametros = parametros;
}

Simbolo::Simbolo() : nome(""), nivel(0), tipoRetorno(SimboloVacuo), tipoSimbolo(TipoVariavel), parametros(nullptr), quantosParametros(0)
{
}

Simbolo::~Simbolo()
{
}
Simbolo::Simbolo(const Simbolo& simbolo)throw() : nome(simbolo.nome), nivel(simbolo.nivel), tipoRetorno(simbolo.tipoRetorno), tipoSimbolo(simbolo.tipoSimbolo),
quantosParametros(simbolo.quantosParametros), parametros(new Simbolo[simbolo.quantosParametros]){
    for(int i=0;i<simbolo.quantosParametros;i++)
        *(parametros+i) = *(simbolo.parametros+i);

}
void Simbolo::operator=(const Simbolo& outro) throw(){
    delete[] this->parametros;
    this->nivel = outro.nivel;
    this->nome = outro.nome;
    this->quantosParametros= outro.quantosParametros;
    this->tipoRetorno = outro.tipoRetorno;
    this->tipoSimbolo = outro.tipoSimbolo;
    this->parametros = new Simbolo [this->quantosParametros];
    for(int i=0;i<quantosParametros;i++)
        *(this->parametros+i) = *(outro.parametros+i);
    //return (Simbolo)(*this);
}
Simbolo Simbolo::getParametro(int indice)
{
    return *(parametros + indice);
}
int Simbolo::getQuantosParametros()
{
    return this->quantosParametros;
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

TipoRetorno Simbolo::getTipoRetorno() const
{
    return this->tipoRetorno;
}
TipoSimbolo Simbolo::getTipoSimbolo() const
{
    return this->tipoSimbolo;
}
