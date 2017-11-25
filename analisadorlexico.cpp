#include "analisadorlexico.h"

using namespace std;
static const string palavras_chave[] =
{"program",
"var",
"begin",
"end",
":=",//4
"=",
"+",
"-",
"*",
"/",
"not",//10
">",
"<",
"<>",
">=",
"<=",
"if",
"while",
"else",//18
"(",//19
")",//20
"try", //21
"except",//22
";",//23
",",//24
".",//25
":",//26
"integer",//27
"boolean",
"true",
"false",
"and",
"or",
"procedure",
"function"
};

const string* AnalisadorLexico::palavrasChave = palavras_chave;

AnalisadorLexico::AnalisadorLexico(string nomeArquivo)
{
    (this->arquivo)= new ifstream();
    this->arquivo->open(nomeArquivo.c_str());
    this->doisCharLidos=false;
    this->valorNumeroValido = false;
}

AnalisadorLexico::~AnalisadorLexico()
{
    this->arquivo->close();
}

bool AnalisadorLexico::armazenarValor(string palavraLida)
{
    int i;
    bool ehNumero = true;

    if (isalpha(palavraLida.at(0)))
    {
        this->valorNumeroValido = false;
        this->valorLiteral = palavraLida;
        return true;
    }

    for (i = 0; i < palavraLida.size(); i++)
        if (!isdigit(palavraLida.at(i)))
            ehNumero = false;

    if (ehNumero)
    {
        this->valorNumeroValido  =true;
        this->valorNumerico = atoi(palavraLida.c_str());
        this->valorLiteral = "";
        return true;
    }
    char primeiro ;
	for (i = 4; i < NUM_PALAVRAS_CHAVE; i++){
		if (palavraLida.compare(palavrasChave[i])==0){
                this->valorLiteral = palavraLida;
                this->valorNumeroValido = false;
			return true;
        }
	}
	if (isspace(palavraLida.at(0)))
		return false;
    return false;
}

bool AnalisadorLexico::fimDaPalavra(char* palavraEmVetor, int tamanhoPalavra)
{
	int indice;
    bool espacos = false;
    char proxChar = this->arquivo->get();
    this->arquivo->unget();

    while(isspace(proxChar)|| proxChar==EOF){
            this->lengthUltimaLeitura++;//é espaço
        if(proxChar==EOF){
                this->arquivo->get();

                return true;
        }
        proxChar = this->arquivo->get();
        espacos=true;
    }
    if(espacos){
        this->lengthUltimaLeitura--;//decrementando pq ele leu o primeiro char
            this->arquivo->unget();//  da próxima palavra
        return true;
    }
        this->lengthUltimaLeitura++;//não é espaço

    if(tamanhoPalavra==0)
        return false;
    if(isalpha(proxChar)&&tamanhoPalavra==1&&(this->doisCharLidos= false))
        return false;
        else
            this->doisCharLidos = true;
    if(isalpha(palavraEmVetor[tamanhoPalavra-1]))
    {
		if (isalpha(proxChar) || isdigit(proxChar)) {

			return false;
		}
		else {
            this->lengthUltimaLeitura--;
			return true;
		}
    }
	if (isdigit(palavraEmVetor[tamanhoPalavra-1])) {
		if (isdigit(proxChar)) {

			return false;
		}
		else {
            this->lengthUltimaLeitura--;
			return true;
		}
	}
	if (palavraEmVetor[tamanhoPalavra-1] == '<' || palavraEmVetor[tamanhoPalavra-1] == '>'
		|| palavraEmVetor[tamanhoPalavra-1] == ':') {
		if (proxChar == '=') {

			return false;
		}
		else{
                if(palavraEmVetor[tamanhoPalavra-1]=='<'){
                    if(proxChar=='>')
                        return false;
                }
                this->lengthUltimaLeitura--;
			return true;
	}}
	for (indice = 5; indice < NUM_PALAVRAS_CHAVE; indice++) {//se for um dos símbolos independentes, retorna true
		if ((indice>4&&indice < 10) || (indice>18 && indice < 21) || (indice>22 && indice < 26)) {
			if (palavraEmVetor[tamanhoPalavra-1] == palavras_chave[indice].at(0)){
				this->lengthUltimaLeitura--;
				return true;
				}

		}
	}
	this->lengthUltimaLeitura--;
	return true;
}

string AnalisadorLexico::proximaPalavra()
{
    string* retorno;

    char palavraEmVetor[1024];
    char letra;
    int tamanhoPalavra = 0;
    char caracAtual;
    this->lengthUltimaLeitura = 0;
	while ((!this->fimDaPalavra(palavraEmVetor, tamanhoPalavra))&&caracAtual!=EOF) {
            caracAtual = this->arquivo->get();
    if(caracAtual!=EOF)
		palavraEmVetor[tamanhoPalavra++] = caracAtual;
    else{
        this->arquivo->get();
	}}
verif:if (tamanhoPalavra>0) {
		retorno = new string(palavraEmVetor, tamanhoPalavra);
        this->armazenarValor(*retorno);

		return *retorno;
	}
	return "";
}

