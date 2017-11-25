#include "TabelaDeSimbolos.h"
#include "simbolo.h"
#include <list>
using namespace std;
TabelaDeSimbolos::TabelaDeSimbolos(){
//armazenador();
}

void TabelaDeSimbolos::guarde(Simbolo* aGuardar){
int nivel = aGuardar->getNivel();
list<Simbolo*>::iterator it;
if(armazenador.empty()){
armazenador.push_front(aGuardar);
return;
}

for(it=armazenador.begin();it!=armazenador.end();++it){
if((*(*it)).getNivel()>nivel){
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

for(it=armazenador.begin();it!=armazenador.end();++it){
	while((*(*it)).getNivel()==nivel){
		armazenador.erase(it);
		it++;
		if((*(*it)).getNivel()!=nivel)
			return;
	}
}//fim do for
armazenador.erase(armazenador.end());
}//fim do if
//lançar exceção
}
