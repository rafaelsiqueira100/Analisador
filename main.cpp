#include <iostream>
#include "AnalisadorLexico.h"
#include <exception>
#include "AnalisadorSintatico.h"

int main()
{
    AnalisadorSintatico a("teste3.txt");
    a.CompInicioPrograma();

    return 0;
}
