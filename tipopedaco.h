#ifndef TIPOPEDACO_H_INCLUDED
#define TIPOPEDACO_H_INCLUDED

typedef enum
{
    Programa,
    Variavel,
    Comeco,
    Fim,
    Atribuicao,
    Comparacao, //igual
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
    Enquanto,
    Senao,
    AbreParenteses,
    FechaParenteses,
    Tente,
    Pegue,
    Virgula,
    PontoVirgula,
    Ponto

    Identificador,
    Numero,
    Logico,
    Desconhecido
} TipoPedaco;

#endif // TIPOPEDACO_H_INCLUDED
