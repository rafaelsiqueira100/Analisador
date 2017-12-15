#ifndef TIPOPEDACO_H_INCLUDED
#define TIPOPEDACO_H_INCLUDED
//#include "stdafx.h"
typedef enum
{
    Programa,
    Variavel,
    Comeco,
    Fim,
    Atribuicao, // 4
    Comparacao, //  =
    Soma,
    Subtracao,
    Multiplicacao,
    Divisao,
    Negacao,
    Maior,
    Menor,
	Diferente,
    MaiorOuIgual,
    MenorOuIgual,
    Se,
    Enquanto,
    Faca,
    Senao,//18
    Entao,
    Resto,
    AbreParenteses,
    FechaParenteses,
    Tente,
    Pegue,
    PontoVirgula,//23
    Virgula,//24
    Ponto,
	Aspa,
	DoisPontos,
	Inteiro,
	Logico,
	Verdadeiro,
	Falso,
	E,
	Ou,
	Procedimento,
	Funcao,
	Escreva,
	Numero,
    Identificador,//possív el identificador(uma string alfanumérico)
    Desconhecido,
    Nulo
} TipoPedaco;

#endif // TIPOPEDACO_H_INCLUDED
