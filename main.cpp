#include <iostream>
#include "AnalisadorLexico.h"
#include <exception>
#include "AnalisadorSintatico.h"
//#include "stdafx.h"
int main()
{
    string arquivos[] = {    	    			
    	"26-SemIdAposTipoParamProc",
		"27-SemVirgulaOu)AposIdParamProc",
		"28-Sem)AposTodosParamProc",
		"29-SemPontoVirgulaAposDecProc",
		"30-ProcComecaSemBegin",
		"31-SemPontoEVirgulaAposChamarProc",
		"32-SemPontoEVirgulaAposChamarFunc",
		"33-SemFechaParentesesAposParamWrite"
		/*,
		"16-Certo",
		"17-Certo",
		"18-Certo",
		"19-Certo"*/
		
		/*"2-ProgramaSemId",
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
        "14-FuncSemId"*/
		};
	//const string pasta = "C:/Users/rafae/Downloads/Analisador/arquivos/";
	const string pasta = "C:/Temp/Analisador-master/arquivos/";
	int qtos =8;
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
