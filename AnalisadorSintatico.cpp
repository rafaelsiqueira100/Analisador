#include <iostream>
#include "AnalisadorSintatico.h"

void AnalisadorSintatico::ExibeErro(void)
{
    cout << this->erro;
}

AnalisadorSintatico::AnalisadorSintatico(string nomeArquivo):
    anaLex(new AnalisadorLexico(nomeArquivo)),
    nivelAtual(0),
    nomeFuncAtual(""),
    retornoFuncInt(false),
    jaRetornou(false),
    erro("")
{
    set_terminate(ExibeErro);
}


AnalisadorSintatico::~AnalisadorSintatico()
{
    delete (this->anaLex);
}

void AnalisadorSintatico::CompProgramaPrincipal()throw(string){
     TipoPedaco prox = anaLex->proximoPedaco();
     if(prox!=Programa)
     {
         this->erro = "Programa esperado";

         throw "Programa esperado";
     }

    prox = anaLex->proximoPedaco();
     if(prox!=Identificador)
     {
         this->erro = "Identificador esperado";

         throw "Identificador esperado";
     }

    prox = anaLex->proximoPedaco();
    if(prox!=PontoVirgula)
    {
        this->erro = "Ponto e Vírgula esperado";

        throw "Ponto e Vírgula esperado";
    }

    prox = anaLex->verPedaco();
    while(prox==Variavel){
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }
    if(prox==Procedimento)
        CompProcedimento();
    if(prox==Funcao)
        CompFuncao();
    prox = anaLex->verPedaco();
    if(prox!= Comeco)
    {
        this->erro = "Início inesperado";

        throw "Início inesperado";
    }

    CompComandoComposto();//COMPILA INÍCIO E FIM

}
void AnalisadorSintatico::CompInicioPrograma() throw(string){
    CompProgramaPrincipal();
    if(anaLex->proximoPedaco()!=Ponto)
    {
        this->erro = "Ponto esperado";

        throw "Ponto esperado";
    }
}
void AnalisadorSintatico::CompProcedimento()throw(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Procedimento){
        this->erro = "Procedimento esperado";

        throw "Procedimento esperado";
    }
    prox = anaLex->proximoPedaco();

    if (prox != Identificador){
        this->erro = "Identificador esperado";

        throw "Identificador esperado";
    }
    string nomeProc = anaLex->getLiteral();
    std::list<Simbolo> listaParametros;
    /*std::list<Simbolo>::iterator it;
    it = listaParametros.begin();*/
	int tamanhoLista = 0;
	prox = anaLex->proximoPedaco();
    if (prox != AbreParenteses){
        this->erro = "Abre Parênteses esperado";

        throw "Abre Parênteses esperado";
    }

    prox = anaLex->verPedaco();
    while(prox == Inteiro || prox == Logico){
        TipoPedaco tipoParametro = prox;
        TipoRetorno retornoParametro;

        switch(tipoParametro){
            case Inteiro:
                retornoParametro = SimboloInteiro;
            case Logico:
                retornoParametro = SimboloLogico;
        }

        anaLex->proximoPedaco();
        prox = anaLex->proximoPedaco();
        if(prox != Identificador)
        {
            this->erro = "Identificador esperado !";

            throw "Identificador esperado !";
        }

        Simbolo param (anaLex->getLiteral(), this->nivelAtual, retornoParametro);
		tamanhoLista++;

		listaParametros.push_back(param);
        prox = anaLex->verPedaco();
        switch(prox){
            case FechaParenteses:
            goto foraLoop;
            break;
            case Virgula:
            anaLex->proximoPedaco();
            break;
            default:
                this->erro = "Vírgula ou Fecha Parênteses esperado!";

                throw "Vírgula ou Fecha Parênteses esperado!";
        }
        prox = anaLex->verPedaco();

    }//fim do while
