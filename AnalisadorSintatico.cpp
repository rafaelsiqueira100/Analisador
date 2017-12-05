#include "AnalisadorSintatico.h"

AnalisadorSintatico::AnalisadorSintatico(string nomeArquivo):
    this->anaLex(new AnalisadorLexico(nomeArquivo)),
    this->nivelAtual(0){}



AnalisadorSintatico::~AnalisadorSintatico()
{
    delete (this->anaLex);
}

void AnalisadorSintatico::CompProgramaPrincipal()throws(string){
     TipoPedaco prox = anaLex->proximoPedaco();
     if(prox!=Programa)
         throw "Programa esperado";

    prox = anaLex->proximoPedaco();
     if(prox!=Identificador)
         throw "Identificador esperado";
    prox = anaLex->proximoPedaco();
    if(prox!=PontoVirgula)
         throw "Ponto e Vírgula esperado";
    prox = anaLex->verPedaco();
    while(prox==Variavel){
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }
    if(prox==Procedimento)
        CompProcedimento();
    if(prox==Funcao)
        CompFuncao();
    prox = anaLex->verPedaco();
    if(prox!=Inicio)
        throw "Início inesperado";

    CompComandoComposto();//COMPILA INÍCIO E FIM

}
void AnalisadorSintatico::CompInicioPrograma() throws(string){
    CompProgramaPrincipal();
    if(anaLex->proximoPedaco()!=Ponto)
        throw "Ponto esperado";
}
void AnalisadorSintatico::CompProcedimento()throws(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Procedimento){
        throw "procedimento esperado";
    }
    prox = anaLex->proximoPedaco();
    if (prox != Identificador){
        throw "identificador esperado";
    }
    prox = anaLex->proximoPedaco();
    if (prox != AbreParenteses){
        throw "Abre Parênteses esperado";
    }

    prox = anaLex->verPedaco();
    while(prox == Inteiro || prox == Logico){
        anaLex->proximoPedaco();
        prox = anaLex->proximoPedaco();
        if(prox != Identificador)
            throw "Identificador esperado !";
        prox = anaLex->verPedaco();
        switch(prox){
            case FechaParenteses:
            goto foraLoop;
            break;
            case Virgula:
            anaLex->proximoPedaco();
            break;
            case default:
                throw "Vírgula ou Fecha Parênteses esperado!";
        }
        prox = anaLex->verPedaco();

    }//fim do while
foraLoop:prox = anaLex->proximoPedaco();
    if(prox !=FechaParenteses)
            throw "Fecha Parênteses esperado !";

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula){
        throw "ponto e virgula esperado";
    }

    prox = anaLex->verPedaco();
    while (prox == Variavel){
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }
    //loop da main
    if(prox==Procedimento)
        CompProcedimento();
    if(prox==Funcao)
        CompFuncao();
    prox = anaLex->verPedaco();
    if(prox!=Inicio)
        throw "Início inesperado";
    CompComandoComposto();

    /*prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula){
        throw "ponto e virgula esperado";
    }*/
}
// E função??
void AnalisadorSintatico::CompComando()throws(string){
    TipoPedaco prox = anaLex->verPedaco();
    if (prox == Identificador){
        string nomeId = anaLex->getLiteral();
        if (EhIdDeVariavel(nomeId)){
            CompChamadaDeVariavel();
        }
        else if (EhIdDeProcedimento(nomeId)){
            CompChamadaDeProcedimento();
        }
        else if(EhIdDeFuncao(nomeId)){
            CompChamadaDeFuncao();
        }

    }
    else{
        if (prox == Se){
            CompSe();
        }
        else if (prox == Enquanto){
            CompEnquanto();
        }
        //....
    }
}

void AnalisadorSintatico::CompSe()throws(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Se){
        throw "if esperado";
    }

    CompExpressaoLogica();

    prox = anaLex->proximoPedaco();
    if (prox == Entao){
        throw "Then esperado";
    }

    prox = anaLex->verPedaco();
    if (prox == Comeco){
        CompComandoComposto();
    }
    else{
        CompComando();
    }

    /*prox = anaLex->proximoPedaco();
    if (prox == PontoVirgula){prox = anaLex->proximoPedaco();
    if(prox !=FechaParenteses)
            throw "Fecha Parênteses esperado !";
        throw "Ponto e virgula esperado";
    }*/
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

