#include<iostream>
#include "analisadorlexico.h"
/*#include<windows.h>
#include "stdafx.h"*/
int main(){
    int indice;
	AnalisadorLexico anaLex("teste.txt");
TipoPedaco pedAtual;
loop:while(anaLex.temMaisPedacos()){
	pedAtual = anaLex.proximoPedaco();
	string tipoPed;
            switch(pedAtual){
            case Programa:
                tipoPed="Programa";
            break;
            case Variavel:
            tipoPed="Variavel";
            break;
            case Comeco:
            tipoPed="Comeco";
            break;
            case Fim:
            tipoPed="Fim";
            break;
            case Atribuicao:
            tipoPed="Atribuicao";
            break;
            case Comparacao:
            tipoPed="Comparacao";
            break;
            case Soma:
            tipoPed="Soma";
            break;
            case Subtracao:
            tipoPed="Subtracao";
            break;
            case Multiplicacao:
            tipoPed="Multiplicacao";
            break;
            case Divisao:
            tipoPed="Divisao";
            break;
            case Negacao:
            tipoPed="Negacao";
            break;
            case Maior:
            tipoPed="Maior";
            break;
            case Menor:
            tipoPed="Menor";
            break;
            case Diferente:
            tipoPed="Diferente";
            break;
            case MaiorOuIgual:
            tipoPed="MaiorOuIgual";
            break;
            case MenorOuIgual:
            tipoPed="MenorOuIgual";
            break;
            case Se:
            tipoPed="Se";
            break;
            case Enquanto:
            tipoPed="Enquanto";
            break;
            case Senao:
            tipoPed="Senao";
            break;
            case AbreParenteses:
            tipoPed="AbreParenteses";
            break;
            case FechaParenteses:
            tipoPed="FechaParenteses";
            break;
            case Tente:
            tipoPed="Tente";
            break;
            case Pegue:
            tipoPed="Pegue";
            break;
            case PontoVirgula:
            tipoPed="PontoVirgula";
            break;
            case Virgula:
            tipoPed="Virgula";
            break;
            case Ponto:
            tipoPed="Ponto";
            break;
            case DoisPontos:
            tipoPed="DoisPontos";
            break;
            case Inteiro:
            tipoPed="Inteiro";
            break;
            case Logico:
            tipoPed="Logico";
            break;
            case Verdadeiro:
            tipoPed="Verdadeiro";
            break;
            case Falso:
            tipoPed="Falso";
            break;
            case E:
            tipoPed="E";
            break;
            case Ou:
            tipoPed="Ou";
            break;
            case Procedimento:
            tipoPed="Procedimento";
            break;
            case Funcao:
            tipoPed="Funcao";
            break;
            case Numero:
            tipoPed="Numero";
            cout<< tipoPed<<'\t'<<anaLex.getNumero()<<"\n";
            break;
            case Identificador:
            tipoPed="Identificador";
            break;
            case Desconhecido:
            tipoPed="Desconhecido";
            break;
            }
            if(tipoPed!="Numero")
            cout << tipoPed <<'\t' <<anaLex.getLiteral()<<"\n";
                goto loop;
        }





	return 0;
}
