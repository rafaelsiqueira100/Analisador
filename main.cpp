#include <iostream>
#include "AnalisadorLexico.h"
#include <exception>
#include "AnalisadorSintatico.h"
//#include "stdafx.h"
int main()
{
    string arquivos[] = {    	    			
    	"CertoSemWrite.pas",
        "Certo.pas",
    	"IdentificadorComecandoComDigito.pas",    	    	
		"ConflitoDeTipo1.pas",
		"ConflitoDeTipo2.pas",
		"ConflitoDeTipo3.pas",
		"FaltaDeDo.pas",
        "FaltaDePontoFinal.pas",
        "FaltaDeThen.pas",
        "FaltaPontoEVirgula1.pas",
        "FaltaPontoEVirgula2.pas",
        "FaltaPontoEVirgula3.pas",        
        "ParentesesDesbalanceados.pas",        
        "IdentificadorNaoDeclarado.pas",
        "PontoEVirgulaAntesDeElse.pas"
    };

    for (int i = 0; i < 15; i++){
    	//if (i > 0)
    	//	cout << endl;
    		
    	cout <<"=============================================================" << endl;

        cout << "Nome do Arquivo : " << arquivos[i] << endl ;

        AnalisadorSintatico a("arquivos/" + arquivos[i]);

        a.CompInicioPrograma();
        /*
        AnalisadorLexico al("arquivos/" + arquivos[i]);
        while(al.temMaisPedacos()){
            cout << "Ver pedaco :" <<AnalisadorLexico::nomeTipo(al.verPedaco())<< endl;
            cout << "Literal :" <<al.getLiteral()<< endl;
            cout << "Linha atual :" <<al.getLinhaAtual()<< endl;
            cout << "Proximo pedaco:" <<AnalisadorLexico::nomeTipo(al.proximoPedaco())<< endl;
            cout << "Literal :" <<al.getLiteral()<< endl;
            cout << "Linha atual :" <<al.getLinhaAtual()<< endl;
        }*/
        
        cout << endl << endl;
        
        if (a.NaoHaErro())
        	cout << "Arquivo compilado com sucesso!";
        else
        	cout << "Erro detectado, compilacao interrompida";
        
        cout << endl <<  "=============================================================";

        cout << endl;               
    }
	
    return 0;
}
