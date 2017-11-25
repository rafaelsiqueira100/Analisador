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
    int     lengthUltimaLeitura;
    bool   armazenarValor(string);

    bool   fimDaPalavra(char* , int );
    string proximaPalavra();

    static string paraMinusculas(string);
    bool valorNumeroValido;
    string valorLiteral;
    int    valorNumerico;
    bool doisCharLidos ;
    ifstream* arquivo;
public:
     AnalisadorLexico(string);
    ~AnalisadorLexico();
    static string nomeTipo(TipoPedaco);
    int getLengthUltimoPedaco();
     /*
        TipoPedaco proximoPedaco()

        retorna o TipoPedaco da palavra chave,
        TipoPedaco.Desconhecido se não encontrado
        TipoPedaco.Numero se é valor numerico
        TipoPedaco.Identificador se é alfanumérico e não é palavra chave
     */
    TipoPedaco proximoPedaco();
    TipoPedaco verPedaco();

    char       temMaisPedacos();

    /*
        TipoPedaco getLiteral()

        retorna o valor literal caso seja do tipo
        Identificador ou uma palavra chave
     */
    string     getLiteral();
    int        getNumero();
};

#endif // ANALISADORLEXICO_H_INCLUDED
