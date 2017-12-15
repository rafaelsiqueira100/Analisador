#include "TabelaDeSimbolos.h"
#include "simbolo.h"
//#include "stdafx.h"
//#include <list>
using namespace std;
TabelaDeSimbolos::TabelaDeSimbolos():armazenador(){}

void TabelaDeSimbolos::guarde(Simbolo* aGuardar){
    int nivel = aGuardar->getNivel();

    list<Simbolo*>::iterator it;
    if(armazenador.empty()){
        armazenador.push_front(aGuardar);
        return;
    }

    for(it=armazenador.begin(); it!=armazenador.end(); ++it){
        if((*(*it)).getNivel() > nivel){
            --it;
            armazenador.insert(it, aGuardar);
            return;
        }
    }

    armazenador.insert(armazenador.end(), aGuardar);
}

void TabelaDeSimbolos::eliminaNivel(int nivel){
    if(!armazenador.empty()){
        list<Simbolo*>::iterator it;
loop:   for(it=armazenador.begin(); it!=armazenador.end(); ++it){

            int nivelAtual = (*it)->getNivel();

            if(nivelAtual >= nivel){
                armazenador.erase(it);
                goto loop;
            }
        }
    }
}

bool TabelaDeSimbolos::encontrar(string nomeSimbolo, Simbolo* retorno){
    list<Simbolo*>::iterator it;
    list<Simbolo*> simbolosEncontrados;

    for (it=armazenador.begin(); it!=armazenador.end(); ++it){
        if (nomeSimbolo == (*(*it)).getNome()){
            *retorno = **it;
            simbolosEncontrados.push_front(retorno);//add no início
        }
    }
        int tamanhoLista = simbolosEncontrados.size();
        if(tamanhoLista==0)
            return false;
        else
            retorno = *(simbolosEncontrados.begin());//retira no início
        for(int i=0;i<tamanhoLista;i++)
            simbolosEncontrados.pop_front();
        return retorno;
}