foraLoop:prox = anaLex->proximoPedaco();
	 Simbolo* vetor = new Simbolo[tamanhoLista];
	 int i;
	 for(i=0;i<tamanhoLista;i++){
        *(vetor+i) = listaParametros.front();
        listaParametros.pop_front();
        }
    Metodo* procedimento = new Metodo( nomeProc, this->nivelAtual,vetor, tamanhoLista, SimboloVacuo );
    if(prox !=FechaParenteses)
    {
        this->erro = "Fecha Parênteses esperado !";

        throw "Fecha Parênteses esperado !";
    }

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula){
        this->erro = "Ponto e virgula esperado";

        throw "Ponto e virgula esperado";
    }

	this->tabela.guarde(procedimento);
    prox = anaLex->verPedaco();
    while (prox == Variavel){
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }
    //loop da main
    if(prox==Procedimento)
        CompProcedimento();
    if(prox==Funcao)
        CompFuncao();
    prox = anaLex->verPedaco();
    if(prox!=Comeco)
        throw "Início esperado !";
    CompComandoComposto();

    /*prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula){
        throw "ponto e virgula esperado";
    }*/
}
// E função??
void AnalisadorSintatico::CompComando()throw(string){
    TipoPedaco prox = anaLex->verPedaco();
    if (prox == Identificador){
        string nomeId = anaLex->getLiteral();
        if (EhIdDeVariavel(nomeId)){
            CompChamadaDeVariavel();
        }
        else if (EhIdDeProcedimento(nomeId)){
            CompChamadaDeProcedimento();
			if (anaLex->proximoPedaco() != PontoVirgula)
            {
                this->erro = "Ponto e vírgula esperado";

                throw "Ponto e vírgula esperado";
            }
        }
        else if(EhIdDeFuncao(nomeId)){
            CompChamadaDeFuncao();
			if (anaLex->proximoPedaco() != PontoVirgula)
            {
                this->erro = "Ponto e vírgula esperado";

                throw "Ponto e vírgula esperado";
            }
        }

    }
    else{
		switch (prox)
		{
			case Se:
				CompSe();
			break;
			case Enquanto:
				CompEnquanto();
			break;
			case  Tente:
				CompTente();
			break;
			case Pegue:
				CompPegue();
			break;
		}

    }
}
void AnalisadorSintatico::CompPegue()throw(string){
	TipoPedaco prox = anaLex->proximoPedaco();
	if (prox != Pegue) {
        this->erro = "Except esperado !";

		throw "Except esperado !";
	}

	prox = anaLex->verPedaco();
	if (prox == Comeco) {
		CompComandoComposto();
	}
	else {
		CompComando();
	}
}
void AnalisadorSintatico::CompTente()throw(string) {
	TipoPedaco prox = anaLex->proximoPedaco();
	if (prox != Tente) {
        this->erro = throw "Try esperado !";

		throw "Try esperado !";
	}
	prox = anaLex->verPedaco();
	if (prox == Comeco) {
		CompComandoComposto();
	}
	else {
		CompComando();
	}
}
void AnalisadorSintatico::CompSe()throw(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Se){
        this->erro = "if esperado";

        throw "if esperado";
    }

    CompExpressaoLogica();

    prox = anaLex->proximoPedaco();
    if (prox != Entao){
        this->erro = "Then esperado";

        throw "Then esperado";
    }

    prox = anaLex->verPedaco();
	if (prox == Comeco) {
		CompComandoComposto();
	}
	else {
		CompComando();
	}
	if (anaLex->verPedaco() == Senao) {
		anaLex->proximoPedaco();
		if (prox == Comeco) {
			CompComandoComposto();
		}
		else {
			CompComando();
		}

	}

    /*prox = anaLex->proximoPedaco();
    if (prox == PontoVirgula){prox = anaLex->proximoPedaco();
    if(prox !=FechaParenteses)
            throw "Fecha Parênteses esperado !";
        throw "Ponto e virgula esperado";
    }*/
}

