#include "analisadorlexico.h"
//using namespace std;
//#include "stdafx.h"
static const string palavras_chave[] =
    {
        "program",
        "var",
        "begin",
        "end",
        ":=", //4
        "=",
        "+",
        "-",
        "*",
        "/",
        "not", //10
        ">",
        "<",
        "<>",
        ">=",
        "<=",
        "if",
        "while",
        "do",
        "else", //19
        "then",
        "mod",
        "(",       //22
        ")",       //23
        "try",     //24
        "except",  //25
        ";",       //26
        ",",       //27
        ".",       //28
		"'",
        ":",       
        "integer", 
        "boolean",
        "true",
        "false",
        "and",
        "or",
        "procedure",
        "function",
		"write"};

const string *AnalisadorLexico::palavrasChave(palavras_chave);

AnalisadorLexico::AnalisadorLexico(string nomeArquivo) : arquivo(),
                                                         doisCharLidos(false),
                                                         valorLiteral(""),
                                                         linhaAtual(1),
                                                         tamanhoVetor(0),
                                                         indiceAtual(0),
                                                         consumiu(false)
{
    this->arquivo.open(nomeArquivo.c_str());
    std::list<TipoPedaco> listaPedacos;
    std::list<int> listaLinhas;
    std::list<string> listaPalavras;
    TipoPedaco prox= Comeco;
    TipoPedaco ant = prox;
	bool iniciando = true;
    while(!acabouLeitura()){
		if (listaLinhas.size() == 104) 
			int n = 0;
        if(ant == Fim)
            int a = 2;
        if(ant == Fim && prox == Ponto)
            goto fora;
        ant = prox;
        prox = this->consuma(iniciando);
		iniciando = false;
        listaPedacos.push_back(prox);
        listaLinhas.push_back(this->linhaAtual);
        listaPalavras.push_back(this->getLiteral());
    }
fora:this->arquivo.close();
    this->tamanhoVetor = listaPedacos.size();
    this->vetorPalavras = new string [this->tamanhoVetor];
    this->vetorLinhas = new string[this->tamanhoVetor];
    this->vetorPedacos = (TipoPedaco*)malloc(this->tamanhoVetor*sizeof(TipoPedaco));
    for(int i=0;i<this->tamanhoVetor;i++){
        *(vetorPalavras+i) = *(listaPalavras.begin());
		char*conversao = (char*)malloc(4 * sizeof(char));
        _itoa_s(*(listaLinhas.begin()),conversao,4 ,10);//
		*(vetorLinhas + i) = conversao;
		free(conversao);
		*(vetorPedacos+i) = *(listaPedacos.begin());
        listaPalavras.pop_front();
        listaPedacos.pop_front();
        listaLinhas.pop_front();
    }
}

AnalisadorLexico::~AnalisadorLexico()
{
   delete [](this->vetorPalavras);
    delete [](this->vetorLinhas);
    delete[](this->vetorPedacos);
}
string AnalisadorLexico::getLinhaAtual()
{
	string retorno;
	
        if(temMaisPedacos()){
            if(consumiu)
                return *(vetorLinhas + indiceAtual -1);
            else
                return *(vetorLinhas + indiceAtual);
        }
        else
            return "Ultima linha";
    
}

bool AnalisadorLexico::armazenarValor(string palavraLida)
{
    int i;
    if(isalnum(*(palavraLida.c_str()))){
        this->valorLiteral = palavraLida;
        return true;
    }
    for (i = 4; i < NUM_PALAVRAS_CHAVE; i++)
    {
        if (palavraLida.compare(palavrasChave[i]) == 0)
        {
            this->valorLiteral = palavraLida;

            return true;
        }
    }
    if (isspace(palavraLida.at(0)))
        return false;
    return false;
}

