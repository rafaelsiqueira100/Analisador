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
    CompComandoComposto();

    TipoPedaco prox = anaLex->proximoPedaco();

    if (prox != Ponto){
        throw "ponto final esperado";
    }
}

void AnalisadorSintatico::CompProcedimento(){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Procedimento){
        throw "procedimento esperado";
    }

    prox = anaLex->proximoPedaco();
    if (prox != Identificador){
        throw "identificador esperado";
    }

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula){
        throw "ponto e virgula esperado";
    }

    prox = anaLex->verPedaco();
    if (prox != Variavel){
        CompDeclaracaoVariavel();
    }

    CompComandoComposto();

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula){
        throw "ponto e virgula esperado"
    }
}

void AnalisadorSintatico::CompComando(){
    TipoPedaco prox = anaLex->verPedaco();
    if (prox == Identificador){
        if (EhIdDeVariavel()){
            CompChamadaDeVariavel();
        }
        else if (EhIdDeProcedimento()){
            CompChamadaDeProcedimento();
        }
        else{
            throw "Identificador invalido";
        }
    }
    else{
        if (prox == Se){
            CompSe();
        }
        else if (prox == Enquanto){
            CompEnquanto();
        }
    }
}

void AnalisadorSintatico::CompSe(){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Se){
        throw "if esperado";
    }

    CompExpressaoLogica();

    prox = anaLex.proximoPedaco();
    if (prox == Entao){
        throw "Then esperado";
    }

    prox = anaLex.proximoPedaco();
    if (prox == Comeco){
        CompComandoComposto();
    }
    else{
        CompComando();
    }

    prox = anaLex.proximoPedaco();
    if (prox == PontoVirgula){
        throw "Ponto e virgula esperado";
    }
}

void AnalisadorSintatico::CompExpressaoAritimetica(){
    CompTermo();

    TipoPedaco prox;

    while (EhMaisOuMenos(anaLex->verPedaco())){
        prox = anaLex.verPedaco();
    }

    CompFator();
}

void AnalisadorSintatico::CompTermo(){
    CompFator();

    TipoPedaco prox;
    while (EhVezesOuDividirOuResto(anaLex->verPedaco())){
        prox = anaLex.proximoPedaco();

        CompFator();
    }
}

void AnalisadorSintatico::CompFator(){
    TipoPedaco prox = anaLex->proximoPedaco();

    if (prox = Identificador){
        if(ehFuncao(simbolo)  && FuncaoRetornaInteiro(simbolo)){
            CompFuncao();
        }
        else if ((!EhVariavel(simbolo)) || (!EhInteiro(simbolo))){
            throw "o simbolo não é variavel nem numero";
        }
    }
    else {
        if (prox == AbreParenteses){
            CompExpressaoAritimetica();

            prox = anaLex->proximoPedaco();
            if (prox == FechaParenteses){
                throw "Fecha parenteses esperado";
            }
        }
        else if (prox != Numero){
            throw "numero esperado";
        }
    }


}

void AnalisadorSintatico::CompExpressaoRelacional(){
    TipoPedaco prox = anaLex.proximoPedaco();
    if (! EhOperadorRelacional(prox)){
        throw "operador relacional esperado";
    }

    CompExpressaoAritimetica();
}

void AnalisadorSintatico::CompExpressaoLogica(){
    CompTermoRelacional();

    TipoPedaco prox;
    while (anaLex->verPedaco() == Ou){
        prox = anaLex->proximoPedaco();
        CompTermoRelacional();
    }
}

void AnalisadorSintatico::CompTermoRelacional(){
    CompTermoRelacional();

    TipoPedaco prox;
    while (anaLex->verPedaco() == E){
        prox = anaLex->proximoPedaco();
        CompFatorRelacional();
    }
}

void AnalisadorSintatico::CompFatorRelacional(){
    TipoPedaco prox = anaLex->proximoPedaco();

    if (prox == Negacao){
        prox = anaLex->proximoPedaco();
    }

    if (prox == Identificador){
        if (EhFuncao(simbolo) && FuncaoRetornaBool(simbolo)){
            CompChamadaFuncao();
        }
        else if ((!EhVariavel(simbolo)) && (!EhBoll(simbolo))){
            CompExpressaoRelacional();
        }
    }
    else{
        if (prox == AbreParenteses){
            CompExpressaoLogica();

            prox = anaLex->proximoPedaco();

            if (prox != FechaParenteses){
                throw "Fecha parenteses esperado";
            }
        }
        else if (!EhValorLogico(prox)){
            throw "valor logico esperado";
        }
    }
}

void AnalisadorSintatico::CompComandoComposto(){
}
