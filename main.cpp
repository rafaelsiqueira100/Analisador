#include <iostream>
#include "AnalisadorLexico.h"
#include <exception>
#include "AnalisadorSintatico.h"
#include <string>

int main()
{
    string arquivos[] = {
        "CertoSemWrite.pas",
        "Certo.pas",
        "ConflitoDeTipo1.pas",
        "ConflitoDeTipo2.pas",
        "ConflitoDeTipo3.pas",
        "FaltaDeDo.pas",
        "FaltaDePontoFinal.pas",
        "FaltaDeThen.pas",
        "FaltaPontoEVirgula1.pas",
        "FaltaPontoEVirgula2.pas",
        "FaltaPontoEVirgula3.pas",
        "IdentificadorComecandoComDigito.pas",
        "IdentificadorNaoDeclarado.pas",
        "ParentesesDesbalanceados.pas",
        "PontoEVirgulaAntesDeElse.pas"
    };

    for (int i = 0; i < 14; i++){
    	if (i > 0)
    		cout << endl;
    	
        cout << "Nome do Arquivo : " << arquivos[i] << endl ;

        AnalisadorSintatico a("arquivos/" + arquivos[i]);
        
        a.CompInicioPrograma();
        
        
        cout << endl << endl << "Compilacao terminada";
        
        /*AnalisadorLexico al("arquivos/" + arquivos[i]);
        while(al.temMaisPedacos()){
            cout << "Ver pedaco :" <<AnalisadorLexico::nomeTipo(al.verPedaco())<< endl;
            cout << "Literal :" <<al.getLiteral()<< endl;
            cout << "Linha atual :" <<al.getLinhaAtual()<< endl;
            cout << "Proximo pedaco:" <<AnalisadorLexico::nomeTipo(al.proximoPedaco())<< endl;
            cout << "Literal :" <<al.getLiteral()<< endl;
            cout << "Linha atual :" <<al.getLinhaAtual()<< endl;
        }*/

        cout << endl;
    }

    return 0;
}
