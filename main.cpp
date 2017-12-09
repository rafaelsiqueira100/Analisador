#include <iostream>
#include "AnalisadorLexico.h"
#include <exception>
#include "AnalisadorSintatico.h"

int main()
{
    string arquivos[] = {
        "Certo.pas",
        "ConflitoDeTipo1.pas",
        "ConflitoDeTipo2.pas",
        "ConflitoDeTipo3.pas",
        "FaltaDeDo.pas",
        "FaltaDePontoFinal.pas",
        "FaltaDeThen.pas",
        "FaltaPontoEVigula1.pas",
        "FaltaPontoEVigula2.pas",
        "FaltaPontoEVigula3.pas",
        "IdentificadorComecandoComDigito.pas",
        "IdentificadorNaoDeclarado.pas",
        "ParentesesDesvalanceados.pas",
        "PontoEVirgulaAntesDeElse.pas"
    };

    for (int i = 0; i < 14; i++){
        cout << "Nome do Arquivo : " << arquivos[i] << endl ;

        AnalisadorSintatico a("arquivos/" + arquivos[i]);
        a.CompInicioPrograma();

        cout << endl << endl ;
    }

    return 0;
}