string AnalisadorLexico::paraMinusculas(string palavra)
{
	if (palavra != "") {
		string emMinusculas(palavra);
		int i;

		for (i = 0; i < palavra.size(); i++)
			emMinusculas[i] = tolower(palavra[i]);

		return emMinusculas;
	}
	return "";

}
TipoPedaco AnalisadorLexico::verPedaco(){
    TipoPedaco retorno  = proximoPedaco();

    for (int i = 0; i < this->lengthUltimaLeitura; i++){
        this->arquivo->unget();
    }

    return retorno;
}

int AnalisadorLexico::getLengthUltimoPedaco(){
    return this->lengthUltimaLeitura;
}

TipoPedaco AnalisadorLexico::proximoPedaco()
{
	string retorno = AnalisadorLexico::paraMinusculas(this->proximaPalavra());
		if (retorno != "") {
			string pedaco = (retorno);

			int i;
            string palavraChave;
			for (i = 0; i < NUM_PALAVRAS_CHAVE; i++){
                    palavraChave=(palavrasChave[i]);
				if (pedaco.compare(palavraChave)==0)
					return TipoPedaco(i);}
			int numero;
			sscanf(pedaco.c_str(), "%i", &numero);
			if ((this->valorNumerico == numero)&&this->valorNumeroValido ){
				return Numero;
			}
        if(isalpha(pedaco.at(0)))
            return Identificador;

		}
//jogar exceção
this->valorLiteral= "";
this->valorNumeroValido = false;
return Desconhecido;
}

char AnalisadorLexico::temMaisPedacos()
{
    char atual = this->arquivo->get();
    if(atual==EOF)
        return false;
    else{
        this->arquivo->unget();
        return true;
    }
}

string AnalisadorLexico::nomeTipo(TipoPedaco tp){
    string tipoPed;
    switch(tp){
        case Programa:
            tipoPed="Programa";
        break;
        case Variavel:
        tipoPed="Variavel";
        break;
        case Comeco:
        tipoPed="Comeco";
        break;
        case Fim:
        tipoPed="Fim";
        break;
        case Atribuicao:
        tipoPed="Atribuicao";
        break;
        case Comparacao:
        tipoPed="Comparacao";
        break;
        case Soma:
        tipoPed="Soma";
        break;
        case Subtracao:
        tipoPed="Subtracao";
        break;
        case Multiplicacao:
        tipoPed="Multiplicacao";
        break;
        case Divisao:
        tipoPed="Divisao";
        break;
        case Negacao:
        tipoPed="Negacao";
        break;
        case Maior:
        tipoPed="Maior";
        break;
        case Menor:
        tipoPed="Menor";
        break;
        case Diferente:
        tipoPed="Diferente";
        break;
        case MaiorOuIgual:
        tipoPed="MaiorOuIgual";
        break;
        case MenorOuIgual:
        tipoPed="MenorOuIgual";
        break;
        case Se:
        tipoPed="Se";
        break;
        case Enquanto:
        tipoPed="Enquanto";
        break;
        case Senao:
        tipoPed="Senao";
        break;
        case AbreParenteses:
        tipoPed="AbreParenteses";
        break;
        case FechaParenteses:
        tipoPed="FechaParenteses";
        break;
        case Tente:
        tipoPed="Tente";
        break;
        case Pegue:
        tipoPed="Pegue";
        break;
        case PontoVirgula:
        tipoPed="PontoVirgula";
        break;
        case Virgula:
        tipoPed="Virgula";
        break;
        case Ponto:
        tipoPed="Ponto";
        break;
        case DoisPontos:
        tipoPed="DoisPontos";
        break;
        case Inteiro:
        tipoPed="Inteiro";
        break;
        case Logico:
        tipoPed="Logico";
        break;
        case Verdadeiro:
        tipoPed="Verdadeiro";
        break;
        case Falso:
        tipoPed="Falso";
        break;
        case E:
        tipoPed="E";
        break;
        case Ou:
        tipoPed="Ou";
        break;
        case Procedimento:
        tipoPed="Procedimento";
        break;
        case Funcao:
        tipoPed="Funcao";
        break;
        case Numero:
        tipoPed="Numero";
        break;
        case Identificador:
        tipoPed="Identificador";
        break;
        case Desconhecido:
        tipoPed="Desconhecido";
        break;
        }
        return tipoPed;
}


string AnalisadorLexico::getLiteral()
{
    //if(this->valorLiteral !="")
    return this->valorLiteral;
    //throw exception
}

int AnalisadorLexico::getNumero()
{
    //if(this->valorNumeroValido)
    return this->valorNumerico;
    //throw exception
}