void AnalisadorSintatico::CompExpressaoAritimetica(){
    CompTermo();

    TipoPedaco prox;

    while (EhMaisOuMenos(anaLex->verPedaco())){
        prox = anaLex->proximoPedaco();
    }

    CompFator();
}

void AnalisadorSintatico::CompTermo(){
    CompFator();

    TipoPedaco prox;
    while (EhVezesOuDividirOuResto(anaLex->verPedaco())){
        prox = anaLex->proximoPedaco();

        CompFator();
    }
}

void AnalisadorSintatico::CompFator()throw(string){
    TipoPedaco prox = anaLex->proximoPedaco();

    if (prox == Identificador){
        Simbolo* simbolo;
       this->tabela.encontrar(anaLex->getLiteral(), simbolo);
        if(EhFuncao(*simbolo) && FuncaoRetornaInteiro(*simbolo)){
            CompFuncao();
        }
        else if ((!EhVariavel(*simbolo)) || (!EhInteiro(*simbolo))){
            this->erro = "O simbolo não é variavel nem numero";

            throw "O simbolo não é variavel nem numero";
        }
    }
    else {
        if (prox == AbreParenteses){
            CompExpressaoAritimetica();

            prox = anaLex->proximoPedaco();
            if (prox == FechaParenteses){
                this->erro = "Fecha parenteses esperado";

                throw "Fecha parenteses esperado";
            }
        }
        else if (prox != Numero){
            this->erro = "Numero esperado";

            throw "Numero esperado";
        }
    }


}

void AnalisadorSintatico::CompExpressaoRelacional()throw(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (! EhOperadorRelacional(prox)){
        this->erro = "Operador relacional esperado";

        throw "Operador relacional esperado";
    }

    CompExpressaoAritimetica();
}

void AnalisadorSintatico::CompExpressaoLogica(){
    TipoPedaco prox = anaLex->verPedaco();

   /* if(prox == AbreParenteses){
        anaLex->proximoPedaco();
        CompExpressaoLogica();
        prox = anaLex->proximoPedaco();
        if(prox!=FechaParenteses)
            throw ") esperado !";
        prox = anaLex->verPedaco();
    }


    if(prox!= Ou && prox!=E && !Eh)
            throw "Operador relacional ou lógico esperado !";
    */CompTermoRelacional();

    prox = anaLex->verPedaco();
    while (prox == Ou){
        anaLex->proximoPedaco();
        CompTermoRelacional();
        prox = anaLex->verPedaco();
    }
}

void AnalisadorSintatico::CompTermoRelacional(){
    //CompTermoRelacional();

    TipoPedaco prox;
    while (anaLex->verPedaco() == E){
        prox = anaLex->proximoPedaco();
        CompFatorRelacional();
    }
}

void AnalisadorSintatico::CompFatorRelacional() throw(string){
    TipoPedaco prox = anaLex->proximoPedaco();

    if (prox == Negacao){
        prox = anaLex->proximoPedaco();
    }

    if (prox == Identificador){
            Simbolo* simbolo;
        this->tabela.encontrar(anaLex->getLiteral(), simbolo);
        if (EhFuncao(*simbolo) && FuncaoRetornaBool(*simbolo)){
            CompChamadaDeFuncao();

        }
        else if ((!EhVariavel(*simbolo)) && (!EhBool(*simbolo))){
            CompExpressaoRelacional();
        }
    }
    else{
        if (prox == AbreParenteses){
            CompExpressaoLogica();

            prox = anaLex->proximoPedaco();

            if (prox != FechaParenteses){
                this->erro = "Fecha parenteses esperado";

                throw "Fecha parenteses esperado";
            }
        }
        else if (!EhValorLogico(prox)){
            this->erro = "Valor logico esperado";

            throw "Valor logico esperado";
        }
    }
}

