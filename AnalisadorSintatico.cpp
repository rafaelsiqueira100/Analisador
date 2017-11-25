#include "AnalisadorSintatico.h"

AnalisadorSintatico::AnalisadorSintatico(string nomeArquivo)
{
    this->anaLex = new AnalisadorLexico(nomeArquivo);

}

AnalisadorSintatico::~AnalisadorSintatico()
{
    free (this->anaLex);
}

void AnalisadorSintatico::CompProgramaPrincipal(){
}

void AnalisadorSintatico::CompProcedimento(){
}

void AnalisadorSintatico::CompComando(){
}

void AnalisadorSintatico::CompSe(){
}

void AnalisadorSintatico::CompExpressaoAritimetica(){
}

void AnalisadorSintatico::CompTermo(){
}

void AnalisadorSintatico::CompFator(){
}

void AnalisadorSintatico::CompExpressaoRelacional(){
}

void AnalisadorSintatico::CompExpressaoLogica(){
}

void AnalisadorSintatico::CompTermoRelacional(){
}

void AnalisadorSintatico::CompFatorRelacional(){
}

void AnalisadorSintatico::CompComandoComposto(){
}
