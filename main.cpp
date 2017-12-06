#include<iostream>
#include "AnalisadorLexico.h"
#include "AnalisadorSintatico.h"

int main(){
    try {
        AnalisadorSintatico a("teste.txt");
        a.CompInicioPrograma();
    } catch(char* s) {
        cout << s;
    }
}
