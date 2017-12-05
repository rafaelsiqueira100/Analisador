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
    if (prox == Variavel){
        CompDeclaracaoVariavel();
    }
    //loop da main
    CompComandoComposto();

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula){
        throw "ponto e virgula esperado";
    }
}

void AnalisadorSintatico::CompComando(){
    TipoPedaco prox = anaLex->verPedaco();
    if (prox == Identificador){
        if (EhIdDeVariavel(anaLex->getLiteral())){
            CompChamadaDeVariavel();
        }
        else if (EhIdDeProcedimento(anaLex->getLiteral())){
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

    prox = anaLex->proximoPedaco();
    if (prox == Entao){
        throw "Then esperado";
    }

    prox = anaLex->proximoPedaco();
    if (prox == Comeco){
        CompComandoComposto();
    }
    else{
        CompComando();
    }

    prox = anaLex->proximoPedaco();
    if (prox == PontoVirgula){
        throw "Ponto e virgula esperado";
    }
}

void AnalisadorSintatico::CompExpressaoAritimetica(){
    CompTermo();

    TipoPedaco prox;

    while (EhMaisOuMenos(anaLex->verPedaco())){
        prox = anaLex->proximoPedaco();
    }

    CompFator();
}

void AnalisadorSintatico::CompTermo(){
    CompFator();

    TipoPedaco prox;
    while (EhVezesOuDividirOuResto(anaLex->verPedaco())){
        prox = anaLex->proximoPedaco();

        CompFator();
    }
}

void AnalisadorSintatico::CompFator(){
    TipoPedaco prox = anaLex->proximoPedaco();

    if (prox == Identificador){
        Simbolo* simbolo = tabela.pegue(anaLex->getLiteral());
        if(EhFuncao(*simbolo) && FuncaoRetornaInteiro(*simbolo)){
            CompFuncao();
        }
        else if ((!EhVariavel(*simbolo)) || (!EhInteiro(*simbolo))){
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
    TipoPedaco prox = anaLex->proximoPedaco();
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
            Simbolo* simbolo = tabela.pegue(anaLex->getLiteral());
        if (EhFuncao(*simbolo) && FuncaoRetornaBool(*simbolo)){
            CompChamadaDeFuncao();
        }
        else if ((!EhVariavel(*simbolo)) && (!EhBool(*simbolo))){
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
    TipoPedaco prox = anaLex->proximoPedaco();
    if(prox!= Comeco)
        throw "Início esperado";
    do{
        CompComando();
        prox = anaLex->proximoPedaco();
    }while(prox!=Fim && anaLex->temMaisPedacos());
    if(prox!=Fim)
        throw "Fim esperado";
}
void AnalisadorSintatico::CompDeclaracaoVariavel(){
    TipoPedaco prox = anaLex->proximoPedaco();
    if(prox!=Variavel)
        throw "Variável esperado";
    prox = anaLex->proximoPedaco();
    if(prox!= Identificador)
        throw "Identificador esperado";
    while(anaLex->verPedaco()!=DoisPontos && anaLex->temMaisPedacos()){
        prox = anaLex->proximoPedaco();
        if(prox!=Virgula)
            throw "Vírgula esperado";
        prox = anaLex->proximoPedaco();
        if(prox!=Identificador)
            throw "Identificador esperado";

    }
    if(anaLex->proximoPedaco()!=DoisPontos)
        throw "Dois Pontos esperado";
    prox = anaLex->proximoPedaco();
    if(prox==Logico || prox == Inteiro){
        prox = anaLex->proximoPedaco();
        if(prox!=PontoVirgula)
            throw "Ponto e Vírgula esperado";
        return;
    }//não é uma constante literal
    throw "Tipo Primitivo esperado";
}
void AnalisadorSintatico::CompInicioPrograma(){
    CompProgramaPrincipal();
    if(anaLex->proximoPedaco()!=Ponto)
        throw "Ponto esperado";
}
bool AnalisadorSintatico::EhIdDeVariavel(string nomeSimbolo){
    Simbolo* simbolo;
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);
    bool ehVariavel = this->EhVariavel(*simbolo);
    return encontrou && ehVariavel;
}
bool AnalisadorSintatico::EhIdDeProcedimento(string nomeSimbolo){
    Simbolo* simbolo;
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);
    bool ehProcedimento = simbolo->getTipo() == SimboloProcedimento;
    return encontrou && ehProcedimento;
}
bool AnalisadorSintatico::EhMaisOuMenos(TipoPedaco tipo){
    return (tipo == Soma) || (tipo == Subtracao);
}
bool AnalisadorSintatico::EhVezesOuDividir(TipoPedaco tipo){
    return (tipo == Multiplicacao) || (tipo == Divisao);
}
bool AnalisadorSintatico::EhVezesOuDividirOuResto(TipoPedaco tipo){
    return EhVezesOuDividir(tipo) || (tipo == Resto);
}
bool AnalisadorSintatico::EhFuncao(Simbolo simbolo){
    return simbolo.getTipo() == SimboloFuncao;
}
bool AnalisadorSintatico::FuncaoRetornaInteiro(Simbolo simbolo){
    return simbolo.getTipo()== SimboloInteiro;
}
bool AnalisadorSintatico::FuncaoRetornaBool(Simbolo simbolo){
    return simbolo.getTipo()== SimboloLogico;
}
bool AnalisadorSintatico::EhVariavel(Simbolo simbolo){
    return simbolo.getTipo() == SimboloVariavel;
}
bool AnalisadorSintatico::EhInteiro(Simbolo simbolo){
    return simbolo.getTipo() == SimboloInteiro;
}
bool AnalisadorSintatico::EhOperadorRelacional(TipoPedaco tipo){
    return tipo == Comparacao || tipo == Maior || tipo == Menor || tipo == Diferente || tipo == MaiorOuIgual || tipo == MenorOuIgual;
}
bool AnalisadorSintatico::EhValorLogico(TipoPedaco tipo){
    return tipo == Verdadeiro || tipo == Falso;
}
bool AnalisadorSintatico::EhBool(Simbolo simbolo){
    return simbolo.getTipo()== SimboloLogico;
}
void AnalisadorSintatico::CompChamadaDeVariavel(){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        throw "Identificador esperado";

    if (!EhIdDeVariavel(anaLex->getLiteral()))
        throw "id de variavel invalido";

    Simbolo* simbolo = this->tabela.pegue(anaLex->getLiteral());

    prox = anaLex->proximoPedaco();

    if (prox == Atribuicao){
        if (simbolo->getTipo() == SimboloInteiro){
            CompExpressaoAritimetica();
        }
        else if (simbolo->getTipo() == SimboloLogico){
            CompExpressaoLogica();
        }
    }

    if(prox != PontoVirgula)
        throw "ponto e virgula esperado";
}
void AnalisadorSintatico::CompChamadaDeProcedimento(){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        throw "Identificador esperado";

    if (!EhIdDeProcedimento(anaLex->getLiteral()))
        throw "id de procedimento invalido";

    Simbolo* simbolo = this->tabela.pegue(anaLex->getLiteral());

}
void AnalisadorSintatico::CompChamadaDeFuncao(){
}
void AnalisadorSintatico::CompEnquanto(){
}
void AnalisadorSintatico::CompFuncao(){
}
