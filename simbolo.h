#ifndef SIMBOLO_H_INCLUDED
#define SIMBOLO_H_INCLUDED

#include <string>

using namespace std;
typedef enum
{
    SimboloInteiro,
    SimboloLogico,
    SimboloVacuo
} TipoRetorno;
class Simbolo
{
private:
   string nome;
   int    nivel;
   //TipoSimbolo tipo;
   TipoRetorno tipoRetorno;
public:
     Simbolo(string, int,  TipoRetorno);
     Simbolo();
    ~Simbolo();

    string getNome();
    int    getNivel();
   // TipoSimbolo getTipo();
    TipoRetorno getTipoRetorno();
};

#endif // SIMBOLO_H_INCLUDED
