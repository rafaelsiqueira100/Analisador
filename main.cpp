#include<iostream>
#include "analisadorlexico.h"
/*#include<windows.h>
#include "stdafx.h"*/
int main(){
    int indice;
	AnalisadorLexico anaLex("teste.txt");
    TipoPedaco pedAtual;
loop:while(anaLex.temMaisPedacos()){
        pedAtual = anaLex.verPedaco();
        string tipoPed = AnalisadorLexico::nomeTipo(pedAtual);
        if (tipoPed=="Numero"){
            cout << anaLex.getNumero() << "\n";
        }
        else if(tipoPed!="Numero"){
                if(tipoPed=="Pegue"){
                        char x;
                cin >> x;
                }

            cout << tipoPed <<'\t' <<anaLex.getLiteral()<<"\n";
        }

        pedAtual = anaLex.proximoPedaco();
        tipoPed = AnalisadorLexico::nomeTipo(pedAtual);

                if (tipoPed=="Numero"){
            cout << anaLex.getNumero() << "\n";
        }
        else if(tipoPed!="Numero"){
            cout << tipoPed <<'\t' <<anaLex.getLiteral()<<"\n";
        }

        cout << anaLex.getLengthUltimoPedaco() << "\n";
        goto loop;
        }
    char c;
    cin >> c;
	return 0;
}
