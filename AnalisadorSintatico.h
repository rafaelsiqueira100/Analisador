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
        int nivelAtual = 0;

    public:
        AnalisadorSintatico();
        AnalisadorSintatico(string);
        ~AnalisadorSintatico();
        void CompComandoComposto();
        void CompProcedimento();
        void CompComando();
        void CompSe();
        void CompExpressaoAritimetica();
        void CompTermo();
        void CompExpressaoRelacional();
        void CompFator();
        void CompProgramaPrincipal();
        void CompExpressaoLogica();
        void CompTermoRelacional();
        void CompFatorRelacional();
        void CompDeclaracaoVariavel();
        void CompInicioPrograma();
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
        void CompChamadaDeVariavel();
        void CompChamadaDeProcedimento();
        void CompChamadaDeFuncao();
        void CompEnquanto();
        void CompFuncao();

};

#endif // ANALISADORSINTATICO_H_INCLUDED
