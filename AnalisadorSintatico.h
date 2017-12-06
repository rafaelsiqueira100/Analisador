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
        string nomeFuncAtual;
        bool retornoFuncInt;
        bool jaRetornou;
        string erro;
    public:
        AnalisadorSintatico() ;
        AnalisadorSintatico(string);
        ~AnalisadorSintatico();
        void CompComandoComposto() throw(string);
        void CompProcedimento() throw(string);
        void CompComando() throw(string);
        void CompSe() throw(string);
        void CompExpressaoAritimetica();
        void CompTermo();
        void CompExpressaoRelacional() throw(string);
        void CompFator() throw(string);
        void CompProgramaPrincipal() throw(string);
        void CompExpressaoLogica();
        void CompTermoRelacional();
        void CompFatorRelacional() throw (string);
        void CompDeclaracaoVariavel() throw(string);
        void CompInicioPrograma() throw(string);
        bool EhIdDeVariavel(string);
        bool EhIdDeProcedimento(string);
        bool EhIdDeFuncao(string);
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
        void CompChamadaDeVariavel()throw(string);
        void CompChamadaDeProcedimento() throw(string);
        void CompChamadaDeFuncao();
        void CompEnquanto();
        void CompFuncao();
		void CompTente() throw(string);
		void CompPegue() throw(string);
        void ExibeErro();
};

#endif // ANALISADORSINTATICO_H_INCLUDED
