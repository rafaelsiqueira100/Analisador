#include <iostream>
#include "AnalisadorSintatico.h"
#include "Variavel.h"

AnalisadorSintatico::AnalisadorSintatico(string nomeArquivo) : anaLex(new AnalisadorLexico(nomeArquivo)),
                                                               nivelAtual(0),
                                                               nomeFuncAtual(""),
                                                               retornoFuncInt(false),
                                                               jaRetornou(false),
                                                               erro(""),
                                                               numParenteses(0)
{
}

AnalisadorSintatico::~AnalisadorSintatico()
{
    delete (this->anaLex);
}

void AnalisadorSintatico::CompProgramaPrincipal() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Programa)
    {

        cout << '\n'
             << "Programa esperado";
    }

    prox = anaLex->proximoPedaco();
    if (prox != Identificador)
    {
        this->erro = "Identificador esperado";

        cout << '\n'
             << "Identificador esperado";
    }

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula)
    {
        this->erro = "Ponto e Virgula esperado";

        cout << '\n'
             << "Ponto e Virgula esperado";
    }

    prox = anaLex->verPedaco();
    while (prox == Variavel)
    {
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }

    if (prox == Procedimento)
        CompProcedimento();

    prox = anaLex->verPedaco();

    if (prox == Funcao)
        CompFuncao();
    prox = anaLex->verPedaco();
    if (prox != Comeco)
    {
        this->erro = "Inicio inesperado";

        cout << '\n'
             << "Inicio inesperado";
    }

    CompComandoComposto(); //COMPILA INiCIO E FIM
}
void AnalisadorSintatico::CompInicioPrograma() throw()
{
    if (this->erro.compare("") != 0)
        return;
    CompProgramaPrincipal();
    if (anaLex->proximoPedaco() != Ponto)
    {
        this->erro = "Ponto esperado";

        cout << '\n'
             << "Ponto esperado";
    }
}
void AnalisadorSintatico::CompProcedimento() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Procedimento)
    {
        this->erro = "Procedimento esperado";

        cout << '\n'
             << "Procedimento esperado";
    }
    prox = anaLex->proximoPedaco();

    if (prox != Identificador)
    {
        this->erro = "Identificador esperado";

        cout << '\n'
             << "Identificador esperado";
    }
    string nomeProc = anaLex->getLiteral();
    std::list<Simbolo> listaParametros;
    /*std::list<Simbolo>::iterator it;
    it = listaParametros.begin();*/
    int tamanhoLista = 0;
    prox = anaLex->proximoPedaco();
    if (prox != AbreParenteses)
    {
        this->erro = "Abre Parenteses esperado";

        cout << '\n'
             << "Abre Parenteses esperado";
    }

    prox = anaLex->verPedaco();
    while (prox == Inteiro || prox == Logico)
    {
        TipoPedaco tipoParametro = prox;
        TipoRetorno retornoParametro;

        switch (tipoParametro)
        {
        case Inteiro:
            retornoParametro = SimboloInteiro;
        case Logico:
            retornoParametro = SimboloLogico;
        }

        anaLex->proximoPedaco();
        prox = anaLex->proximoPedaco();
        if (prox != Identificador)
        {
            this->erro = "Identificador esperado !";

            cout << '\n'
                 << "Identificador esperado !";
        }

        Simbolo param(anaLex->getLiteral(), this->nivelAtual, retornoParametro);
        tamanhoLista++;

        listaParametros.push_back(param);
        prox = anaLex->verPedaco();
        switch (prox)
        {
        case FechaParenteses:
            break;
        case Virgula:
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
            break;
        default:
            this->erro = "Virgula ou Fecha Parenteses esperado!";

            cout << '\n'
                 << "Virgula ou Fecha Parenteses esperado!";
        }
    } //fim do while

    prox = anaLex->proximoPedaco();
    Simbolo *vetor = new Simbolo[tamanhoLista];
    int i;
    for (i = 0; i < tamanhoLista; i++)
    {
        *(vetor + i) = listaParametros.front();
        listaParametros.pop_front();
    }
    Metodo *procedimento;
    if (tamanhoLista != 0)
        procedimento = new Metodo(nomeProc, this->nivelAtual, vetor, tamanhoLista, SimboloVacuo);
    else
        procedimento = new Metodo(nomeProc, this->nivelAtual, nullptr, tamanhoLista, SimboloVacuo);

    if (prox != FechaParenteses)
    {
        this->erro = "Fecha Parenteses esperado !";

        cout << '\n'
             << "Fecha Parenteses esperado !";
    }

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula)
    {
        this->erro = "Ponto e virgula esperado";

        cout << '\n'
             << "Ponto e virgula esperado";
    }

    this->tabela.guarde(procedimento);
    prox = anaLex->verPedaco();

    while (prox == Variavel)
    {
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }

    //loop da main
    if (prox == Procedimento)
        CompProcedimento();
    if (prox == Funcao)
        CompFuncao();
    prox = anaLex->verPedaco();
    if (prox != Comeco)
        cout << '\n'
             << "Inicio esperado !";

    Simbolo *paramAtual;
    this->nivelAtual++;
    for (i = 0; i < tamanhoLista; i++)
    {
        tabela.guarde(vetor + i);
    }
    this->nivelAtual--;

    CompComandoComposto();

    /*prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula){
        cout << '\n' <<"ponto e virgula esperado";
    }*/
}
// E funçao??
void AnalisadorSintatico::CompComando() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->verPedaco();
    if (prox == Identificador)
    {
        string nomeId = anaLex->getLiteral();
        if (EhIdDeVariavel(nomeId))
        {
            CompChamadaDeVariavel();
        }
        else if (EhIdDeProcedimento(nomeId))
        {
            CompChamadaDeProcedimento();
            if (anaLex->proximoPedaco() != PontoVirgula)
            {
                this->erro = "Ponto e virgula esperado";

                cout << '\n'
                     << "Ponto e virgula esperado";
            }
        }
        else if (EhIdDeFuncao(nomeId))
        {
            CompChamadaDeFuncao();
            if (anaLex->proximoPedaco() != PontoVirgula)
            {
                this->erro = "Ponto e virgula esperado";

                cout << '\n'
                     << "Ponto e virgula esperado";
            }
        }
    }
    else
    {
        switch (prox)
        {
        case Se:
            CompSe();
            break;
        case Enquanto:
            CompEnquanto();
            break;
        case Tente:
            CompTente();
            break;
        case Pegue:
            CompPegue();
            break;
        }
    }
}
void AnalisadorSintatico::CompPegue() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Pegue)
    {
        this->erro = "Except esperado !";

        cout << '\n'
             << "Except esperado !";
    }

    prox = anaLex->verPedaco();
    if (prox == Comeco)
    {
        CompComandoComposto();
    }
    else
    {
        CompComando();
    }
}
void AnalisadorSintatico::CompTente() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Tente)
    {
        this->erro = "Try esperado !";

        cout << '\n'
             << "Try esperado !";
    }
    prox = anaLex->verPedaco();
    if (prox == Comeco)
    {
        CompComandoComposto();
    }
    else
    {
        CompComando();
    }
}
void AnalisadorSintatico::CompSe() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Se)
    {
        this->erro = "if esperado";

        cout << '\n'
             << "if esperado";
    }

    CompExpressaoLogica();

    prox = anaLex->proximoPedaco();
    if (prox != Entao)
    {
        this->erro = "Then esperado";

        cout << '\n'
             << "Then esperado";
    }

    prox = anaLex->verPedaco();
    if (prox == Comeco)
    {
        CompComandoComposto();
    }
    else
    {
        CompComando();
    }
    if (anaLex->verPedaco() == Senao)
    {
        anaLex->proximoPedaco();
        if (prox == Comeco)
        {
            CompComandoComposto();
        }
        else
        {
            CompComando();
        }
    }

    /*prox = anaLex->proximoPedaco();
    if (prox == PontoVirgula){prox = anaLex->proximoPedaco();
    if(prox !=FechaParenteses)
            cout << '\n' <<"Fecha Parenteses esperado !";
        cout << '\n' <<"Ponto e virgula esperado";
    }*/
}

