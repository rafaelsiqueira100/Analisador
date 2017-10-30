#ifndef ANALISADORLEXICO_H_INCLUDED
#define ANALISADORLEXICO_H_INCLUDED

#include "tipopedaco.h"

class AnalisadorLexico
{
private:
    char* proximaPalavra();

    char* valorLiteral;
    int   valorNumerico;
public:
    public AnalisadorLexico(char*);

    TipoPedaco proximoPedaco();
    char       temMaisPedacos();
    char*      getLiteral();
    int        getNumero();
};

#endif // ANALISADORLEXICO_H_INCLUDED