void AnalisadorSintatico::CompComandoComposto() throw(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if(prox!= Comeco)
    {
        this->erro = "Início esperado";

        throw "Início esperado";
    }

    this->nivelAtual++;
    do{
        CompComando();
        prox = anaLex->proximoPedaco();
    }while(prox!=Fim && anaLex->temMaisPedacos());
    if(prox!=Fim)
        throw "Fim esperado";

    this->tabela.eliminaNivel(this->nivelAtual);
    this->nivelAtual--;
}
void AnalisadorSintatico::CompDeclaracaoVariavel() throw(string){
    TipoRetorno tipoVar(SimboloVacuo);
    string id("");
    TipoPedaco prox = anaLex->proximoPedaco();
    if(prox!=Variavel)
        throw "Variável esperado";
    prox = anaLex->proximoPedaco();
    if(prox!= Identificador)
        throw "Identificador esperado";
    id = anaLex->getLiteral();
    while(anaLex->verPedaco()!=DoisPontos && anaLex->temMaisPedacos()){
        prox = anaLex->proximoPedaco();
        if(prox!=Virgula)
            throw "Vírgula esperado";
        prox = anaLex->proximoPedaco();
        if(prox!=Identificador)
            throw "Identificador esperado";

    }
    if(anaLex->proximoPedaco()!=DoisPontos)
        throw "Dois Pontos esperado";
    prox = anaLex->proximoPedaco();
    if(prox==Logico || prox == Inteiro){
        prox = anaLex->proximoPedaco();
        if(prox==Inteiro)
            tipoVar=SimboloInteiro;
        else
            tipoVar =SimboloLogico;
        if(prox!=PontoVirgula)
            throw "Ponto e Vírgula esperado";

        Simbolo* novaVar = new Simbolo(id, this->nivelAtual, tipoVar);
        this->tabela.guarde(novaVar);
        return;
    }//não é uma constante literal
    throw "Tipo Primitivo esperado";
}

bool AnalisadorSintatico::EhIdDeVariavel(string nomeSimbolo){
    Simbolo* simbolo;
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);
    bool ehVariavel = this->EhVariavel(*simbolo);
    return encontrou && ehVariavel;
}
bool AnalisadorSintatico::EhIdDeProcedimento(string nomeSimbolo){
    Simbolo* simbolo;
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);
    bool ehProcedimento = typeid(*simbolo) == typeid(Metodo);
    return encontrou && ehProcedimento;
}
bool AnalisadorSintatico::EhIdDeFuncao(string nomeSimbolo){
    Simbolo* simbolo;
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);

    return encontrou && EhFuncao(*simbolo);
}

