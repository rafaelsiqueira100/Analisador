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
"do",
"else",//19
"then",
"mod",
"(",//22
")",//23
"try", //24
"except",//25
";",//26
",",//27
".",//28
":",//29
"integer",//30
"boolean",
"true",
"false",
"and",
"or",
"procedure",
"function"
};

const string* AnalisadorLexico::palavrasChave(palavras_chave);

AnalisadorLexico::AnalisadorLexico(string nomeArquivo):
     arquivo(),
     doisCharLidos(false),
     valorNumeroValido(false),
     numeroGets(0),
     valorNumerico(0),
     valorLiteral("") {
     this->arquivo.open(nomeArquivo.c_str());
}

AnalisadorLexico::~AnalisadorLexico()
{
    this->arquivo.close();
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
    char proxChar = this->arquivo.get();
    this->arquivo.unget();
    while(isspace(proxChar)|| proxChar==EOF){
        proxChar = this->arquivo.get();
        numeroGets++;
        espacos=true;
    }
    if(espacos){
        this->arquivo.unget();//  da próxima palavra
        numeroGets--;
        return true;
    }
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

			return true;
		}
    }
	if (isdigit(palavraEmVetor[tamanhoPalavra-1])) {
		if (isdigit(proxChar)) {

			return false;
		}
		else {

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

			return true;
	}}
	for (indice = 5; indice < NUM_PALAVRAS_CHAVE; indice++) {//se for um dos símbolos independentes, retorna true
		if ((indice>4&&indice < 10) || (indice>18 && indice < 21) || (indice>22 && indice < 26)) {
			if (palavraEmVetor[tamanhoPalavra-1] == palavras_chave[indice].at(0)){

				return true;
				}

		}
	}

	return true;
}

string AnalisadorLexico::proximaPalavra()
{
    string* retorno;

    char palavraEmVetor[1024];
    char letra;
    int tamanhoPalavra = 0;
    char caracAtual;

	while ((!this->fimDaPalavra(palavraEmVetor, tamanhoPalavra))&&caracAtual!=EOF) {

            caracAtual = this->arquivo.get();
            numeroGets++;
            palavraEmVetor[tamanhoPalavra++]=caracAtual;
    }
verif:if (tamanhoPalavra>0) {
		retorno = new string(palavraEmVetor, tamanhoPalavra);
        this->armazenarValor(*retorno);

		return *retorno;
	}
	return "";//DESCONHECIDO
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

}//1234
TipoPedaco AnalisadorLexico::verPedaco(){
    numeroGets=0;
    TipoPedaco retorno  = proximoPedaco();
    int i;
    for(i=0;i<this->numeroGets;i++)
        this->arquivo.unget();
    numeroGets=0;
    /*string palavraLida;
    int lengthPalavraLida = 0;
    char* palavra;
    if(this->valorNumeroValido){
        int numero = this->valorNumerico;

        itoa(numero, palavra, 10);
        while(numero>=10){
            numero = (numero-(numero%10))/10;
            lengthPalavraLida++;
        }
        lengthPalavraLida++;
    }
    else{
        palavraLida = this->getLiteral();
        lengthPalavraLida = palavraLida.length();
        palavra = (char*)palavraLida.c_str();
    }
    char anterior;
    this->arquivo.unget();
    anterior = this->arquivo.get();
    while(isspace(anterior)|| anterior==EOF){
       this->arquivo.unget();
       this->arquivo.unget();
       anterior = this->arquivo.get();
    }//anterior não é espaço
    int  i;

        for(i=0;i<lengthPalavraLida ;i++){
            /*if(palavra[lengthPalavraLida-i-1]!= anterior){
                int j, k;
                for(j=0;j<lengthPalavraLida && palavra[j]!=anterior;j++);
                //j é a posição de anterior no vetor palavra
                for(k=0;k<j;k++){
                    this->arquivo.unget();
                }
                return retorno;
            }

            this->arquivo.unget();
            this->arquivo.unget();
            anterior = this->arquivo.get();
        }
        */
    return retorno;
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
    char atual = this->arquivo.get();
    numeroGets++;
    if(atual==EOF)
        return false;
    else{
        this->arquivo.unget();
        numeroGets--;
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
        case Entao:
        tipoPed="Entao";
        case Resto:
        tipoPed="Resto";
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