bool AnalisadorLexico::fimDaPalavra(char *palavraEmVetor, int tamanhoPalavra)
{
    int indice;
    bool espacos = false;
    char proxChar = this->arquivo.get();

    if (proxChar == EOF){
        return true;
    }

    this->arquivo.unget();

    while (isspace(proxChar) || proxChar == EOF)
    {
        if(proxChar=='\n'){
            this->linhaAtual++;
        }
        proxChar = this->arquivo.get();
        espacos = true;
        if(proxChar==EOF){
            return true;
        }

    }
    if (espacos)
    {
        this->arquivo.unget(); //  da pr�xima palavra

        return true;
    }
    if (tamanhoPalavra == 0)
        return false;
    if (isalpha(proxChar) && tamanhoPalavra == 1 && (this->doisCharLidos = false))
        return false;
    else
        this->doisCharLidos = true;
    if (isalpha(palavraEmVetor[tamanhoPalavra - 1]))
    {
        if (isalpha(proxChar) || isdigit(proxChar))
        {

            return false;
        }
        else
        {

            return true;
        }
    }
    if (isdigit(palavraEmVetor[tamanhoPalavra - 1]))
    {
        if (isdigit(proxChar))
        {

            return false;
        }
        else
        {

            return true;
        }
    }
    if (palavraEmVetor[tamanhoPalavra - 1] == '<' || palavraEmVetor[tamanhoPalavra - 1] == '>' || palavraEmVetor[tamanhoPalavra - 1] == ':')
    {
        if (proxChar == '=')
        {

            return false;
        }
        else
        {
            if (palavraEmVetor[tamanhoPalavra - 1] == '<')
            {
                if (proxChar == '>')
                    return false;
            }

            return true;
        }
    }
    for (indice = 5; indice < NUM_PALAVRAS_CHAVE; indice++)
    { //se for um dos s�mbolos independentes, retorna true
        if ((indice > 4 && indice < 10) || (indice > 18 && indice < 21) || (indice > 22 && indice < 26))
        {
            if (palavraEmVetor[tamanhoPalavra - 1] == palavras_chave[indice].at(0))
            {

                return true;
            }
        }
    }

    return true;
}

string AnalisadorLexico::proximaPalavra(bool iniciando)
{
	static bool palavraTerminaLinha;
	static int proxLinha;
    string *retorno;
	if (iniciando) {
		palavraTerminaLinha = false;
		proxLinha = 0;
	}
	if (palavraTerminaLinha && !iniciando) {
		linhaAtual = proxLinha;
		palavraTerminaLinha = false;
	}
    char palavraEmVetor[1024];
    char letra;
    int tamanhoPalavra = 0;
    char caracAtual(0);
	int linhaAnterior = this->linhaAtual;
    while ((!this->fimDaPalavra(palavraEmVetor, tamanhoPalavra)) && caracAtual != EOF)
    {
        caracAtual = this->arquivo.get();

        palavraEmVetor[tamanhoPalavra++] = caracAtual;
    }
	if (this->linhaAtual - linhaAnterior > 1)
		this->linhaAtual--;
	if (linhaAtual != linhaAnterior && caracAtual!=EOF) {
		palavraTerminaLinha = true;
		proxLinha = this->linhaAtual;
		this->linhaAtual = linhaAnterior;
	}

verif:
    if (tamanhoPalavra > 0)
    {
        retorno = new string(palavraEmVetor, tamanhoPalavra);
        this->armazenarValor(*retorno);

        return *retorno;
    }
    return ""; //DESCONHECIDO
}

string AnalisadorLexico::paraMinusculas(string palavra)
{
    if (palavra != "")
    {
        string emMinusculas(palavra);
        int i;

        for (i = 0; i < palavra.size(); i++)
            emMinusculas[i] = tolower(palavra[i]);

        return emMinusculas;
    }
    return "";

} //1234
TipoPedaco AnalisadorLexico::consuma(bool iniciando)
{
    string retorno = AnalisadorLexico::paraMinusculas(this->proximaPalavra(iniciando));
    if (retorno != "")
    {
        string pedaco = (retorno);

        int i;
        string palavraChave;
        for (i = 0; i < NUM_PALAVRAS_CHAVE; i++)
        {
            palavraChave = (palavrasChave[i]);
            if (pedaco.compare(palavraChave) == 0)
                return TipoPedaco(i);
        }
        if (isdigit(pedaco.at(0)))
        {
            return Numero;
        }
        if (isalpha(pedaco.at(0)))
            return Identificador;
    }
    //jogar exce��o
    this->valorLiteral = "";

    return Desconhecido;
}

