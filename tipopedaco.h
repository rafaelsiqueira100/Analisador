#ifndef TIPOPEDACO_H_INCLUDED
#define TIPOPEDACO_H_INCLUDED

typedef enum
{
    Programa,
    Variavel,
    Comeco,
    Fim,
    Atribuicao, // :=
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
    Senao,
    AbreParenteses,
    FechaParenteses,
    Tente,
    Pegue,
    Virgula,
    PontoVirgula,
    Ponto,
	DoisPontos,
	Inteiro,
	Logico,
	Verdadeiro,
	Falso,
	Procedimento,
	Funcao,
	Numero,
    Identificador,//possível identificador(uma string alfanumérico)
    Desconhecido
} TipoPedaco;

#endif // TIPOPEDACO_H_INCLUDED