void AnalisadorSintatico::CompExpressaoAritimetica() throw()
{
    if (this->erro.compare("") != 0)
        return;
    int parentesesNivel = numParenteses;
    TipoPedaco prox = anaLex->verPedaco();
    while(prox == AbreParenteses || prox==Subtracao){
            if(prox==AbreParenteses)
                numParenteses++;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
    }
        CompOperandoInteiro();
        prox = anaLex->verPedaco();
        while(prox == FechaParenteses){
            if(numParenteses==0){
                this->erro = "Parênteses desbalanceados!";
                cout << '/n'<< this->erro;
                return;
            }
            numParenteses--;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
        while(numParenteses>parentesesNivel || EhOperadorAritmetico(prox)){
            if(EhOperadorAritmetico(prox)){
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
            }
            else{
                this->erro = "Operador aritmético esperado!";
                cout << '\n'<< this->erro;
                return;
            }
        while(prox == AbreParenteses || prox==Subtracao){
            if(prox==AbreParenteses)
                numParenteses++;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
        if(prox== Numero || prox == Identificador)
        CompOperandoInteiro();
        prox = anaLex->verPedaco();
        while(prox == FechaParenteses){
            if(numParenteses==0){
                this->erro = "Parênteses desbalanceados!";
                cout << '/n'<< this->erro;
                return;
            }
            numParenteses--;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
    }
}
void AnalisadorSintatico::CompOperandoInteiro()throw(){
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->verPedaco();

    while(prox == AbreParenteses || prox == Subtracao){
        if(prox == AbreParenteses)
            numParenteses++;
        this->anaLex->proximoPedaco();
        prox = anaLex->verPedaco();
    }

    if(prox == Numero){
        anaLex->proximoPedaco();
        prox = anaLex->verPedaco();
            if(EhOperadorAritmetico(prox)){
                anaLex->proximoPedaco();
                CompExpressaoAritimetica();
            }
            else
                return;
    }
    if(prox == Identificador){
        string id = this->anaLex->getLiteral();
        if(!EhIdDeBool(id)){
            if(EhIdDeVariavel(id)){
                CompChamadaDeVariavel();
            }
            if(EhIdDeFuncao(id)){
                CompChamadaDeFuncao();
            }
            prox = anaLex->verPedaco();
            if(EhOperadorAritmetico(prox)){
                anaLex->proximoPedaco();
                CompExpressaoAritimetica();
            }
            else
                return;
        }
        else{
            this->erro = "Inteiro esperado !";
            cout << '\n' << this->erro;
            return;
        }
    }
}
void AnalisadorSintatico::CompOperandoBooleano()throw(){
    bool operandoBool = false;//suboperando bool
    bool primeiraVez = true;
    int parentesesNivel = numParenteses;
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->verPedaco();
    while(prox == AbreParenteses || prox == Negacao){
        if(prox == AbreParenteses)
            numParenteses++;
        this->anaLex->proximoPedaco();
        prox = anaLex->verPedaco();
    }

    if(prox == Verdadeiro || prox == Falso){
        anaLex->proximoPedaco();
        prox = anaLex->verPedaco();
            if(prox==Comparacao || prox == Diferente){
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
                while(prox == AbreParenteses || prox == Negacao){
                    if(prox == AbreParenteses)
                        numParenteses++;
                    this->anaLex->proximoPedaco();
                    prox = anaLex->verPedaco();
                }
                CompOperandoBooleano();
                while(prox==FechaParenteses){
                    if(numParenteses==0){
                        this->erro = "Parênteses desbalanceados!";
                        cout << '\n' << this->erro;
                        return;
                    }
                    numParenteses--;
                    this->anaLex->proximoPedaco();
                    prox = anaLex->verPedaco();
                }
                if(numParenteses>parentesesNivel&& parentesesNivel==0){
                    this->erro = "Parênteses desbalanceados!";
                    cout << '\n' << this->erro;
                    return;
                }

            }//fim do if prox==comparacao || prox == diferente

            }
            if(EhOperadorLogico(prox))
            {
                anaLex->proximoPedaco();
                CompExpressaoLogica();
            }
    }
    if (prox == Identificador|| prox==Numero){
            if(prox==Identificador)
        string id = this->anaLex.getLiteral();
        if(prox==Numero || (prox==Identificador && (!EhBool(id)))){//com certeza é expressão relacional
            if(prox==Identificador){
            if(EhIdDeVariavel(id)){
                CompChamadaDeVariavel();
            }
            if(EhIdDeFuncao(id)){
                CompChamadaDeFuncao();
            }
            }
            else{
                anaLex->proximoPedaco();
            }

            prox = anaLex->verPedaco();
            while(EhOperadorAritmetico(prox)){
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
                if(prox == Identificador || prox == Numero)
                    CompOperandoInteiro();
                prox = anaLex->verPedaco();
                else{
                    this->erro = "Inteiro esperado!";
                    cout << '\n' << this->erro;
                    return;
                }

            }
            if(EhOperadorRelacional(prox)){
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
            }
            else{
                this->erro = "Inteiro esperado!";
                cout << '\n' << this->erro;
                return;
            }

            while(prox == AbreParenteses || prox == Subtracao){
                if(prox == AbreParenteses)
                    numParenteses++;
                this->anaLex.proximoPedaco();
                prox = anaLex->verPedaco();
            }
            CompOperandoInteiro();
            prox = anaLex->verPedaco();
            while(prox==FechaParenteses){
                if(numParenteses==0){
                    this->erro = "Parenteses desbalanceados!";
                    cout << '\n' << this->erro;
                    return;
                }
                numParenteses--;
                this->anaLex.proximoPedaco();
                prox = anaLex->verPedaco();
            }
            if(EhOperadorLogico(prox)){
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
                if(prox == AbreParenteses ||prox == Identificador || prox == Numero ||prox == Verdadeiro|| prox == Falso || prox==Subtracao || prox == Negacao)
                CompExpressaoLogica();
            }
            if(numParenteses>parentesesNivel&& parentesesNivel==0){
                this->erro = "Parenteses desbalanceados!";
                cout << '\n' << this->erro;
                return;
            }

        }
        else{//só operadores booleanos
            if(EhIdDeVariavel(id)){
                CompDeclaracaoVariavel();
            }
            if(EhIdDeFuncao(id)){
                CompChamadaDeFuncao();
            }
            prox = anaLex->verPedaco();
            if(prox==Comparacao || prox == Diferente){
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
                while(prox == AbreParenteses || prox == Negacao){
                    if(prox == AbreParenteses)
                        numParenteses++;
                    this->anaLex.proximoPedaco();
                    prox = anaLex->verPedaco();
                }
                CompOperandoBooleano();
                while(prox==FechaParenteses){
                    if(numParenteses==0){
                        this->erro = "Parenteses desbalanceados!";
                        cout << '\n' << this->erro;
                        return;
                    }
                    numParenteses--;
                    this->anaLex.proximoPedaco();
                    prox = anaLex->verPedaco();
                }
                if(numParenteses>parentesesNivel&& parentesesNivel==0){
                    this->erro = "Parenteses desbalanceados!";
                    cout << '\n' << this->erro;
                    return;
                }

            }//fim do if(prox==comparacao || prox == diferente)

            if(EhOperadorLogico(prox){
                anaLex->proximoPedaco();
                CompExpressaoLogica();
            }
        }
        }
    }
}
void AnalisadorSintatico::CompExpressaoLogica() throw()
{
    if (this->erro.compare("") != 0)
        return;
    int parentesesNivel = numParenteses;
    TipoPedaco prox = anaLex->verPedaco();
    while(prox == AbreParenteses || prox==Negacao){
            if(prox==AbreParenteses)
                numParenteses++;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
    }
        CompOperandoBooleano();
        prox = anaLex->verPedaco();
        while(prox == FechaParenteses){
            if(numParenteses==0){
                this->erro = "Parênteses desbalanceados!";
                cout << '/n'<< this->erro;
                return;
            }
            numParenteses--;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
        while(numParenteses>parentesesNivel){
            if(EhOperadorLogico(prox)){
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
            }
            else{
                this->erro = "Operador lógico esperado!";
                cout << '\n'<< this->erro;
                return;
            }
        while(prox == AbreParenteses || prox==Negacao){
            if(prox==AbreParenteses)
                numParenteses++;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
        if(prox==Identificador || prox == Numero || prox == Verdadeiro || prox == Falso)
        CompOperandoBooleano();
        prox = anaLex->verPedaco();
        while(prox == FechaParenteses){
            if(numParenteses==0){
                this->erro = "Parênteses desbalanceados!";
                cout << '/n'<< this->erro;
                return;
            }
            numParenteses--;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
    }
}
void AnalisadorSintatico::CompComandoComposto() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Comeco)
    {
        this->erro = "Inicio esperado";

        cout << '\n'
             << "Inicio esperado";
    }

    this->nivelAtual++;
    do
    {
        CompComando();
        prox = anaLex->proximoPedaco();
    } while (prox != Fim && anaLex->temMaisPedacos());
    if (prox != Fim)
        cout << '\n'
             << "Fim esperado";

    this->tabela.eliminaNivel(this->nivelAtual);
    this->nivelAtual--;
}
void AnalisadorSintatico::CompDeclaracaoVariavel() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoRetorno tipoVar(SimboloVacuo);
    string id("");
    list<string> lista;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Variavel)
        cout << '\n'
             << "Variavel esperado";
    prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        cout << '\n'
             << "Identificador esperado";
    id = anaLex->getLiteral();
    lista.push_back(id);
    prox = anaLex->verPedaco();
    while (prox != DoisPontos && anaLex->temMaisPedacos())
    {
        prox = anaLex->proximoPedaco();
        if (prox != Virgula)
            cout << '\n'
                 << "Virgula esperado";
        prox = anaLex->proximoPedaco();
        if (prox != Identificador)
            cout << '\n'
                 << "Identificador esperado";
        id = anaLex->getLiteral();
        lista.push_back(id);
        prox = anaLex->verPedaco();
    }

    if (anaLex->proximoPedaco() != DoisPontos)
        cout << '\n'
             << "Dois Pontos esperado";
    prox = anaLex->verPedaco();
    if (prox == Logico || prox == Inteiro)
    {
        prox = anaLex->proximoPedaco();
        if (prox == Inteiro)
            tipoVar = SimboloInteiro;
        else
            tipoVar = SimboloLogico;
        prox = anaLex->proximoPedaco();
        if (prox != PontoVirgula)
            cout << '\n'
                 << "Ponto e Virgula esperado";
        int i(0);

        int tamanhoLista(lista.size());
        for (; i < tamanhoLista; i++)
        {
            id = *(lista.begin());
            Simbolo*simb=new Simbolo(id, this->nivelAtual, tipoVar);

            Var* variavel = new Var(id, this->nivelAtual, tipoVar);

            this->tabela.guarde(variavel);
            lista.pop_front();
        }
        lista.erase(lista.begin(), lista.end());
        return;
    } //nao e uma constante literal
    cout << '\n'
         << "Tipo Primitivo esperado";
}

bool AnalisadorSintatico::EhIdDeBool(string nomeSimbolo) throw()
{
    Simbolo *simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);
    bool ehVariavel = this->EhBool(*simbolo);
    return encontrou && ehVariavel;
}

