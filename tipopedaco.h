#ifndef TIPOPEDACO_H_INCLUDED
#define TIPOPEDACO_H_INCLUDED

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
    Senao,//18
    AbreParenteses,
    FechaParenteses,
    Tente,
    Pegue,
    PontoVirgula,//23
    Virgula,//24
    Ponto,
	DoisPontos,
	Inteiro,
	Logico,
	Verdadeiro,
	Falso,
	E,
	Ou,
	Procedimento,
	Funcao,
	Numero,
    Identificador,//possível identificador(uma string alfanumérico)
    Desconhecido
} TipoPedaco;

#endif // TIPOPEDACO_H_INCLUDED
