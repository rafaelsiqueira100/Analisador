#include <iostream>
#include "AnalisadorLexico.h"
#include <exception>
#include "Variavel.h"
#include "AnalisadorSintatico.h"
#include "main.h"
//#include "stdafx.h"
int main()
{
    string arquivos[] = {    	    			
    	/*"26-SemIdAposTipoParamProc"/*
		"27-SemVirgulaOu)AposIdParamProc",
		"28-Sem)AposTodosParamProc",
		"29-SemPontoVirgulaAposDecProc",
		"30-ProcComecaSemBegin",
		"31-SemPontoEVirgulaAposChamarProc",
		"32-SemPontoEVirgulaAposChamarFunc",
		"33-SemFechaParentesesAposParamWrite"*/
		/*,
		"16-Certo",
		"17-Certo",
		"18-Certo",
		"19-Certo"
		"20-Certo",
		"21-Certo",
		"22-Certo",
		"23-Certo",
		"24-Certo",
		*/"25-Certo"
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
		/*"34-Parenteses1",
		"35-Parenteses2",
		"36-Parenteses3",
		"37-Parenteses4",
		"38-Parenteses5",
		"39-Parenteses6",
		"40-Parenteses7",
		"41-Parenteses8",
		"42-Parenteses9",
		"43-Parenteses10",
		"44-Parenteses11",
		"45-Parenteses12"
		"51-SemOpLogicoAposOpBoolExprLogica",
		"52-)DemaisAposExprLogica",
		"53-ChamadaVarDesconhecida",
		"54-Sem;AposChamadaVar",
		"55-ChamadaProcDesconhecido",
		"56-Sem(AposChamadaProc",
		"57-Sem,AposParamChamadaProc",
		"58-Sem)AposChamadaProc",
		"59-ChamadaFuncDesconhecida",
		"60-SemAtribuicaoAposChamarMesmaFunc",
		"61-Sem;AposRetornoFunc",
		"62-Sem(AposChamadaFunc",
		"63-Sem,AposChamadaFunc",
		"64-Sem)AposChamadaFunc",
		"65-Sem(AposDecFunc",
		"66-SemIdParamDecFunc",
		"67-Sem,Ou)AposParamDecFunc",
		"68-Sem)AposParamDecFunc",
		"69-SemDoisPontosAposDecFunc",
		"70-SemTipoRetornoDecFunc",
		"71-Sem;AposDecFunc",
		"72-SemBeginAntesLogicaFunc",
		"73-SemRetornoFunc",
		"",
		"",
		"",
		//"51-ArquivoGigante",
		//"52-MuitosTabs",
		//"53-MuitosEspaços",
		//"54-MuitosEnters",
		//"55-ArquivoAposEnd.",
		//"56-IniciaComNumeroTerminaComLetra",
		"57-CaracteresUnicode"*/
		""};
	//const string pasta = "C:/Users/rafae/Downloads/Analisador/arquivos/";
	/*const string pasta = "C:/Temp/Analisador/arquivos";
	int qtos =1;
    for (int i = 0; i < qtos; i++){
    	if (i > 0)
    		cout << endl;
    */		
    	cout <<"=============================================================" << endl;
		/*Simbolo* param = new Simbolo[2];//
		Simbolo p1("param1", 1, SimboloLogico);
		Simbolo p2("param2", 1, SimboloInteiro);
		(param[0]) = p1;
		(param[1]) = p2;*/
		/*Simbolo* simb = new Simbolo("simb1", 0, SimboloLogico);
		Simbolo* simb3 = new Simbolo("simb3", 2, SimboloInteiro);
		TabelaDeSimbolos ts;
		ts.guarde(simb);
		ts.guarde(simb3);
		ts.eliminaNivel(1);*/
		/*cout << "Nome do Arquivo : " << arquivos[i] << endl ;
		*/
		//Metodo m("i", 1,param, -2, SimboloVacuo);
		//m.getParametro(1);
			/*
        AnalisadorSintatico a(pasta+"/" + arquivos[i]+ ".pas");

        a.CompInicioPrograma();
       
        AnalisadorLexico al("C:/Temp/Analisador/arquivos/" + arquivos[i]+".pas");
		while(al.temMaisPedacos()){
            cout << "Ver pedaco :" <<AnalisadorLexico::nomeTipo(al.verPedaco())<< endl;
            cout << "Literal :" <<al.getLiteral()<< endl;
            cout << "Linha atual :" <<al.getLinhaAtual()<< endl;
            cout << "Proximo pedaco:" <<AnalisadorLexico::nomeTipo(al.proximoPedaco())<< endl;
            cout << "Literal :" <<al.getLiteral()<< endl;
            cout << "Linha atual :" <<al.getLinhaAtual()<< endl;
			if (al.getLiteral() == "nada") 
			{
				al.getLiteral();
			}
        }
		cout << "Ver pedaco :" << AnalisadorLexico::nomeTipo(al.verPedaco()) << endl;
		cout << "Literal :" << al.getLiteral() << endl;
		cout << "Linha atual :" << al.getLinhaAtual() << endl;
		cout << "Proximo pedaco:" << AnalisadorLexico::nomeTipo(al.proximoPedaco()) << endl;
		cout << "Literal :" << al.getLiteral() << endl;
		cout << "Linha atual :" << al.getLinhaAtual() << endl;
		
		cout << endl << endl;
        
        if (a.NaoHaErro())
        	cout << "Arquivo compilado com sucesso!";
        else
        	cout << "Erro detectado, compilacao interrompida";
        */
        cout << endl <<  "=============================================================";

        cout << endl;               
    //}
	char x;
	cin >> x;
	
    return 0;
}
