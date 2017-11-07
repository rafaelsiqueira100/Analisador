#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



#include "analisadorlexico.h"

using namespace std;
static const string palavras_chave[] =
{"program",
"var",
"begin",
"end",
":=",//4
"=",
"+",
"-",
"*",
"/",
"not",//10
">",
"<",
"<>",
">=",
"<=",
"if",
"while",
"else"//18
"(",//19
")",//20
"try", //21
"except",//22
",",//23
";",
".",//25
":",//26
"Integer",//27
"Boolean",
"true",
"false",
"procedure",
"function"
};

const string* AnalisadorLexico::palavrasChave = palavras_chave;

AnalisadorLexico::AnalisadorLexico(string nomeArquivo)
{
    (this->arquivo)= new ifstream(nomeArquivo.c_str());

}

AnalisadorLexico::~AnalisadorLexico()
{
    this->arquivo->close();
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
	for (i = 4; i < NUM_PALAVRAS_CHAVE; i++) {
		if (palavraLida.at(0) == palavras_chave[i].at(0)){
                this->valorLiteral = palavraLida;
			return true;
        }
	}
	if (isspace(palavraLida.at(0)))
		return false;
    return false;
}

bool AnalisadorLexico::fimDaPalavra(char* palavraEmVetor, int tamanhoPalavra)
{
	int indice;
    if(tamanhoPalavra==0)
        return false;
    char proxChar = this->arquivo->get();
    this->arquivo->unget();

	if (isspace(proxChar)) {
		this->arquivo->get();
		return true;
	}
	if (proxChar == EOF) {
		return true;
	}

    if(isalpha(palavraEmVetor[tamanhoPalavra]))
    {
		if (isalnum(proxChar)) {

			return false;
		}
		else {

			return true;
		}
    }
	if (isdigit(palavraEmVetor[tamanhoPalavra])) {
		if (isdigit(proxChar)) {

			return false;
		}
		else {

			return true;
		}
	}
	if (palavraEmVetor[tamanhoPalavra] == '<' || palavraEmVetor[tamanhoPalavra] == '>'
		|| palavraEmVetor[tamanhoPalavra] == ':') {
		if (proxChar == '=') {

			return false;
		}
		else
			return true;
	}
	for (indice = 5; indice < NUM_PALAVRAS_CHAVE; indice++) {//se for um dos símbolos independentes, retorna true
		if ((indice>4&&indice < 10) || (indice>18 && indice < 21) || (indice>22 && indice < 26)) {
			if (palavraEmVetor[tamanhoPalavra] == palavras_chave[indice].at(0))
				return true;
		}
	}
	return true;
}

string AnalisadorLexico::proximaPalavra()
{
    string* retorno;

    char palavraEmVetor[1024];
    char letra;
    int tamanhoPalavra = 0;

	while (!this->fimDaPalavra(palavraEmVetor, tamanhoPalavra)) {
		palavraEmVetor[tamanhoPalavra++] = this->arquivo->get();
	}
	if (temMaisPedacos()) {
		retorno = new string(palavraEmVetor, tamanhoPalavra);

		this->armazenarValor(*retorno);

		return *retorno;
	}
	return "";
}

string AnalisadorLexico::paraMinusculas(string palavra)
{
	if (palavra != "") {
		string emMinusculas(palavra);
		int i;

		for (i = 0; i < palavra.size(); i++)
			emMinusculas[i] = tolower(palavra[i]);

		return emMinusculas;
	}
	return "";

}

TipoPedaco AnalisadorLexico::proximoPedaco()
{
	string retorno = AnalisadorLexico::paraMinusculas(this->proximaPalavra());
		if (retorno != "") {
			string pedaco(retorno);

			int i;

			for (i = 0; i < NUM_PALAVRAS_CHAVE; i++)
				if (pedaco == AnalisadorLexico::palavrasChave[i])
					return TipoPedaco(i);
			int numero;
			sscanf(pedaco.c_str(), "%i", &numero);
			if (this->valorNumerico == numero) {
				return Numero;
			}
        if(isalpha(pedaco.at(0)))
            return Identificador;

		}
//jogar exceção
return Desconhecido;
}

char AnalisadorLexico::temMaisPedacos()
{
    return this->arquivo->eof();
}

string AnalisadorLexico::getLiteral()
{
    return this->valorLiteral;
}

int AnalisadorLexico::getNumero()
{
    return this->valorNumerico;
}