void AnalisadorSintatico::CompFator()throws(string){
    TipoPedaco prox = anaLex->proximoPedaco();

    if (prox == Identificador){
        Simbolo* simbolo
       this->tabela.encontrar(anaLex->getLiteral(), simbolo);
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

void AnalisadorSintatico::CompExpressaoRelacional()throws(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (! EhOperadorRelacional(prox)){
        throw "operador relacional esperado";
    }

    CompExpressaoAritimetica();
}

void AnalisadorSintatico::CompExpressaoLogica(){
    CompTermoRelacional();

    TipoPedaco prox = anaLex->verPedaco();
    while (prox == Ou){
        anaLex->proximoPedaco();
        CompTermoRelacional();
        prox = anaLex->verPedaco();
    }
}

void AnalisadorSintatico::CompTermoRelacional(){
    //CompTermoRelacional();

    TipoPedaco prox;
    while (anaLex->verPedaco() == E){
        prox = anaLex->proximoPedaco();
        CompFatorRelacional();
    }
}

void AnalisadorSintatico::CompFatorRelacional() throws(string){
    TipoPedaco prox = anaLex->proximoPedaco();

    if (prox == Negacao){
        prox = anaLex->proximoPedaco();
    }

    if (prox == Identificador){
            Simbolo* simbolo;
        this->tabela.encontrar(anaLex->getLiteral(), simbolo);
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

void AnalisadorSintatico::CompComandoComposto() throws(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if(prox!= Comeco)
        throw "Início esperado";
    this->nivelAtual++;
    do{
        CompComando();
        prox = anaLex->proximoPedaco();
    }while(prox!=Fim && anaLex->temMaisPedacos());
    if(prox!=Fim)
        throw "Fim esperado";
    this->nivelAtual--;
}
void AnalisadorSintatico::CompDeclaracaoVariavel() throws(string){
    TipoRetorno tipoVar(SimboloVacuo);
    string id("");
    TipoPedaco prox = anaLex->proximoPedaco();
    if(prox!=Variavel)
        throw "Variável esperado";
    prox = anaLex->proximoPedaco();
    if(prox!= Identificador)
        throw "Identificador esperado";
    id = anaLex->getLiteral();
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
        if(prox==Inteiro)
            tipoVar=SimboloInteiro;
        else
            tipoVar =SimboloLogico;
        if(prox!=PontoVirgula)
            throw "Ponto e Vírgula esperado";

        Simbolo* novaVar = new Simbolo(id, this->nivelAtual, tipoVar);
        anaLex->tabela.guarde(novaVar);
        return;
    }//não é uma constante literal
    throw "Tipo Primitivo esperado";
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
    bool ehProcedimento = typeid(*simbolo) == typeid(Metodo);
    return encontrou && ehProcedimento;
}
bool AnalisadorSintatico::EhIdDeFuncao(string nomeSimbolo){
    Simbolo* simbolo;
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);

    return encontrou && EhFuncao(*simbolo);
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
    return typeid(simbolo)==typeid(Metodo) && simbolo.getTipoRetorno != SimboloVacuo;
}
bool AnalisadorSintatico::FuncaoRetornaInteiro(Simbolo simbolo){
    return simbolo.getTipoRetorno()== SimboloInteiro && typeid(simbolo) == typeid(Metodo);
}
bool AnalisadorSintatico::FuncaoRetornaBool(Simbolo simbolo){
    return simbolo.getTipoRetorno()== SimboloLogico && typeid(simbolo) == typeid(Metodo);
}
bool AnalisadorSintatico::EhVariavel(Simbolo simbolo){
    return typeid(simbolo) != typeid(Metodo);
}
bool AnalisadorSintatico::EhInteiro(Simbolo simbolo){
    return simbolo.getTipoRetorno() == SimboloInteiro;
}
bool AnalisadorSintatico::EhOperadorRelacional(TipoPedaco tipo){
    return tipo == Comparacao || tipo == Maior || tipo == Menor || tipo == Diferente || tipo == MaiorOuIgual || tipo == MenorOuIgual;
}
bool AnalisadorSintatico::EhValorLogico(TipoPedaco tipo){
    return tipo == Verdadeiro || tipo == Falso;
}
bool AnalisadorSintatico::EhBool(Simbolo simbolo){
    return simbolo.getTipoRetorno()== SimboloLogico;
}
void AnalisadorSintatico::CompChamadaDeVariavel() throws(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        throw "Identificador esperado";

    if (!EhIdDeVariavel(anaLex->getLiteral()))
        throw "id de variavel invalido";

    Simbolo* simbolo;
    if(!this->tabela.encontrar(anaLex->getLiteral(), simbolo))
        throw "Variável não foi declarada";

    prox = anaLex->proximoPedaco();

    if (prox == Atribuicao){
        if (simbolo->getTipoRetorno() == SimboloInteiro){
            CompExpressaoAritimetica();
        }
        else if (simbolo->getTipoRetorno() == SimboloLogico){
            CompExpressaoLogica();
        }
    }

    if(prox != PontoVirgula)
        throw "Ponto e vírgula esperado !";
}
void AnalisadorSintatico::CompChamadaDeProcedimento() throws(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        throw "Identificador esperado";

    if (!EhIdDeProcedimento(anaLex->getLiteral()))
        throw "Identificador de procedimento esperado";
    if(anaLex->proximoPedaco!=AbreParenteses)
        throw "Abre parênteses esperado";

    Simbolo* simbolo;
    this->tabela.encontrar(anaLex->getLiteral(), simbolo);
//compilar parâmetros....
    if(anaLex->proximoPedaco!=FechaParenteses)
        throw "Fecha parênteses esperado !";
    if(anaLex->proximoPedaco!=PontoVirgula)
        throw "Ponto e Vírgula esperado !";
}
void AnalisadorSintatico::CompChamadaDeFuncao(){
    TipoPedaco prox = anaLex->proximoPedaco();
    if(prox!= Identificador)
        throw "Identificador esperado";
}
void AnalisadorSintatico::CompEnquanto(){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Enquanto){
        throw "Enquanto esperado";
    }

    CompExpressaoLogica();

    prox = anaLex->proximoPedaco();
    if (prox == Faça){
        throw "Do esperado";
    }

    prox = anaLex->verPedaco();
    if (prox == Comeco){
        CompComandoComposto();
    }
    else{
        CompComando();
    }
}
//sintaxe do nossa declaração de função repetição de 0 a n
//function + identificador+ (           + [<parãmetros>] + )+ : boolean/integer + begin + ..
void AnalisadorSintatico::CompFuncao(){
     TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Funcao){
        throw "Função esperada";
    }

    prox = anaLex->proximoPedaco();
    if (prox != Identificador){
        throw "Identificador esperado";
    }

    prox = anaLex->proximoPedaco();
    if (prox != AbreParenteses){
        throw "Abre Parênteses esperado";
    }

    prox = anaLex->verPedaco();
    while(prox == Inteiro || prox == Logico){
        anaLex->proximoPedaco();
        prox = anaLex->proximoPedaco();
        if(prox != Identificador)
            throw "Identificador esperado !";
        prox = anaLex->verPedaco();
        switch(prox){
            case FechaParenteses:
            goto foraLoop;
            break;
            case Virgula:
            anaLex->proximoPedaco();
            break;
            case default:
                throw "Vírgula ou Fecha Parênteses esperado!";
        }
        prox = anaLex->verPedaco();

    }//fim do while
foraLoop:prox = anaLex->proximoPedaco();
    if(prox !=FechaParenteses)
            throw "Fecha Parênteses esperado !";
    prox = anaLex->proximoPedaco();
    if(prox !=DoisPontos)
            throw "Dois Pontos esperado !";
    prox = anaLex->proximoPedaco;
    if(!(prox==Inteiro || prox==Logico))
            throw "Tipo de retorno esperado !";
    prox = anaLex->verPedaco();
    while (prox == Variavel){
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }
    //loop da main
    if(prox==Procedimento)
        CompProcedimento();
    if(prox==Funcao)
        CompFuncao();
    prox = anaLex->verPedaco();
    if(prox!=Inicio)
        throw "Início inesperado";
    CompComandoComposto();
}
