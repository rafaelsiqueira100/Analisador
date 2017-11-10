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
    if(proxChar==EOF){
            this->arquivo->get();
    return true;}
        proxChar = this->arquivo->get();
    espacos=true;
    }
    if(espacos){
            this->arquivo->unget();
        return true;}

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
			if (palavraEmVetor[tamanhoPalavra-1] == palavras_chave[indice].at(0))
				return true;
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
			if (this->valorNumerico == numero) {
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
