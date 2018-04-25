#include <iostream>
#include "AnalisadorLexico.h"
#include <exception>
#include "AnalisadorSintatico.h"
//#include "stdafx.h"
int main()
{
    string arquivos[] = {    	    			
    	"1-NaoComecaComProgram",
        "2-ProgramaSemId",
    	"3-ProgramaComecaSemBegin",    	    	
		"4-ProcedimentoSemId",
		"5-ProcSemParenteses",
		"6-WriteSemParenteses",
		"7-TrySemExcept",
		"8-BeginSemEnd",
		"9-SemIdAposVar",

		"10-CharAposIdDecVar",

		"11-AlfanumAposVirgulaDecVar",
		"12-ComandoAposVirgulaDecVar",
        "13-DecVarNaoIntNemBool",
        "14-FuncSemId"
		/*"15-Certo",
		"16-Certo",
		"17-Certo"*/
	};
	const string pasta = "C:/Users/rafae/Downloads/Analisador/arquivos/";
	int qtos = 14;
    for (int i = 0; i < qtos; i++){
    	//if (i > 0)
    	//	cout << endl;
    		
    	cout <<"=============================================================" << endl;

        cout << "Nome do Arquivo : " << arquivos[i] << endl ;

        AnalisadorSintatico a(pasta+"/" + arquivos[i]+ ".pas");

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
	char x;
	cin >> x;
	
    return 0;
}