bool AnalisadorSintatico::EhMaisOuMenos(TipoPedaco tipo){
    return (tipo == Soma) || (tipo == Subtracao);
}
bool AnalisadorSintatico::EhVezesOuDividir(TipoPedaco tipo){
    return (tipo == Multiplicacao) || (tipo == Divisao);
}
bool AnalisadorSintatico::EhVezesOuDividirOuResto(TipoPedaco tipo){
    return EhVezesOuDividir(tipo) || (tipo == Resto);
}
bool AnalisadorSintatico::EhFuncao(Simbolo simbolo){
    return typeid(simbolo)==typeid(Metodo) && (simbolo.getTipoRetorno() != SimboloVacuo);
}
bool AnalisadorSintatico::FuncaoRetornaInteiro(Simbolo simbolo){
    return simbolo.getTipoRetorno()== SimboloInteiro && typeid(simbolo) == typeid(Metodo);
}
bool AnalisadorSintatico::FuncaoRetornaBool(Simbolo simbolo){
    return simbolo.getTipoRetorno()== SimboloLogico && typeid(simbolo) == typeid(Metodo);
}
bool AnalisadorSintatico::EhVariavel(Simbolo simbolo){
    return typeid(simbolo) != typeid(Metodo);
}
bool AnalisadorSintatico::EhInteiro(Simbolo simbolo){
    return simbolo.getTipoRetorno() == SimboloInteiro;
}
bool AnalisadorSintatico::EhOperadorRelacional(TipoPedaco tipo){
    return tipo == Comparacao || tipo == Maior || tipo == Menor || tipo == Diferente || tipo == MaiorOuIgual || tipo == MenorOuIgual;
}
bool AnalisadorSintatico::EhValorLogico(TipoPedaco tipo){
    return tipo == Verdadeiro || tipo == Falso;
}
bool AnalisadorSintatico::EhBool(Simbolo simbolo){
    return simbolo.getTipoRetorno()== SimboloLogico;
}
void AnalisadorSintatico::CompChamadaDeVariavel() throw(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        throw "Identificador esperado";

    if (!EhIdDeVariavel(anaLex->getLiteral()))
        throw "id de variavel invalido";

    Simbolo* simbolo;
    if(!this->tabela.encontrar(anaLex->getLiteral(), simbolo))
        throw "Variável não foi declarada";

    prox = anaLex->proximoPedaco();

    if (prox == Atribuicao){
        if (simbolo->getTipoRetorno() == SimboloInteiro){
            CompExpressaoAritimetica();
        }
        else if (simbolo->getTipoRetorno() == SimboloLogico){
            CompExpressaoLogica();
        }
    }

    if(prox != PontoVirgula)
        throw "Ponto e vírgula esperado !";
}
void AnalisadorSintatico::CompChamadaDeProcedimento() throw(string){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        throw "Identificador esperado";

    if (!EhIdDeProcedimento(anaLex->getLiteral()))
        throw "Identificador de procedimento esperado";
    if(anaLex->proximoPedaco()!=AbreParenteses)
        throw "Abre parênteses esperado";

    Simbolo* simbolo;
    this->tabela.encontrar(anaLex->getLiteral(), simbolo);
	int qtosParametros = ((Metodo*)simbolo)->getQuantosParametros();
	Simbolo parFormal;
	Simbolo* parReal;
	string nomeParReal;
	int i;
	//compilar parâmetros....
	for ( i = 0; i < qtosParametros; i++) {
		if (i > 0)
			anaLex->proximoPedaco();//vírgula
		parFormal= ((Metodo*)simbolo)->getParametro(i);
		prox = anaLex->verPedaco();
		if(prox!=Identificador)
		{
			if (parFormal.getTipoRetorno()==Inteiro){
				if (prox == Numero)
					goto verif;
				else//tbm pode ser expressão booleana
					throw "Inteiro esperado!";
			}
			else {
				if (prox == Verdadeiro || prox == Falso)
					goto verif;
				else//tbm pode ser expressão aritmética
					throw "Booleano esperado!";
			}
		}

		nomeParReal = anaLex->getLiteral();
		if (!this->tabela.encontrar(nomeParReal, parReal))
			throw "Identificador não declarada !";
		//achou o parâmetro real na tabela de símbolos
		if ((*parReal).getTipoRetorno() != parFormal.getTipoRetorno())
			throw "Tipo do parâmetro real é diferente do parâmetro formal";
		if (EhIdDeFuncao(nomeParReal))
			CompChamadaDeFuncao();
		if(EhIdDeProcedimento(nomeParReal))
			CompChamadaDeProcedimento();
verif:	    anaLex->proximoPedaco();
		if (anaLex->verPedaco() != Virgula && i < qtosParametros - 1)
			throw "Vírgula esperada !";
	}

    if(anaLex->proximoPedaco()!=FechaParenteses)
        throw "Fecha parênteses esperado !";

}
void AnalisadorSintatico::CompChamadaDeFuncao(){
	TipoPedaco prox = anaLex->proximoPedaco();
	string nomeId("");
	if (prox != Identificador)
		throw "Identificador esperado";
    string nomeFuncEncontrado(anaLex->getLiteral());
	if (!EhIdDeFuncao(nomeFuncEncontrado))
		throw "Identificador de função esperado";
        if((this->nomeFuncAtual).compare(nomeFuncEncontrado)==0){
            prox = anaLex->proximoPedaco();
            //POR ENQUANTO NÃO TEM RECURSÃO

            if(prox != Atribuicao)
                throw ":= esperado!";
            prox= anaLex->verPedaco();
            if(this->retornoFuncInt){
                switch(prox){
                    case Identificador:
                        nomeId = anaLex->getLiteral();
                        Simbolo* simboloId;
                        if(tabela.encontrar(nomeId, simboloId)){
                                if(EhInteiro(*simboloId)){
                                    if(EhIdDeFuncao(nomeId))
                                        CompChamadaDeFuncao();
                                    else
                                        this->anaLex->proximoPedaco();
                                }
                                else{
                                    throw "Inteiro esperado, mas Booleano encontrado !";
                                }
                        }
                        else
                            throw "Identificador não declarado!";

                    break;
                    case Numero://por enquanto não
                        //aceita expressão aritmétoica
                        anaLex->proximoPedaco();
                    break;
                }
            }
            else{//função retorna bool
                switch(prox){
                    case Identificador:
                     nomeId = anaLex->getLiteral();
                        Simbolo* simboloId;
                        if(tabela.encontrar(nomeId, simboloId)){
                                if(EhBool(*simboloId)){
                                    if(EhIdDeFuncao(nomeId))
                                        CompChamadaDeFuncao();
                                    else
                                        this->anaLex->proximoPedaco();
                                }
                                else{
                                    throw "Inteiro esperado, mas Booleano encontrado !";
                                }
                        }
                        else
                            throw "Identificador não declarado!";

                    break;
                    case Verdadeiro:
                    case Falso:
                        anaLex->proximoPedaco();
                    break;
                }//FIM DO SWITCH

            }//FIM DO IF(FUNCAORETONAINT)
            prox = anaLex->proximoPedaco();
            if(prox != PontoVirgula)
                throw "; esperado !";
            return;
            }//FIM DO IF NOME DA FUNÇÃO É IGUAL AO ENCONTRADO

	if (anaLex->proximoPedaco() != AbreParenteses)
		throw "Abre parênteses esperado";

	Simbolo* simbolo;
	this->tabela.encontrar(anaLex->getLiteral(), simbolo);
    int qtosParametros = ((Metodo*)simbolo)->getQuantosParametros();
    Simbolo parFormal;
	Simbolo* parReal;
	string nomeParReal;
	int i;
	//compilar parâmetros....
	for (i = 0; i < qtosParametros; i++) {
		if (i > 0)
			anaLex->proximoPedaco();//vírgula
		parFormal = ((Metodo*)simbolo)->getParametro(i);
		prox = anaLex->verPedaco();
		if (prox != Identificador)
		{
			if (parFormal.getTipoRetorno() == Inteiro) {
				if (prox == Numero)
					goto verif;
				else//tbm pode ser expressão booleana
					throw "Inteiro esperado!";
			}
			else {
				if (prox == Verdadeiro || prox == Falso)
					goto verif;
				else//tbm pode ser expressão aritmética
					throw "Booleano esperado!";
			}
		}

		nomeParReal = anaLex->getLiteral();
		if (!this->tabela.encontrar(nomeParReal, parReal))
			throw "Identificador não declarada !";
		//achou o parâmetro real na tabela de símbolos
		if ((*parReal).getTipoRetorno() != parFormal.getTipoRetorno())
			throw "Tipo do parâmetro real é diferente do parâmetro formal";
		if (EhIdDeFuncao(nomeParReal))
			CompChamadaDeFuncao();
		if (EhIdDeProcedimento(nomeParReal))
			CompChamadaDeProcedimento();
	verif:	    anaLex->proximoPedaco();
		if (anaLex->verPedaco()!= Virgula && i < qtosParametros - 1)
			throw "Vírgula esperada !";
	}

	if (anaLex->proximoPedaco() != FechaParenteses)
		throw "Fecha parênteses esperado !";

}
void AnalisadorSintatico::CompEnquanto(){
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Enquanto){
        throw "Enquanto esperado";
    }

    CompExpressaoLogica();

    prox = anaLex->proximoPedaco();
    if (prox == Faca){
        throw "Do esperado";
    }

    prox = anaLex->verPedaco();
    if (prox == Comeco){
        CompComandoComposto();
    }
    else{
        CompComando();
    }
}
//sintaxe do nossa declaração de função repetição de 0 a n
//function + identificador+ (           + [<parãmetros>] + )+ : boolean/integer + begin + ..
void AnalisadorSintatico::CompFuncao(){
     TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Funcao){
        throw "Função esperada";
    }

    prox = anaLex->proximoPedaco();
    if (prox != Identificador){
        throw "Identificador esperado";
    }

    string nomeFunc = anaLex->getLiteral();
    this->nomeFuncAtual = nomeFunc;
    std::list<Simbolo> listaParametros;
    //std::list<Simbolo>::iterator it;
    //it = listaParametros.begin();
    int tamanhoLista = 0;

    prox = anaLex->proximoPedaco();
    if (prox != AbreParenteses){
        throw "Abre Parênteses esperado";
    }

    prox = anaLex->verPedaco();
    while(prox == Inteiro || prox == Logico){
        TipoPedaco tipoParametro = prox;
        TipoRetorno retornoParametro;

        switch(tipoParametro){
            case Inteiro:
                retornoParametro = SimboloInteiro;

                break;
            case Logico:
                retornoParametro = SimboloLogico;

                break;
        }

        anaLex->proximoPedaco();
        prox = anaLex->proximoPedaco();

        if(prox != Identificador)
            throw "Identificador esperado !";
        Simbolo param(anaLex->getLiteral(), this->nivelAtual, retornoParametro);
        listaParametros.push_back(param);
		tamanhoLista++;
        prox = anaLex->verPedaco();
        switch(prox){
            case FechaParenteses:
            goto foraLoop;
            break;
            case Virgula:
            anaLex->proximoPedaco();
            break;
            default:
                throw "Vírgula ou Fecha Parênteses esperado!";
        }
        prox = anaLex->verPedaco();

    }//fim do while
