#ifndef ANALISADORSINTATICO_H_INCLUDED
#define ANALISADORSINTATICO_H_INCLUDED

#include "analisadorlexico.h"
using namespace std;

class AnalisadorSintatico
{
    private:
        AnalisadorLexico* anaLex;

    public:
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
};

#endif // ANALISADORSINTATICO_H_INCLUDED
