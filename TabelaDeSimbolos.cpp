#include "TabelaDeSimbolos.h"
#include "simbolo.h"
#include <list>
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

    for (it=armazenador.begin(); it!=armazenador.end(); ++it){
        if (nomeSimbolo == (*(*it)).getNome()){
            *retorno = **it;
            return true;
        }}
        return false;

}
