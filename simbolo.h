#ifndef SIMBOLO_H_INCLUDED
#define SIMBOLO_H_INCLUDED

#include <string>

using namespace std;

typedef enum {
    SimboloInteiro,
    SimboloLogico,
    SimboloVacuo
} TipoRetorno;
typedef enum{
    TipoVariavel,
    TipoMetodo
}TipoSimbolo;
class Simbolo
{
  private:
    string nome;
    int nivel;
    Simbolo* parametros;
    int quantosParametros;
    //TipoSimbolo tipo;
    TipoRetorno tipoRetorno;
    TipoSimbolo tipoSimbolo;
  public:
    Simbolo(string, int, Simbolo*, int, TipoRetorno)throw();
    Simbolo(string, int, TipoRetorno);
    Simbolo();
    Simbolo(const Simbolo&)throw();
    void operator=(const Simbolo&) throw();
    ~Simbolo();
    string getNome() const;
    int getNivel() const;
    Simbolo getParametro(int);
	int getQuantosParametros();
	TipoSimbolo getTipoSimbolo() const;
    // TipoSimbolo getTipo();
    //virtual bool getTipo();
    TipoRetorno getTipoRetorno() const;
};

#endif // SIMBOLO_H_INCLUDED