bool AnalisadorSintatico::EhIdDeVariavel(string nomeSimbolo) throw()
{
    Simbolo *simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);
    bool ehVariavel = this->EhVariavel(*simbolo);
    return encontrou && ehVariavel;
}
bool AnalisadorSintatico::EhIdDeProcedimento(string nomeSimbolo) throw()
{
    Simbolo *simbolo;
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);
    bool ehProcedimento = typeid(*simbolo) == typeid(Metodo);
    return encontrou && ehProcedimento;
}
bool AnalisadorSintatico::EhIdDeFuncao(string nomeSimbolo) throw()
{
    Simbolo *simbolo;
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);

    return encontrou && EhFuncao(*simbolo);
}

bool AnalisadorSintatico::EhOperadorAritmetico(TipoPedaco tipo) throw()
{
    return (tipo == Soma) || (tipo == Subtracao) ||
    (tipo == Multiplicacao) || (tipo == Divisao) ||(tipo == Resto);
}
bool AnalisadorSintatico::EhOperadorLogico(TipoPedaco tipo)throw()
{
    return (tipo == E) || (tipo == Ou);
}
bool AnalisadorSintatico::EhFuncao(Simbolo simbolo) throw()
{
    return typeid(simbolo) == typeid(Metodo) && (simbolo.getTipoRetorno() != SimboloVacuo);
}
bool AnalisadorSintatico::FuncaoRetornaInteiro(Simbolo simbolo) throw()
{
    return simbolo.getTipoRetorno() == SimboloInteiro && typeid(simbolo) == typeid(Metodo);
}
bool AnalisadorSintatico::FuncaoRetornaBool(Simbolo simbolo) throw()
{
    return simbolo.getTipoRetorno() == SimboloLogico && typeid(simbolo) == typeid(Metodo);
}
bool AnalisadorSintatico::EhVariavel(Simbolo simbolo) throw()
{
    return typeid(simbolo) != typeid(Variavel);
}
bool AnalisadorSintatico::EhInteiro(Simbolo simbolo) throw()
{
    return simbolo.getTipoRetorno() == SimboloInteiro;
}
bool AnalisadorSintatico::EhOperadorRelacional(TipoPedaco tipo) throw()
{
    return tipo == Comparacao || tipo == Maior || tipo == Menor || tipo == Diferente || tipo == MaiorOuIgual || tipo == MenorOuIgual;
}
bool AnalisadorSintatico::EhValorLogico(TipoPedaco tipo) throw()
{
    return tipo == Verdadeiro || tipo == Falso;
}
bool AnalisadorSintatico::EhBool(Simbolo simbolo) throw()
{
    return simbolo.getTipoRetorno() == SimboloLogico;
}
void AnalisadorSintatico::CompChamadaDeVariavel() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        cout << '\n'
             << "Identificador esperado";

    if (!EhIdDeVariavel(anaLex->getLiteral()))
        cout << '\n'
             << "id de variavel invalido";

    Simbolo *simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    if (!this->tabela.encontrar(anaLex->getLiteral(), simbolo))
        cout << '\n'
             << "Variavel nao foi declarada";

    prox = anaLex->verPedaco();

    string nome = anaLex->getLiteral();
    if (prox == Atribuicao)
    {
        anaLex->proximoPedaco();
        if (simbolo->getTipoRetorno() == SimboloInteiro)
        {
            CompExpressaoAritimetica();
        }
        else if (simbolo->getTipoRetorno() == SimboloLogico)
        {
            CompExpressaoLogica();
        }
    }

    /*prox = anaLex->proximoPedaco();

    if (prox != PontoVirgula)
        cout << '\n'
             << "Ponto e virgula esperado !";*/
}
void AnalisadorSintatico::CompChamadaDeProcedimento() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        cout << '\n'
             << "Identificador esperado";

    if (!EhIdDeProcedimento(anaLex->getLiteral()))
        cout << '\n'
             << "Identificador de procedimento esperado";
    if (anaLex->proximoPedaco() != AbreParenteses)
        cout << '\n'
             << "Abre parenteses esperado";

    Simbolo *simbolo;
    this->tabela.encontrar(anaLex->getLiteral(), simbolo);
    int qtosParametros = ((Metodo *)simbolo)->getQuantosParametros();
    Simbolo parFormal;
    Simbolo *parReal;
    string nomeParReal;
    int i;
    //compilar parametros....
    for (i = 0; i < qtosParametros; i++)
    {
        if (i > 0)
            anaLex->proximoPedaco(); //virgula
        parFormal = ((Metodo *)simbolo)->getParametro(i);
        prox = anaLex->verPedaco();
        if (prox != Identificador)
        {
            if (parFormal.getTipoRetorno() == Inteiro)
            {
                if (prox == Numero)
                    goto verif;
                else //tbm pode ser expressao booleana
                    cout << '\n'
                         << "Inteiro esperado!";
            }
            else
            {
                if (prox == Verdadeiro || prox == Falso)
                    goto verif;
                else //tbm pode ser expressao aritmetica
                    cout << '\n'
                         << "Booleano esperado!";
            }
        }

        nomeParReal = anaLex->getLiteral();
        if (!this->tabela.encontrar(nomeParReal, parReal))
            cout << '\n'
                 << "Identificador nao declarada !";
        //achou o parametro real na tabela de simbolos
        if ((*parReal).getTipoRetorno() != parFormal.getTipoRetorno())
            cout << '\n'
                 << "Tipo do parametro real e diferente do parametro formal";
        if (EhIdDeFuncao(nomeParReal))
            CompChamadaDeFuncao();
        if (EhIdDeProcedimento(nomeParReal))
            CompChamadaDeProcedimento();
    verif:
        anaLex->proximoPedaco();
        if (anaLex->verPedaco() != Virgula && i < qtosParametros - 1)
            cout << '\n'
                 << "Virgula esperada !";
    }

    if (anaLex->proximoPedaco() != FechaParenteses)
        cout << '\n'
             << "Fecha parenteses esperado !";
}
void AnalisadorSintatico::CompChamadaDeFuncao() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    string nomeId("");
    if (prox != Identificador)
        cout << '\n'
             << "Identificador esperado";
    string nomeFuncEncontrado(anaLex->getLiteral());
    if (!EhIdDeFuncao(nomeFuncEncontrado))
        cout << '\n'
             << "Identificador de funcao esperado";
    if ((this->nomeFuncAtual).compare(nomeFuncEncontrado) == 0)
    {
        prox = anaLex->proximoPedaco();
        //POR ENQUANTO NaO TEM RECURSaO

        if (prox != Atribuicao)
            cout << '\n'
                 << ":= esperado!";
        prox = anaLex->verPedaco();
        if (this->retornoFuncInt)
        {
            switch (prox)
            {
            case Identificador:
                nomeId = anaLex->getLiteral();
                Simbolo *simboloId;
                if (tabela.encontrar(nomeId, simboloId))
                {
                    if (EhInteiro(*simboloId))
                    {
                        if (EhIdDeFuncao(nomeId))
                            CompChamadaDeFuncao();
                        else
                            this->anaLex->proximoPedaco();
                    }
                    else
                    {
                        cout << '\n'
                             << "Inteiro esperado, mas Booleano encontrado !";
                    }
                }
                else
                    cout << '\n'
                         << "Identificador nao declarado!";

                break;
            case Numero: //por enquanto nao
                //aceita expressao aritmetoica
                anaLex->proximoPedaco();
                break;
            }
        }
        else
        { //funçao retorna bool
            switch (prox)
            {
            case Identificador:
                nomeId = anaLex->getLiteral();
                Simbolo *simboloId;
                if (tabela.encontrar(nomeId, simboloId))
                {
                    if (EhBool(*simboloId))
                    {
                        if (EhIdDeFuncao(nomeId))
                            CompChamadaDeFuncao();
                        else
                            this->anaLex->proximoPedaco();
                    }
                    else
                    {
                        cout << '\n'
                             << "Inteiro esperado, mas Booleano encontrado !";
                    }
                }
                else
                    cout << '\n'
                         << "Identificador nao declarado!";

                break;
            case Verdadeiro:
            case Falso:
                anaLex->proximoPedaco();
                break;
            } //FIM DO SWITCH

        } //FIM DO IF(FUNCAORETONAINT)
        prox = anaLex->proximoPedaco();
        if (prox != PontoVirgula)
            cout << '\n'
                 << "; esperado !";
        return;
    } //FIM DO IF NOME DA FUNÇaO e IGUAL AO ENCONTRADO

    if (anaLex->proximoPedaco() != AbreParenteses)
        cout << '\n'
             << "Abre parenteses esperado";

    Simbolo *simbolo;
    this->tabela.encontrar(anaLex->getLiteral(), simbolo);
    int qtosParametros = ((Metodo *)simbolo)->getQuantosParametros();
    Simbolo parFormal;
    Simbolo *parReal;
    string nomeParReal;
    int i;
    //compilar parametros....
    for (i = 0; i < qtosParametros; i++)
    {
        if (i > 0)
            anaLex->proximoPedaco(); //virgula
        parFormal = ((Metodo *)simbolo)->getParametro(i);
        prox = anaLex->verPedaco();
        if (prox != Identificador)
        {
            if (parFormal.getTipoRetorno() == Inteiro)
            {
                if (prox == Numero)
                    goto verif;
                else //tbm pode ser expressao booleana
                    cout << '\n'
                         << "Inteiro esperado!";
            }
            else
            {
                if (prox == Verdadeiro || prox == Falso)
                    goto verif;
                else //tbm pode ser expressao aritmetica
                    cout << '\n'
                         << "Booleano esperado!";
            }
        }

        nomeParReal = anaLex->getLiteral();
        if (!this->tabela.encontrar(nomeParReal, parReal))
            cout << '\n'
                 << "Identificador nao declarada !";
        //achou o parametro real na tabela de simbolos
        if ((*parReal).getTipoRetorno() != parFormal.getTipoRetorno())
            cout << '\n'
                 << "Tipo do parametro real e diferente do parametro formal";
        if (EhIdDeFuncao(nomeParReal))
            CompChamadaDeFuncao();
        if (EhIdDeProcedimento(nomeParReal))
            CompChamadaDeProcedimento();
    verif:
        anaLex->proximoPedaco();
        if (anaLex->verPedaco() != Virgula && i < qtosParametros - 1)
            cout << '\n'
                 << "Virgula esperada !";
    }

    if (anaLex->proximoPedaco() != FechaParenteses)
        cout << '\n'
             << "Fecha parenteses esperado !";
}
void AnalisadorSintatico::CompEnquanto() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Enquanto)
    {
        cout << '\n'
             << "Enquanto esperado";
    }

    CompExpressaoLogica();

    prox = anaLex->proximoPedaco();
    if (prox == Faca)
    {
        cout << '\n'
             << "Do esperado";
    }

    prox = anaLex->verPedaco();
    if (prox == Comeco)
    {
        CompComandoComposto();
    }
    else
    {
        CompComando();
    }
}
//sintaxe do nossa declaraçao de funçao repetiçao de 0 a n
//function + identificador+ (           + [<parametros>] + )+ : boolean/integer + begin + ..
void AnalisadorSintatico::CompFuncao() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Funcao)
    {
        cout << '\n'
             << "Funçao esperada";
    }

    prox = anaLex->proximoPedaco();
    if (prox != Identificador)
    {
        cout << '\n'
             << "Identificador esperado";
    }

    string nomeFunc = anaLex->getLiteral();
    this->nomeFuncAtual = nomeFunc;
    std::list<Simbolo> listaParametros;
    //std::list<Simbolo>::iterator it;
    //it = listaParametros.begin();
    int tamanhoLista = 0;

    prox = anaLex->proximoPedaco();
    if (prox != AbreParenteses)
    {
        cout << '\n'
             << "Abre Parenteses esperado";
    }

    prox = anaLex->verPedaco();
    while (prox == Inteiro || prox == Logico)
    {
        TipoPedaco tipoParametro = prox;
        TipoRetorno retornoParametro;

        switch (tipoParametro)
        {
        case Inteiro:
            retornoParametro = SimboloInteiro;

            break;
        case Logico:
            retornoParametro = SimboloLogico;

            break;
        }

        anaLex->proximoPedaco();
        prox = anaLex->proximoPedaco();

        if (prox != Identificador)
            cout << '\n'
                 << "Identificador esperado !";
        Simbolo param(anaLex->getLiteral(), this->nivelAtual, retornoParametro);
        listaParametros.push_back(param);
        tamanhoLista++;
        prox = anaLex->verPedaco();
        switch (prox)
        {
        case FechaParenteses:
            goto foraLoop;
            break;
        case Virgula:
            anaLex->proximoPedaco();
            break;
        default:
            cout << '\n'
                 << "Virgula ou Fecha Parenteses esperado!";
        }
        prox = anaLex->verPedaco();

    } //fim do while