foraLoop:prox = anaLex->proximoPedaco();
	 if(prox !=FechaParenteses)
            throw "Fecha Parênteses esperado !";
    prox = anaLex->proximoPedaco();
    if(prox !=DoisPontos)
            throw "Dois Pontos esperado !";
    prox = anaLex->proximoPedaco();
    if(!(prox==Inteiro || prox==Logico))
            throw "Tipo de retorno esperado !";


    TipoRetorno retorno;
    switch(prox){
        case Inteiro:
            retorno = SimboloInteiro;
            this->retornoFuncInt=true;
            break;
        case Logico:
            retorno = SimboloLogico;
            this->retornoFuncInt=false;
            break;
    }

     Simbolo* vetor = new Simbolo[tamanhoLista];
	 int i;
	 for(i=0;i<tamanhoLista;i++){
        *(vetor+i) = listaParametros.front();
        listaParametros.pop_front();
        }

    Metodo* funcao = new Metodo(nomeFunc, this->nivelAtual, vetor, tamanhoLista, retorno);
	prox = anaLex->proximoPedaco();
	if (prox != PontoVirgula) {
		throw "ponto e virgula esperado";
	}
	this->tabela.guarde(funcao);
    prox = anaLex->verPedaco();
    while (prox == Variavel){
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }
    //loop da main
    if(prox==Procedimento){
        this->nomeFuncAtual = "";
        CompProcedimento();}
    if(prox==Funcao){
        this->nomeFuncAtual= "";
        CompFuncao();}
    this->nomeFuncAtual= nomeFunc;
    this->retornoFuncInt = retorno == SimboloInteiro;
    this->jaRetornou = false;
    prox = anaLex->verPedaco();
    if(prox!=Comeco)
        throw "Início esperado";
    CompComandoComposto();
    if(!jaRetornou)
        throw "Função não retorna nenhum valor!";
    this->nomeFuncAtual = "";
    this->jaRetornou = false;
}