bool AnalisadorLexico::acabouLeitura()
{
    char c = this->arquivo.get();
    if(c==EOF)
        return true;
    else
        this->arquivo.unget();
    return false;
}

string AnalisadorLexico::nomeTipo(TipoPedaco tp)
{
    string tipoPed;
    switch (tp)
    {
    case Programa:
        tipoPed = "Programa";
        break;
    case Variavel:
        tipoPed = "Variavel";
        break;
    case Comeco:
        tipoPed = "Comeco";
        break;
    case Fim:
        tipoPed = "Fim";
        break;
    case Atribuicao:
        tipoPed = "Atribuicao";
        break;
    case Comparacao:
        tipoPed = "Comparacao";
        break;
    case Soma:
        tipoPed = "Soma";
        break;
    case Subtracao:
        tipoPed = "Subtracao";
        break;
    case Multiplicacao:
        tipoPed = "Multiplicacao";
        break;
    case Divisao:
        tipoPed = "Divisao";
        break;
    case Negacao:
        tipoPed = "Negacao";
        break;
    case Maior:
        tipoPed = "Maior";
        break;
    case Menor:
        tipoPed = "Menor";
        break;
    case Diferente:
        tipoPed = "Diferente";
        break;
    case MaiorOuIgual:
        tipoPed = "MaiorOuIgual";
        break;
    case MenorOuIgual:
        tipoPed = "MenorOuIgual";
        break;
    case Se:
        tipoPed = "Se";
        break;
    case Entao:
        tipoPed = "Entao";
    case Resto:
        tipoPed = "Resto";
        break;
    case Enquanto:
        tipoPed = "Enquanto";
        break;
    case Faca:
        tipoPed = "Faca";
        break;
    case Senao:
        tipoPed = "Senao";
        break;
    case AbreParenteses:
        tipoPed = "AbreParenteses";
        break;
    case FechaParenteses:
        tipoPed = "FechaParenteses";
        break;
    case Tente:
        tipoPed = "Tente";
        break;
    case Pegue:
        tipoPed = "Pegue";
        break;
    case PontoVirgula:
        tipoPed = "PontoVirgula";
        break;
    case Virgula:
        tipoPed = "Virgula";
        break;
    case Ponto:
        tipoPed = "Ponto";
        break;
    case DoisPontos:
        tipoPed = "DoisPontos";
        break;
    case Inteiro:
        tipoPed = "Inteiro";
        break;
    case Logico:
        tipoPed = "Logico";
        break;
    case Verdadeiro:
        tipoPed = "Verdadeiro";
        break;
    case Falso:
        tipoPed = "Falso";
        break;
    case E:
        tipoPed = "E";
        break;
    case Ou:
        tipoPed = "Ou";
        break;
    case Procedimento:
        tipoPed = "Procedimento";
        break;
    case Funcao:
        tipoPed = "Funcao";
        break;
    case Numero:
        tipoPed = "Numero";
        break;
    case Identificador:
        tipoPed = "Identificador";
        break;
    case Desconhecido:
        tipoPed = "Desconhecido";
        break;
    }
    return tipoPed;
}

string AnalisadorLexico::getLiteral()
{
   if(this->tamanhoVetor==0)
    return this->valorLiteral;
    else{
            if(temMaisPedacos()){
                if(!consumiu)
                    return *(vetorPalavras+indiceAtual);
                else
                    return *(vetorPalavras+indiceAtual-1);
            }
            else
                return "nada";
    }
}

bool AnalisadorLexico::temMaisPedacos(){
    return (this->indiceAtual<this->tamanhoVetor);
}
TipoPedaco AnalisadorLexico::proximoPedaco(){
    if(temMaisPedacos()){
    this->indiceAtual++;
    consumiu = true;
    return *(this->vetorPedacos +indiceAtual -1 );}
    else{
        return Nulo;
    }
}
TipoPedaco AnalisadorLexico::verPedaco(){
    if(temMaisPedacos()){
        consumiu = false;
        return *(this->vetorPedacos +indiceAtual);
    }
    else
        return Nulo;

}
