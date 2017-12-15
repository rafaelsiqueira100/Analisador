#ifndef ANALISADORLEXICO_H_INCLUDED
#define ANALISADORLEXICO_H_INCLUDED
#include "tipopedaco.h"
#include <string.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include <list>
using namespace std;
//#include "stdafx.h"
#define NUM_PALAVRAS_CHAVE 40
//Esta classe não possui operator=, construtor de cópia e destrutor
//porque não possui atributos ponteiros dinamicamente alocados,
//logo não há problema realizar uma cópia binária disparada quando
//não há operator= e construtor de cópia, e a ausência de destrutor
//não implica um perigo(desalocação automática quando se acaba o escopo)
class AnalisadorLexico
{
  private:
    static const string *palavrasChave;
    string* vetorPalavras;
    TipoPedaco* vetorPedacos;
    int* vetorLinhas;
    bool armazenarValor(string);
    bool fimDaPalavra(char *, int);
    string proximaPalavra();
    static string paraMinusculas(string);
    string valorLiteral;
    bool doisCharLidos;
    ifstream arquivo;
    int indiceAtual;
    int tamanhoVetor;
    int linhaAtual;
    TipoPedaco consuma();
    bool acabouLeitura();
    bool consumiu;
  public:
    AnalisadorLexico(string);
    ~AnalisadorLexico();
    static string nomeTipo(TipoPedaco);
    TipoPedaco proximoPedaco();
    TipoPedaco verPedaco();
    bool temMaisPedacos();
    string getLiteral();
    int getLinhaAtual();
};

#endif // ANALISADORLEXICO_H_INCLUDED
