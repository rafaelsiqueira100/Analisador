#include <iostream>
#include "AnalisadorSintatico.h"



AnalisadorSintatico::AnalisadorSintatico(string nomeArquivo):
    anaLex(new AnalisadorLexico(nomeArquivo)),
    nivelAtual(0),
    nomeFuncAtual(""),
    retornoFuncInt(false),
    jaRetornou(false),
    erro("")
{}


AnalisadorSintatico::~AnalisadorSintatico()
{
    delete (this->anaLex);
}

void AnalisadorSintatico::CompProgramaPrincipal() throw(){
     if(this->erro.compare("")!=0)
        return;
     TipoPedaco prox = anaLex->proximoPedaco();
     if(prox!=Programa)
     {

         cout << '\n' <<"Programa esperado";
     }

    prox = anaLex->proximoPedaco();
     if(prox!=Identificador)
     {
         this->erro = "Identificador esperado";

         cout << '\n' <<"Identificador esperado";
     }

    prox = anaLex->proximoPedaco();
    if(prox!=PontoVirgula)
    {
        this->erro = "Ponto e Vírgula esperado";

        cout << '\n' <<"Ponto e Vírgula esperado";
    }

    prox = anaLex->verPedaco();
    while(prox==Variavel){
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();

    }

    if(prox==Procedimento)
        CompProcedimento();

    prox = anaLex->verPedaco();

    if(prox==Funcao)
        CompFuncao();
    prox = anaLex->verPedaco();
    if(prox!= Comeco)
    {
        this->erro = "Início inesperado";

        cout << '\n' <<"Início inesperado";
    }

    CompComandoComposto();//COMPILA INÍCIO E FIM

}
void AnalisadorSintatico::CompInicioPrograma() throw(){
    if(this->erro.compare("")!=0)
        return;
    CompProgramaPrincipal();
    if(anaLex->proximoPedaco()!=Ponto)
    {
        this->erro = "Ponto esperado";

        cout << '\n' <<"Ponto esperado";
    }
}
void AnalisadorSintatico::CompProcedimento()throw(){
    if(this->erro.compare("")!=0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Procedimento){
        this->erro = "Procedimento esperado";

        cout << '\n' <<"Procedimento esperado";
    }
    prox = anaLex->proximoPedaco();

    if (prox != Identificador){
        this->erro = "Identificador esperado";

        cout << '\n' <<"Identificador esperado";
    }
    string nomeProc = anaLex->getLiteral();
    std::list<Simbolo> listaParametros;
    /*std::list<Simbolo>::iterator it;
    it = listaParametros.begin();*/
	int tamanhoLista = 0;
	prox = anaLex->proximoPedaco();
    if (prox != AbreParenteses){
        this->erro = "Abre Parênteses esperado";

        cout << '\n' <<"Abre Parênteses esperado";
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

            cout << '\n' <<"Identificador esperado !";
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

                cout << '\n' <<"Vírgula ou Fecha Parênteses esperado!";
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
    Metodo* procedimento;
    if(tamanhoLista!=0)
        procedimento = new Metodo( nomeProc, this->nivelAtual,vetor, tamanhoLista, SimboloVacuo );
    else
        procedimento = new Metodo( nomeProc, this->nivelAtual,nullptr, tamanhoLista, SimboloVacuo );

    if(prox !=FechaParenteses)
    {
        this->erro = "Fecha Parênteses esperado !";

        cout << '\n' <<"Fecha Parênteses esperado !";
    }

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula){
        this->erro = "Ponto e virgula esperado";

        cout << '\n' <<"Ponto e virgula esperado";
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
        cout << '\n' <<"Início esperado !";
    CompComandoComposto();

    /*prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula){
        cout << '\n' <<"ponto e virgula esperado";
    }*/
}
// E função??
void AnalisadorSintatico::CompComando()throw(){
    if(this->erro.compare("")!=0)
        return;
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

                cout << '\n' <<"Ponto e vírgula esperado";
            }
        }
        else if(EhIdDeFuncao(nomeId)){
            CompChamadaDeFuncao();
			if (anaLex->proximoPedaco() != PontoVirgula)
            {
                this->erro = "Ponto e vírgula esperado";

                cout << '\n' <<"Ponto e vírgula esperado";
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
void AnalisadorSintatico::CompPegue()throw(){
	if(this->erro.compare("")!=0)
        return;
	TipoPedaco prox = anaLex->proximoPedaco();
	if (prox != Pegue) {
        this->erro = "Except esperado !";

		cout << '\n' <<"Except esperado !";
	}

	prox = anaLex->verPedaco();
	if (prox == Comeco) {
		CompComandoComposto();
	}
	else {
		CompComando();
	}
}
void AnalisadorSintatico::CompTente()throw() {
	if(this->erro.compare("")!=0)
        return;
	TipoPedaco prox = anaLex->proximoPedaco();
	if (prox != Tente) {
        this->erro = "Try esperado !";

		cout << '\n' <<"Try esperado !";
	}
	prox = anaLex->verPedaco();
	if (prox == Comeco) {
		CompComandoComposto();
	}
	else {
		CompComando();
	}
}
void AnalisadorSintatico::CompSe()throw(){
    if(this->erro.compare("")!=0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Se){
        this->erro = "if esperado";

        cout << '\n' <<"if esperado";
    }

    CompExpressaoLogica();

    prox = anaLex->proximoPedaco();
    if (prox != Entao){
        this->erro = "Then esperado";

        cout << '\n' <<"Then esperado";
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
            cout << '\n' <<"Fecha Parênteses esperado !";
        cout << '\n' <<"Ponto e virgula esperado";
    }*/
}

void AnalisadorSintatico::CompExpressaoAritimetica() throw(){
    if(this->erro.compare("")!=0)
        return;

    CompTermo();

    TipoPedaco prox;

    while (EhMaisOuMenos(anaLex->verPedaco())) {
        prox = anaLex->proximoPedaco();
    }

    CompFator();
}

void AnalisadorSintatico::CompTermo()throw(){
    if(this->erro.compare("")!=0)
        return;
    CompFator();

    TipoPedaco prox;
    while (EhVezesOuDividirOuResto(anaLex->verPedaco())){
        prox = anaLex->proximoPedaco();

        CompFator();
    }
}

void AnalisadorSintatico::CompFator()throw(){
    if(this->erro.compare("")!=0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();

    if (prox == Identificador){
        Simbolo* simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
       this->tabela.encontrar(anaLex->getLiteral(), simbolo);
        if(EhFuncao(*simbolo) && FuncaoRetornaInteiro(*simbolo)){
            CompFuncao();
        }
        else if ((!EhVariavel(*simbolo)) || (!EhInteiro(*simbolo))){
            this->erro = "O simbolo não é variavel nem numero";

            cout << '\n' <<"O simbolo não é variavel nem numero";
        }
    }
    else {
        if (prox == AbreParenteses){
            CompExpressaoAritimetica();

            prox = anaLex->proximoPedaco();
            if (prox == FechaParenteses){
                this->erro = "Fecha parenteses esperado";

                cout << '\n' <<"Fecha parenteses esperado";
            }
        }
        else if (prox != Numero){
            this->erro = "Numero esperado";

            cout << '\n' <<"Numero esperado";
        }
    }


}

void AnalisadorSintatico::CompExpressaoRelacional()throw(){
    if(this->erro.compare("")!=0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (! EhOperadorRelacional(prox)){
        this->erro = "Operador relacional esperado";

        cout << '\n' <<"Operador relacional esperado";
    }

    CompExpressaoAritimetica();
}

void AnalisadorSintatico::CompExpressaoLogica() throw(){
    if(this->erro.compare("")!=0)
        return;
    TipoPedaco prox = anaLex->verPedaco();

   /* if(prox == AbreParenteses){
        anaLex->proximoPedaco();
        CompExpressaoLogica();
        prox = anaLex->proximoPedaco();
        if(prox!=FechaParenteses)
            cout << '\n' <<") esperado !";
        prox = anaLex->verPedaco();
    }


    if(prox!= Ou && prox!=E && !Eh)
            cout << '\n' <<"Operador relacional ou lógico esperado !";
    */CompTermoRelacional();

    prox = anaLex->verPedaco();
    while (prox == Ou){
        anaLex->proximoPedaco();
        CompTermoRelacional();
        prox = anaLex->verPedaco();
    }
}

void AnalisadorSintatico::CompTermoRelacional()throw(){
    if(this->erro.compare("")!=0)
        return;
    //CompTermoRelacional();

    TipoPedaco prox;
    while (anaLex->verPedaco() == E){
        prox = anaLex->proximoPedaco();
        CompFatorRelacional();
    }
}

void AnalisadorSintatico::CompFatorRelacional() throw(){
    if(this->erro.compare("")!=0)
        return;
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

                cout << '\n' <<"Fecha parenteses esperado";
            }
        }
        else if (!EhValorLogico(prox)){
            this->erro = "Valor logico esperado";

            cout << '\n' <<"Valor logico esperado";
        }
    }
}

void AnalisadorSintatico::CompComandoComposto() throw(){
    if(this->erro.compare("")!=0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if(prox!= Comeco)
    {
        this->erro = "Início esperado";

        cout << '\n' <<"Início esperado";
    }

    this->nivelAtual++;
    do{
        CompComando();
        prox = anaLex->proximoPedaco();
    }while(prox!=Fim && anaLex->temMaisPedacos());
    if(prox!=Fim)
        cout << '\n' <<"Fim esperado";

    this->tabela.eliminaNivel(this->nivelAtual);
    this->nivelAtual--;
}
void AnalisadorSintatico::CompDeclaracaoVariavel() throw(){
    if(this->erro.compare("")!=0)
        return;
    TipoRetorno tipoVar(SimboloVacuo);
    string id("");
    list<string> lista;
    TipoPedaco prox = anaLex->proximoPedaco();
    if(prox!=Variavel)
        cout << '\n' <<"Variável esperado";
    prox = anaLex->proximoPedaco();
    if(prox!= Identificador)
        cout << '\n' <<"Identificador esperado";
    id = anaLex->getLiteral();
    lista.push_back(id);
    prox = anaLex->verPedaco();
    while(prox!=DoisPontos && anaLex->temMaisPedacos()){

        prox = anaLex->proximoPedaco();
        if(prox!=Virgula )
            cout << '\n' <<"Vírgula esperado";
        prox = anaLex->proximoPedaco();
        if(prox!=Identificador)
            cout << '\n' <<"Identificador esperado";
        id = anaLex->getLiteral();
        lista.push_back(id);
        prox = anaLex->verPedaco();

    }

    if(anaLex->proximoPedaco()!=DoisPontos)
        cout << '\n' <<"Dois Pontos esperado";
    prox = anaLex->verPedaco();
    if(prox==Logico || prox == Inteiro){
        prox = anaLex->proximoPedaco();
        if(prox==Inteiro)
            tipoVar=SimboloInteiro;
        else
            tipoVar =SimboloLogico;
        prox = anaLex->proximoPedaco();
        if(prox!=PontoVirgula)
            cout << '\n' <<"Ponto e Vírgula esperado";
        int i(0);
        Simbolo* novaVar = new Simbolo();
        int tamanhoLista(lista.size());
        for(;i<tamanhoLista;i++){
            id = *(lista.begin());
            delete novaVar;
            novaVar = new Simbolo(id, this->nivelAtual,tipoVar);
            this->tabela.guarde(novaVar);
            lista.pop_front();
        }
        lista.erase(lista.begin(), lista.end());
        return;
    }//não é uma constante literal
    cout << '\n' <<"Tipo Primitivo esperado";
}

bool AnalisadorSintatico::EhIdDeVariavel(string nomeSimbolo){
    Simbolo* simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
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
void AnalisadorSintatico::CompChamadaDeVariavel() throw(){
    if(this->erro.compare("")!=0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        cout << '\n' <<"Identificador esperado";

    if (!EhIdDeVariavel(anaLex->getLiteral()))
        cout << '\n' <<"id de variavel invalido";

    Simbolo* simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    if(!this->tabela.encontrar(anaLex->getLiteral(), simbolo))
        cout << '\n' <<"Variável não foi declarada";

    prox = anaLex->proximoPedaco();

    if (prox == Atribuicao){
        if (simbolo->getTipoRetorno() == SimboloInteiro){
            CompExpressaoAritimetica();
        }
        else if (simbolo->getTipoRetorno() == SimboloLogico){
            CompExpressaoLogica();
        }
    }

    prox = anaLex->proximoPedaco();

    if(prox != PontoVirgula)
        cout << '\n' <<"Ponto e vírgula esperado !";
}
void AnalisadorSintatico::CompChamadaDeProcedimento() throw(){
    if(this->erro.compare("")!=0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador)
        cout << '\n' <<"Identificador esperado";

    if (!EhIdDeProcedimento(anaLex->getLiteral()))
        cout << '\n' <<"Identificador de procedimento esperado";
    if(anaLex->proximoPedaco()!=AbreParenteses)
        cout << '\n' <<"Abre parênteses esperado";

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
					cout << '\n' <<"Inteiro esperado!";
			}
			else {
				if (prox == Verdadeiro || prox == Falso)
					goto verif;
				else//tbm pode ser expressão aritmética
					cout << '\n' <<"Booleano esperado!";
			}
		}

		nomeParReal = anaLex->getLiteral();
		if (!this->tabela.encontrar(nomeParReal, parReal))
			cout << '\n' <<"Identificador não declarada !";
		//achou o parâmetro real na tabela de símbolos
		if ((*parReal).getTipoRetorno() != parFormal.getTipoRetorno())
			cout << '\n' <<"Tipo do parâmetro real é diferente do parâmetro formal";
		if (EhIdDeFuncao(nomeParReal))
			CompChamadaDeFuncao();
		if(EhIdDeProcedimento(nomeParReal))
			CompChamadaDeProcedimento();
verif:	    anaLex->proximoPedaco();
		if (anaLex->verPedaco() != Virgula && i < qtosParametros - 1)
			cout << '\n' <<"Vírgula esperada !";
	}

    if(anaLex->proximoPedaco()!=FechaParenteses)
        cout << '\n' <<"Fecha parênteses esperado !";

}
void AnalisadorSintatico::CompChamadaDeFuncao()throw(){
	if(this->erro.compare("")!=0)
        return;
	TipoPedaco prox = anaLex->proximoPedaco();
	string nomeId("");
	if (prox != Identificador)
		cout << '\n' <<"Identificador esperado";
    string nomeFuncEncontrado(anaLex->getLiteral());
	if (!EhIdDeFuncao(nomeFuncEncontrado))
		cout << '\n' <<"Identificador de função esperado";
        if((this->nomeFuncAtual).compare(nomeFuncEncontrado)==0){
            prox = anaLex->proximoPedaco();
            //POR ENQUANTO NÃO TEM RECURSÃO

            if(prox != Atribuicao)
                cout << '\n' <<":= esperado!";
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
                                    cout << '\n' <<"Inteiro esperado, mas Booleano encontrado !";
                                }
                        }
                        else
                            cout << '\n' <<"Identificador não declarado!";

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
                                    cout << '\n' <<"Inteiro esperado, mas Booleano encontrado !";
                                }
                        }
                        else
                            cout << '\n' <<"Identificador não declarado!";

                    break;
                    case Verdadeiro:
                    case Falso:
                        anaLex->proximoPedaco();
                    break;
                }//FIM DO SWITCH

            }//FIM DO IF(FUNCAORETONAINT)
            prox = anaLex->proximoPedaco();
            if(prox != PontoVirgula)
                cout << '\n' <<"; esperado !";
            return;
            }//FIM DO IF NOME DA FUNÇÃO É IGUAL AO ENCONTRADO

	if (anaLex->proximoPedaco() != AbreParenteses)
		cout << '\n' <<"Abre parênteses esperado";

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
					cout << '\n' <<"Inteiro esperado!";
			}
			else {
				if (prox == Verdadeiro || prox == Falso)
					goto verif;
				else//tbm pode ser expressão aritmética
					cout << '\n' <<"Booleano esperado!";
			}
		}

		nomeParReal = anaLex->getLiteral();
		if (!this->tabela.encontrar(nomeParReal, parReal))
			cout << '\n' <<"Identificador não declarada !";
		//achou o parâmetro real na tabela de símbolos
		if ((*parReal).getTipoRetorno() != parFormal.getTipoRetorno())
			cout << '\n' <<"Tipo do parâmetro real é diferente do parâmetro formal";
		if (EhIdDeFuncao(nomeParReal))
			CompChamadaDeFuncao();
		if (EhIdDeProcedimento(nomeParReal))
			CompChamadaDeProcedimento();
	verif:	    anaLex->proximoPedaco();
		if (anaLex->verPedaco()!= Virgula && i < qtosParametros - 1)
			cout << '\n' <<"Vírgula esperada !";
	}

	if (anaLex->proximoPedaco() != FechaParenteses)
		cout << '\n' <<"Fecha parênteses esperado !";

}
void AnalisadorSintatico::CompEnquanto()throw(){
    if(this->erro.compare("")!=0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Enquanto){
        cout << '\n' <<"Enquanto esperado";
    }

    CompExpressaoLogica();

    prox = anaLex->proximoPedaco();
    if (prox == Faca){
        cout << '\n' <<"Do esperado";
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
void AnalisadorSintatico::CompFuncao()throw(){
     if(this->erro.compare("")!=0)
        return;
     TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Funcao){
        cout << '\n' <<"Função esperada";
    }

    prox = anaLex->proximoPedaco();
    if (prox != Identificador){
        cout << '\n' <<"Identificador esperado";
    }

    string nomeFunc = anaLex->getLiteral();
    this->nomeFuncAtual = nomeFunc;
    std::list<Simbolo> listaParametros;
    //std::list<Simbolo>::iterator it;
    //it = listaParametros.begin();
    int tamanhoLista = 0;

    prox = anaLex->proximoPedaco();
    if (prox != AbreParenteses){
        cout << '\n' <<"Abre Parênteses esperado";
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
            cout << '\n' <<"Identificador esperado !";
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
                cout << '\n' <<"Vírgula ou Fecha Parênteses esperado!";
        }
        prox = anaLex->verPedaco();

    }//fim do while
foraLoop:prox = anaLex->proximoPedaco();
	 if(prox !=FechaParenteses)
            cout << '\n' <<"Fecha Parênteses esperado !";
    prox = anaLex->proximoPedaco();
    if(prox !=DoisPontos)
            cout << '\n' <<"Dois Pontos esperado !";
    prox = anaLex->proximoPedaco();
    if(!(prox==Inteiro || prox==Logico))
            cout << '\n' <<"Tipo de retorno esperado !";


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
		cout << '\n' <<"ponto e virgula esperado";
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
        cout << '\n' <<"Início esperado";
    CompComandoComposto();
    if(!jaRetornou)
        cout << '\n' <<"Função não retorna nenhum valor!";
    this->nomeFuncAtual = "";
    this->jaRetornou = false;
}
