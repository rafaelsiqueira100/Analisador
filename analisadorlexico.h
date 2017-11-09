#ifndef ANALISADORLEXICO_H_INCLUDED
#define ANALISADORLEXICO_H_INCLUDED
#include "tipopedaco.h"
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

#define NUM_PALAVRAS_CHAVE 35

class AnalisadorLexico
{
private:
    static const string* palavrasChave;

    bool   armazenarValor(string);

    bool   fimDaPalavra(char* , int );
    string proximaPalavra();

    static string paraMinusculas(string);

    string valorLiteral;
    int    valorNumerico;
    bool doisCharLidos ;
    ifstream* arquivo;
public:
     AnalisadorLexico(string);
    ~AnalisadorLexico();

    TipoPedaco proximoPedaco();
    char       temMaisPedacos();
    string     getLiteral();
    int        getNumero();
};

#endif // ANALISADORLEXICO_H_INCLUDED
