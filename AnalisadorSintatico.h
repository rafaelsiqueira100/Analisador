#ifndef ANALISADORSINTATICO_H_INCLUDED
#define ANALISADORSINTATICO_H_INCLUDED
#include "TabelaDeSimbolos.h"
#include "analisadorlexico.h"
#include "tipopedaco.h"
#include "simbolo.h"
#include "metodo.h"
#include <typeindex>
#include <typeinfo>
#include <exception>
#include "Variavel.h";
using namespace std;

class AnalisadorSintatico
{
  private:
    TabelaDeSimbolos tabela;
    AnalisadorLexico *anaLex;
    int nivelAtual;
    string nomeFuncAtual;
    bool retornoFuncInt;
    bool jaRetornou;
    string erro;

  public:
    AnalisadorSintatico();
    AnalisadorSintatico(string);
    ~AnalisadorSintatico();
    void CompComandoComposto() throw();
    void CompProcedimento() throw();
    void CompComando() throw();
    void CompSe() throw();
    void CompExpressaoAritimetica() throw();
    void CompTermo() throw();
    void CompExpressaoRelacional() throw();
    void CompFator() throw();
    void CompProgramaPrincipal() throw();
    void CompExpressaoLogica() throw();
    void CompTermoRelacional() throw();
    void CompFatorRelacional() throw();
    void CompDeclaracaoVariavel() throw();
    void CompInicioPrograma() throw();
    bool EhIdDeVariavel(string) throw();
    bool EhIdDeProcedimento(string) throw();
    bool EhIdDeFuncao(string) throw();
    bool EhMaisOuMenos(TipoPedaco) throw();
    bool EhVezesOuDividir(TipoPedaco) throw();
    bool EhVezesOuDividirOuResto(TipoPedaco) throw();
    bool EhFuncao(Simbolo) throw();
    bool FuncaoRetornaInteiro(Simbolo) throw();
    bool FuncaoRetornaBool(Simbolo) throw();
    bool EhVariavel(Simbolo) throw();
    bool EhInteiro(Simbolo) throw();
    bool EhOperadorRelacional(TipoPedaco) throw();
    bool EhBool(Simbolo) throw();
    bool EhValorLogico(TipoPedaco) throw();
    void CompChamadaDeVariavel() throw();
    void CompChamadaDeProcedimento() throw();
    void CompChamadaDeFuncao() throw();
    void CompEnquanto() throw();
    void CompFuncao() throw();
    void CompTente() throw();
    void CompPegue() throw();
    //string GetErro() const throw() ;
    //void ExibeErro()  ;
};

#endif // ANALISADORSINTATICO_H_INCLUDED
