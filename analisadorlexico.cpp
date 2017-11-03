#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include "analisadorlexico.h"

static const string palavras_chave[] = {"prog", "var", "begin", "end", "=", "+", "-", "*", "/", "not", ">", "<", ">=", "<=", "if", "else"};

const string* AnalisadorLexico::palavrasChave = palavras_chave;

AnalisadorLexico::AnalisadorLexico(string nomeArquivo)
{
    this->arquivo.open(nomeArquivo.c_str());
}

AnalisadorLexico::~AnalisadorLexico()
{
    this->arquivo.close();
}

bool AnalisadorLexico::armazenarValor(string palavraLida)
{
    int i;
    bool ehNumero = true;

    if (isalpha(palavraLida.at(0)))
    {
        this->valorLiteral = palavraLida;

        return true;
    }

    for (i = 0; i < palavraLida.size(); i++)
        if (!isdigit(palavraLida.at(i)))
            ehNumero = false;

    if (ehNumero)
    {
        this->valorNumerico = atoi(palavraLida.c_str());

        return true;
    }

    return false;
}

bool AnalisadorLexico::fimDaPalavra()
{
    return true;
}

string AnalisadorLexico::proximaPalavra()
{
    string* retorno;

    char palavraEmVetor[1024];
    char letra;
    int tamanhoPalavra = 0;

    while (this->fimDaPalavra())
        palavraEmVetor[tamanhoPalavra++] = this->arquivo.get();

    retorno = new string(palavraEmVetor, tamanhoPalavra);

    this->armazenarValor(*retorno);

    return *retorno;
}

string AnalisadorLexico::paraMinusculas(string palavra)
{
    string emMinusculas (palavra);
    int i;

    for (i = 0; i < palavra.size(); i++)
        emMinusculas[i] = tolower(palavra[i]);

    return emMinusculas;
}

TipoPedaco AnalisadorLexico::proximoPedaco()
{
    string pedaco (AnalisadorLexico::paraMinusculas(this->proximaPalavra()));

    int i;

    for (i = 0; i < NUM_PALAVRAS_CHAVE; i++)
        if (pedaco == AnalisadorLexico::palavrasChave[i])
            return TipoPedaco(i);
}

char AnalisadorLexico::temMaisPedacos()
{
    return this->arquivo.eof();
}

string AnalisadorLexico::getLiteral()
{
    return this->valorLiteral;
}

int AnalisadorLexico::getNumero()
{
    return this->valorNumerico;
}
