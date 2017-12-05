#ifndef ANALISADORSINTATICO_H_INCLUDED
#define ANALISADORSINTATICO_H_INCLUDED
#include "TabelaDeSimbolos.h"
#include "analisadorlexico.h"
#include "tipopedaco.h"
#include "simbolo.h"
#include "metodo.h"
#include <typeindex>
#include <typeinfo>

using namespace std;

class AnalisadorSintatico
{
    private:
        TabelaDeSimbolos tabela;
        AnalisadorLexico* anaLex;
        int nivelAtual ;
    public:
        AnalisadorSintatico() ;
        AnalisadorSintatico(string);
        ~AnalisadorSintatico();
        void CompComandoComposto() throws(string);
        void CompProcedimento() throws(string);
        void CompComando() throws(string);
        void CompSe() throws(string);
        void CompExpressaoAritimetica();
        void CompTermo();
        void CompExpressaoRelacional() throws(string);
        void CompFator() throws(string);
        void CompProgramaPrincipal() throws(string);
        void CompExpressaoLogica();
        void CompTermoRelacional();
        void CompFatorRelacional();
        void CompDeclaracaoVariavel() throws(string);
        void CompInicioPrograma() throws(string);
        bool EhIdDeVariavel(string);
        bool EhIdDeProcedimento(string);
        bool EhMaisOuMenos(TipoPedaco);
        bool EhVezesOuDividir(TipoPedaco);
        bool EhVezesOuDividirOuResto(TipoPedaco);
        bool EhFuncao(Simbolo);
        bool FuncaoRetornaInteiro(Simbolo);
        bool FuncaoRetornaBool(Simbolo);
        bool EhVariavel(Simbolo);
        bool EhInteiro(Simbolo);
        bool EhOperadorRelacional(TipoPedaco);
        bool EhBool(Simbolo);
        bool EhValorLogico(TipoPedaco);
        void CompChamadaDeVariavel()throws(string);
        void CompChamadaDeProcedimento() throws(string);
        void CompChamadaDeFuncao();
        void CompEnquanto();
        void CompFuncao();

};

#endif // ANALISADORSINTATICO_H_INCLUDED
