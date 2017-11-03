#ifndef ANALISADORLEXICO_H_INCLUDED
#define ANALISADORLEXICO_H_INCLUDED

#include "tipopedaco.h"

#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

#define NUM_PALAVRAS_CHAVE 30

class AnalisadorLexico
{
private:
    static const string* palavrasChave;

    bool   armazenarValor(string);
    string proximaPalavra();

    string valorLiteral;
    int    valorNumerico;

    ifstream arquivo;
public:
    AnalisadorLexico(string);
    ~AnalisadorLexico();

    TipoPedaco proximoPedaco();
    char       temMaisPedacos();
    string     getLiteral();
    int        getNumero();
};

#endif // ANALISADORLEXICO_H_INCLUDED
