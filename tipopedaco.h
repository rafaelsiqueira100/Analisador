#ifndef TIPOPEDACO_H_INCLUDED
#define TIPOPEDACO_H_INCLUDED

typedef enum
{
    Programa,
    Variavel,
    Comeco,
    Fim,
    Atribuicao,
    Soma,
    Subtracao,
    Multiplicacao,
    Divisao,
    Negacao,
    Maior,
    Menor,
    MaiorOuIgual,
    MenorOuIgual,
    Se,
    Senao,

    Identificador,
    Numero,
    Logico,
    Desconhecido
} TipoPedaco;

#endif // TIPOPEDACO_H_INCLUDED
