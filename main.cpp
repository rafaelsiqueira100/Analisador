#include "tipopedaco.h"
#include "analisadorlexico.cpp"
#include <iostream>
int main(){
    int indice;
AnalisadorLexico anaLex("E:\\AnaLexTeste\\teste.txt");
TipoPedaco pedAtual;
loop:while(anaLex.temMaisPedacos()){
	pedAtual = anaLex.proximoPedaco();
for(indice=0;indice<36;indice++){
        if(pedAtual==TipoPedaco(indice)){
            if(TipoPedaco(indice)==Numero)
            cout << "Número:" << anaLex.getNumero();
            else
            cout << "Literal:" << indice<<anaLex.getLiteral();
                goto loop;
        }

	}


	}
	return 0;
}