foraLoop:
    prox = anaLex->proximoPedaco();
    if (prox != FechaParenteses)
        cout << '\n'
             << "Fecha Parenteses esperado !";
    prox = anaLex->proximoPedaco();
    if (prox != DoisPontos)
        cout << '\n'
             << "Dois Pontos esperado !";
    prox = anaLex->proximoPedaco();
    if (!(prox == Inteiro || prox == Logico))
        cout << '\n'
             << "Tipo de retorno esperado !";

    TipoRetorno retorno;
    switch (prox)
    {
    case Inteiro:
        retorno = SimboloInteiro;
        this->retornoFuncInt = true;
        break;
    case Logico:
        retorno = SimboloLogico;
        this->retornoFuncInt = false;
        break;
    }

    Simbolo *vetor = new Simbolo[tamanhoLista];
    int i;
    for (i = 0; i < tamanhoLista; i++)
    {
        *(vetor + i) = listaParametros.front();
        listaParametros.pop_front();
    }

    Metodo *funcao = new Metodo(nomeFunc, this->nivelAtual, vetor, tamanhoLista, retorno);
    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula)
    {
        cout << '\n'
             << "ponto e virgula esperado";
    }
    this->tabela.guarde(funcao);
    prox = anaLex->verPedaco();

    while (prox == Variavel)
    {
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }

    if (prox == Procedimento)
    {
        this->nomeFuncAtual = "";
        CompProcedimento();
    }
    if (prox == Funcao)
    {
        this->nomeFuncAtual = "";
        CompFuncao();
    }
    this->nomeFuncAtual = nomeFunc;
    this->retornoFuncInt = retorno == SimboloInteiro;
    this->jaRetornou = false;
    prox = anaLex->verPedaco();
    if (prox != Comeco)
        cout << '\n'
             << "Inicio esperado";

    Simbolo *paramAtual;
    this->nivelAtual++;
    for (i = 0; i < tamanhoLista; i++)
    {
        tabela.guarde(vetor + i);
    }
    this->nivelAtual--;

    CompComandoComposto();

    if (!jaRetornou)
        cout << '\n'
             << "Funcao nao retorna nenhum valor!";
    this->nomeFuncAtual = "";
    this->jaRetornou = false;
}
