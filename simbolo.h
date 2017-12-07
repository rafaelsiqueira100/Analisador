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
    Simbolo& operator=(const Simbolo& outro);
    string getNome() const;
    int    getNivel() const;
   // TipoSimbolo getTipo();
    TipoRetorno getTipoRetorno() const;
};

#endif // SIMBOLO_H_INCLUDED
