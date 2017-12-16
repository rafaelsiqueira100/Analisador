#include <iostream>
#include <stdlib.h>
#include <ctype.h>

#include "AnalisadorSintatico.h"
//#include "stdafx.h"
#include "Variavel.h"

AnalisadorSintatico::AnalisadorSintatico(string nomeArquivo) : anaLex(new AnalisadorLexico(nomeArquivo)),
                                                               nivelAtual(0),
                                                               nivelDeComandoComposto(0),
                                                               retornoFuncInt(false),
                                                               jaRetornou(false),
                                                               compilandoProcedimento(false),
                                                               erro(""),
                                                               nomeFuncAtual(""),
                                                               numParenteses(0)
{

}

AnalisadorSintatico::~AnalisadorSintatico()
{
	free(this->anaLex);
}

bool AnalisadorSintatico::NaoHaErro() throw()
{
	return this->erro.compare("") == 0;
}

void AnalisadorSintatico::CompProgramaPrincipal() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Programa && this->NaoHaErro())
    {
		this->erro = "Ha erro";

         ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Programa esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
    	return;
    }

    prox = anaLex->proximoPedaco();
    if (prox != Identificador && this->NaoHaErro())
    {
        this->erro = "Identificador esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

         ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
        return;
    }

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula && this->NaoHaErro())
    {
        this->erro = "Ponto e Virgula esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

         ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Ponto e Virgula esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
        return;
    }

    prox = anaLex->verPedaco();
    while (prox == Variavel)
    {
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }

    if (prox == Procedimento)
        CompProcedimento();

    prox = anaLex->verPedaco();

    if (prox == Funcao)
        CompFuncao();
    prox = anaLex->verPedaco();
    if (prox != Comeco && this->NaoHaErro())
    {
        this->erro = "Inicio esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

         ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << this->erro;
        return;
    }

    CompComandoComposto(); //COMPILA INiCIO E FIM
}


void AnalisadorSintatico::CompInicioPrograma() throw()
{
    if (this->erro.compare("") != 0)
        return;
    CompProgramaPrincipal();
    if (anaLex->proximoPedaco() != Ponto && this->NaoHaErro())
    {
        this->erro = "Ponto esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

         ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Ponto esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
        return;
    }
}
void AnalisadorSintatico::CompProcedimento() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Procedimento && this->NaoHaErro())
    {
        this->erro = "Procedimento esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

         ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Procedimento esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
        return;
    }
    prox = anaLex->proximoPedaco();

    if (prox != Identificador && this->NaoHaErro())
    {
        this->erro = "Identificador esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

         ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
        return;
    }
    string nomeProc = anaLex->getLiteral();
    std::list<Simbolo> listaParametros;
    /*std::list<Simbolo>::iterator it;
    it = listaParametros.begin();*/
    int tamanhoLista = 0;
    prox = anaLex->proximoPedaco();
    if (prox != AbreParenteses && this->NaoHaErro())
    {
        this->erro = "Abre Parenteses esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

         ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Abre Parenteses esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
            return;
    }

    prox = anaLex->verPedaco();
    while (prox == Inteiro || prox == Logico)
    {
        TipoPedaco tipoParametro = prox;
        TipoRetorno retornoParametro;

        switch (tipoParametro)
        {
        case Inteiro:
            retornoParametro = SimboloInteiro;
        case Logico:
            retornoParametro = SimboloLogico;
        }

        anaLex->proximoPedaco();
        prox = anaLex->proximoPedaco();
        if (prox != Identificador && this->NaoHaErro())
        {
            this->erro = "Identificador esperado";

            cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << "Identificador esperado"<<", mas "+this->anaLex->getLiteral()<<" encontrado!";
            return;
        }
        this->nivelAtual++;
        Simbolo param(anaLex->getLiteral(), this->nivelAtual, retornoParametro);
        tamanhoLista++;

        listaParametros.push_back(param);
        prox = anaLex->verPedaco();
        switch (prox)
        {
        case FechaParenteses:
            break;
        case Virgula:
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
            break;
        default:
        	if (this->NaoHaErro())
        	{
        		this->erro = "Virgula ou Fecha Parenteses esperado, mas "+this->anaLex->getLiteral()+" encontrado!";

	            cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
	                 << "Virgula ou Fecha Parenteses esperado" << ", mas " + this->anaLex->getLiteral() << " encontrado!";
	                 
	            return;
			}            
        }
    } //fim do while

    prox = anaLex->proximoPedaco();
    Simbolo *vetor = new Simbolo[tamanhoLista];
    int i;
    for (i = 0; i < tamanhoLista; i++)
    {
        *(vetor + i) = listaParametros.front();
        listaParametros.pop_front();
    }
    this->nivelAtual--;
    Simbolo *procedimento;
    if (tamanhoLista != 0)
        procedimento = new Simbolo(nomeProc, this->nivelAtual, vetor, tamanhoLista, SimboloVacuo);
    else
        procedimento = new Simbolo(nomeProc, this->nivelAtual, nullptr, tamanhoLista, SimboloVacuo);

    if (prox != FechaParenteses && this->NaoHaErro())
    {
        this->erro = "Fecha Parenteses esperado";

        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Fecha Parenteses esperado" << ", mas " + this->anaLex->getLiteral() << " encontrado!";
        return;
    }

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula && this->NaoHaErro())
    {
        this->erro = "Ponto e virgula esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Ponto e virgula esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
        return;
    }

    this->tabela.guarde(procedimento);
    prox = anaLex->verPedaco();
    this->nivelAtual++;
    while (prox == Variavel)
    {
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }

    //loop da main
    if (prox == Procedimento)
        CompProcedimento();
    if (prox == Funcao)
        CompFuncao();
    prox = anaLex->verPedaco();
    if (prox != Comeco && this->NaoHaErro()) 
	{
        this->erro = "Inicio esperado";
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << this->erro << ", mas " + this->anaLex->getLiteral() << " encontrado!";
        return;
    }
    Simbolo *paramAtual;
    for (i = 0; i < tamanhoLista; i++)
    {
        tabela.guarde(vetor + i);
    }
    this->nivelAtual--;
    //comando composto j谩 vai incrementar nivelAtual

    CompComandoComposto();
}
// E funcao??
void AnalisadorSintatico::CompComando() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->verPedaco();
    if (prox == Identificador)
    {
        string nomeId = anaLex->getLiteral();
        if (EhIdDeVariavel(nomeId))
        {
            CompChamadaDeVariavel();
        }
        else if (EhIdDeProcedimento(nomeId))
        {
            CompChamadaDeProcedimento();
            if (anaLex->proximoPedaco() != PontoVirgula && this->NaoHaErro())
            {
                this->erro = "Ponto e virgula esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                     << "Ponto e virgula esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
                return;
            }
        }
        else if (EhIdDeFuncao(nomeId))
        {
            CompChamadaDeFuncao(nomeId);
            if(nomeId!=this->nomeFuncAtual){
                    //se for uma chamada de fora da funcao,
                    //chamadadefuncao nao consome ;
                if (anaLex->proximoPedaco() != PontoVirgula && this->NaoHaErro())
                {
                    this->erro = "Ponto e virgula esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

                    cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                         << "Ponto e virgula esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
                    return;
                }
            }//se for uma chamada de atribuicao de retorno interno da
            //pr贸pria funcao, ele consome;
        }
        else
        {
        	if (this->NaoHaErro())
        	{
				this->erro = "Simbolo desconhecido: ";
				cout ;cout <<'\n'<<"Linha atual :" << this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << this->erro << nomeId;
                 
	            anaLex->proximoPedaco();
	                 
	            return;
			}        	        	
		}
    }
    else
    {
        switch (prox)
        {
        case Se:
            CompSe();
            break;
        case Enquanto:
            CompEnquanto();
            break;
        case Tente:
            CompTente();
            break;
		case Escreva:
			CompEscreva();
            break;
		default:
			if (this->NaoHaErro()) {
				this->erro = this->anaLex->getLiteral() + " invalido para iniciar um comando!";
				cout ;cout <<'\n' << "Linha atual:" << this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
				return;
			}
        }
    }
}
void AnalisadorSintatico::CompPegue() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Pegue && this->NaoHaErro())
    {
        this->erro = "Except esperado";

        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Except esperado" << ", mas " + this->anaLex->getLiteral() << " encontrado!";
        return;
    }

    prox = anaLex->verPedaco();
    if (prox == Comeco)
    {
        CompComandoComposto();
    }
    else
    {
        CompComando();
    }
}
void AnalisadorSintatico::CompEscreva()throw() 
{//write pode receber string entre '' ou expressao inteira
	if (this->erro.compare("") != 0)
		return;
	TipoPedaco prox = anaLex->proximoPedaco();
	if (prox != Escreva && this->NaoHaErro())
	{
		this->erro = "Write esperado, mas "+this->anaLex->getLiteral()+" encontrado!";

		cout ;cout <<'\n' << "Linha atual :" << this->anaLex->getLinhaAtual() ;cout <<'\n'
			<< "Write esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
		return;
	}
	prox = anaLex->proximoPedaco();
	if (prox != AbreParenteses && this->NaoHaErro()) {
		this->erro = "( esperado, mas "+this->anaLex->getLiteral()+" encontrado!";

		cout ;cout <<'\n' << "Linha atual :" << this->anaLex->getLinhaAtual() ;cout <<'\n'
			<< this->erro;
		return;
	}
	prox = anaLex->verPedaco();
	
	if(prox == Aspa) {
		anaLex->proximoPedaco();
		do 
		{
			prox = anaLex->proximoPedaco();
		} while (prox != Aspa && anaLex->temMaisPedacos() && this->NaoHaErro());
		if (prox != Aspa) {
			this->erro = "' esperado, mas "+this->anaLex->getLiteral()+" encontrado!";

			cout ;cout <<'\n' << "Linha atual :" << this->anaLex->getLinhaAtual() ;cout <<'\n'
				<< this->erro;
			return;
		}
				
	}
	else {//printar expressao inteira
		CompOperandoInteiro();
	}
	prox = anaLex->proximoPedaco();
	if (prox != FechaParenteses && this->NaoHaErro()) {
		this->erro = ") esperado, mas "+this->anaLex->getLiteral()+" encontrado!";

		cout ;cout <<'\n' << "Linha atual :" << this->anaLex->getLinhaAtual() ;cout <<'\n'
			<< this->erro;
		return;
	}
	prox = anaLex->proximoPedaco();
	if (prox != PontoVirgula && this->NaoHaErro()) {
		this->erro = "Ponto e Virgula esperado, mas "+this->anaLex->getLiteral()+" encontrado!";

		cout ;cout <<'\n' << "Linha atual :" << this->anaLex->getLinhaAtual() ;cout <<'\n'
			<< this->erro;
		return;
	}
}
void AnalisadorSintatico::CompTente() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Tente && this->NaoHaErro())
    {
        this->erro = "Try esperado, mas "+this->anaLex->getLiteral()+" encontrado!";

        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Try esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
        return;
    }
    prox = anaLex->verPedaco();
    if (prox == Comeco)
    {
        CompComandoComposto();
    }
    else
    {
        CompComando();
    }
	prox = anaLex->verPedaco();
	if (prox == Pegue)
		CompPegue();
}
void AnalisadorSintatico::CompSe() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Se && this->NaoHaErro())
    {
        this->erro = "If esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "if esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
        return;
    }

    CompOperandoBooleano();

    prox = anaLex->proximoPedaco();
    if (prox != Entao && this->NaoHaErro())
    {
        this->erro = "Then esperado, mas "+this->anaLex->getLiteral()+" encontrado !";

        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Then esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
        return;
    }

    prox = anaLex->verPedaco();
    if (prox == Comeco)
    {
        CompComandoComposto();
    }
    else
    {
        CompComando();
    }
    if (anaLex->verPedaco() == Senao)
    {
        anaLex->proximoPedaco();//consome senao
        prox = anaLex->verPedaco();
        if (prox == Comeco)
        {
            CompComandoComposto();
        }
        else
        {
            CompComando();
        }
    }

    /*prox = anaLex->proximoPedaco();
    if (prox == PontoVirgula){prox = anaLex->proximoPedaco();
    if(prox !=FechaParenteses)
            cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' <<"Fecha Parenteses esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' <<"Ponto e virgula esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
    }*/
}

void AnalisadorSintatico::CompExpressaoAritimetica() throw()
{
    if (this->erro.compare("") != 0)
        return;
    int parentesesNivel = numParenteses;
    TipoPedaco prox = anaLex->verPedaco();
    while(prox == AbreParenteses || prox==Subtracao){
            if(prox==AbreParenteses)
                numParenteses++;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
    }
        CompOperandoInteiro();
        prox = anaLex->verPedaco();
        while(prox == FechaParenteses){
            if(numParenteses==0 && this->NaoHaErro()){
                this->erro = "Parenteses desbalanceados!";
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'<< this->erro;
                return;
            }
            numParenteses--;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
        while(numParenteses>parentesesNivel || EhOperadorAritmetico(prox)){
            if(EhOperadorAritmetico(prox)){
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
            }
            else if (this->NaoHaErro())
			{
                this->erro = "Operador aritm閠ico esperado, mas " + this->anaLex->getLiteral() + " encontrado!";
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'<< this->erro;
                return;
            }
        while(prox == AbreParenteses || prox==Subtracao){
            if(prox==AbreParenteses)
                numParenteses++;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
        if(prox== Numero || prox == Identificador)
        CompOperandoInteiro();
        prox = anaLex->verPedaco();
        while(prox == FechaParenteses && this->NaoHaErro()){
            if(numParenteses==0){
                this->erro = "Parenteses desbalanceados!";
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'<< this->erro;
                return;
            }
            numParenteses--;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
    }
}
void AnalisadorSintatico::CompOperandoInteiro()throw(){
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->verPedaco();

    while(prox == AbreParenteses || prox == Subtracao){
        if(prox == AbreParenteses)
            numParenteses++;
        this->anaLex->proximoPedaco();
        prox = anaLex->verPedaco();
    }

    if(prox == Numero){
        anaLex->proximoPedaco();
        prox = anaLex->verPedaco();
            if(EhOperadorAritmetico(prox)){
                anaLex->proximoPedaco();
                CompExpressaoAritimetica();
            }
            else
                return;
    }
    if(prox == Identificador){
        string id = this->anaLex->getLiteral();
        if(!EhIdDeBool(id)){
            if(EhIdDeVariavel(id)){
                CompChamadaDeVariavel();
            }
            if(EhIdDeFuncao(id)){
                CompChamadaDeFuncao(id);
            }
            prox = anaLex->verPedaco();
            if(EhOperadorAritmetico(prox)){
                anaLex->proximoPedaco();
                CompExpressaoAritimetica();
            }
            else
                return;
        }
        else if (this->NaoHaErro())
		{
            this->erro = "Identificador Inteiro esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
            cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
            return;
        }
    }
	if (prox == Verdadeiro || prox == Falso && this->NaoHaErro()) {
		anaLex->proximoPedaco();
		this->erro = "Expressao que retorna inteiro esperado, mas "+anaLex->getLiteral()+" encontrado !";
		cout ;cout <<'\n' << "Linha atual :" << this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
		return;
	}
}
void AnalisadorSintatico::CompOperandoBooleano()throw(){
	if (this->erro.compare("") != 0)
        return;
        
    bool operandoBool = false;//suboperando bool
    bool primeiraVez = true;
    int parentesesNivel = numParenteses;
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->verPedaco();
    while(prox == AbreParenteses || prox == Negacao){
        if(prox == AbreParenteses)
            numParenteses++;
        this->anaLex->proximoPedaco();
        prox = anaLex->verPedaco();
    }

    if(prox == Verdadeiro || prox == Falso){
        anaLex->proximoPedaco();
        prox = anaLex->verPedaco();

        if(prox==Comparacao || prox == Diferente){
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
            while(prox == AbreParenteses || prox == Negacao){
                if(prox == AbreParenteses)
                    numParenteses++;
                this->anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
            }
            CompOperandoBooleano();
            while(prox==FechaParenteses){
                if(numParenteses==0){
                	if (this->compilandoProcedimento)
                		return;
                		
                	if (this->NaoHaErro())
                	{
                		this->erro = "Parenteses desbalanceados!";
	                    cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
	                    return;
					}                    
                }
                numParenteses--;
                this->anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
            }
            if(numParenteses>parentesesNivel&& parentesesNivel==0 && this->NaoHaErro()){
                this->erro = "Parenteses desbalanceados!";
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
                return;
            }

        }//fim do if prox==comparacao || prox == diferente
    }

    if(EhOperadorLogico(prox))
    {
        anaLex->proximoPedaco();
        CompExpressaoLogica();
    }

    if (prox == Identificador || prox==Numero)
    {
        string id ("");

        if (prox==Identificador)
            id = this->anaLex->getLiteral();

        if (prox==Numero || (prox==Identificador && (!this->EhIdDeBool(id))))
        {//com certeza 茅 expressao relacional
            if(prox==Identificador){
                if(EhIdDeVariavel(id))
                {
                    CompChamadaDeVariavel();
                }

                if(EhIdDeFuncao(id))
                {
                    CompChamadaDeFuncao(id);
                }
            }
            else
            {
                anaLex->proximoPedaco();
            }

            prox = anaLex->verPedaco();
            while(EhOperadorAritmetico(prox))
            {
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
                if(prox == Identificador || prox == Numero)
                {
                    CompOperandoInteiro();
                    prox = anaLex->verPedaco();
                }
                else if (this->NaoHaErro())
                {
                    this->erro = "Inteiro esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
                    cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
                    return;
                }
            }

            if(EhOperadorRelacional(prox))
            {
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
            }
            else if (this->NaoHaErro())
            {
                this->erro = "Operador Inteiro para comparacao esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
                return;
            }

            while(prox == AbreParenteses || prox == Subtracao)
            {
                if(prox == AbreParenteses)
                    numParenteses++;
                this->anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
            }

            CompOperandoInteiro();

            prox = anaLex->verPedaco();
            while(prox==FechaParenteses)
            {
                if(numParenteses==0)
                {
                    if (this->compilandoProcedimento)
                		return;
                		
                	if (this->NaoHaErro())
                	{
                		this->erro = "Parenteses desbalanceados!";
	                    cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
	                    return;
					}                    
                }
                numParenteses--;
                this->anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
            }

            if(EhOperadorLogico(prox))
            {
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
                if(prox == AbreParenteses ||prox == Identificador || prox == Numero ||prox == Verdadeiro|| prox == Falso || prox==Subtracao || prox == Negacao)
                CompExpressaoLogica();
            }

            if(numParenteses>parentesesNivel&& parentesesNivel==0 && this->NaoHaErro())
            {
                this->erro = "Parenteses desbalanceados!";
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
                return;
            }

        }
        else
        {//s贸 operadores booleanos
            if(EhIdDeVariavel(id))
            {
                CompChamadaDeVariavel();
            }
            if(EhIdDeFuncao(id))
            {
                CompChamadaDeFuncao(id);
            }
            prox = anaLex->verPedaco();
            if(prox==Comparacao || prox == Diferente)
            {
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
                while(prox == AbreParenteses || prox == Negacao){
                    if(prox == AbreParenteses)
                        numParenteses++;
                    this->anaLex->proximoPedaco();
                    prox = anaLex->verPedaco();
                }
                CompOperandoBooleano();
                while(prox==FechaParenteses)
                {
                    if(numParenteses==0){
                        if (this->compilandoProcedimento)
                			return;
                			
                		if (this->NaoHaErro())
                		{
                			this->erro = "Parenteses desbalanceados!";
	                        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
	                        return;
						}                    	
                    }
                    numParenteses--;
                    this->anaLex->proximoPedaco();
                    prox = anaLex->verPedaco();
                }

                if(numParenteses>parentesesNivel&& parentesesNivel==0 && this->NaoHaErro())
                {
                    this->erro = "Parenteses desbalanceados!";
                    cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n' << this->erro;
                    return;
                }
            }//fim do if(prox==comparacao || prox == diferente)

            if (EhOperadorLogico(prox))
            {
                anaLex->proximoPedaco();
                CompExpressaoLogica();
            }
        }
    }
}

void AnalisadorSintatico::CompExpressaoLogica() throw()
{
    if (this->erro.compare("") != 0)
        return;
    int parentesesNivel = numParenteses;
    TipoPedaco prox = anaLex->verPedaco();
    while(prox == AbreParenteses || prox==Negacao){
            if(prox==AbreParenteses)
                numParenteses++;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
    }
        CompOperandoBooleano();
        prox = anaLex->verPedaco();
        while(prox == FechaParenteses){
            if(numParenteses==0 && this->NaoHaErro()){
                this->erro = "Parenteses desbalanceados!";
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'<< this->erro;
                return;
            }
            numParenteses--;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
        while(numParenteses>parentesesNivel){
            if(EhOperadorLogico(prox)){
                anaLex->proximoPedaco();
                prox = anaLex->verPedaco();
            }
            else if (this->NaoHaErro())
			{
                this->erro = "Operador logico esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'<< this->erro;
                return;
            }
        while(prox == AbreParenteses || prox==Negacao){
            if(prox==AbreParenteses)
                numParenteses++;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
        if(prox==Identificador || prox == Numero || prox == Verdadeiro || prox == Falso)
        CompOperandoBooleano();
        prox = anaLex->verPedaco();
        while(prox == FechaParenteses){
            if(numParenteses==0 && this->NaoHaErro()){
                this->erro = "Par锚nteses desbalanceados!";
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'<< this->erro;
                return;
            }
            numParenteses--;
            anaLex->proximoPedaco();
            prox = anaLex->verPedaco();
        }
    }
}
void AnalisadorSintatico::CompComandoComposto() throw()
{
    if (this->erro.compare("") != 0)
        return;

    this->nivelDeComandoComposto++;
    anaLex->proximoPedaco();
    int repeticao = 0;
    this->nivelAtual++;
    TipoPedaco prox;
    //bool primeiraVez = true;
    do
    {
        CompComando();
        prox = anaLex->verPedaco();
        repeticao++;
        if (repeticao > 100)
        	do
        	{
        		prox = anaLex->proximoPedaco();
			} while (prox != Fim && anaLex->temMaisPedacos());
        //primeiraVez = false;
    } while (prox != Fim && anaLex->temMaisPedacos());
    if (prox != Fim && this->NaoHaErro()){
        this->erro ="Fim esperado, mas "+this->anaLex->getLiteral()+" encontrado !";
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << this->erro;
        return;
    }
    else
        anaLex->proximoPedaco();
    this->tabela.eliminaNivel(this->nivelAtual);
    this->nivelAtual--;

    this->nivelDeComandoComposto--;
}

bool AnalisadorSintatico::EhStringAlfabetico(const string& identificador) throw()
{
	for (int i = 0; i < identificador.size(); i++)
		if (isdigit(identificador.c_str()[i]))
			return false;
			
	return true;
}

void AnalisadorSintatico::CompDeclaracaoVariavel() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoRetorno tipoVar(SimboloVacuo);
    string id("");
    list<string> lista;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Variavel && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Variavel esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
    	return;
	}
             
    prox = anaLex->proximoPedaco();
             
	id = anaLex->getLiteral();
    
    if ((!this->EhStringAlfabetico(id)) && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador inicia nome com digito:"<<id;
             
        anaLex->proximoPedaco(); //Consome a parte alfab閠ica do identificador
             
    	goto loop;
	}    	
        
    if (prox != Identificador && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
    	return;
	}        
                     
    lista.push_back(id);
    
loop:
    prox = anaLex->verPedaco();
    while (prox != DoisPontos && anaLex->temMaisPedacos())
    {
        prox = anaLex->proximoPedaco();
        if (prox != Virgula && this->NaoHaErro())
        {
        	this->erro = "Ha erro";
        	
        	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << "Virgula esperada, mas "+this->anaLex->getLiteral()+" encontrado!";
            
			return;
		}            
                 
    	prox = anaLex->proximoPedaco();
                 
        id = anaLex->getLiteral();
    
	    if ((!this->EhStringAlfabetico(id)) && this->NaoHaErro())
	    {
	    	this->erro = "Ha erro";
	    	
	    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'	    	
	             << "Identificador inicia nome com digito";
	             
	    	anaLex->proximoPedaco(); //Consome a parte alfab閠ica do identificador
	             
	    	continue;
		}	    	
	             	                     
        if (prox != Identificador && this->NaoHaErro())
        {
        	this->erro = "Ha erro";
        	
        	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << "Identificador esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";  
				 
			return;                       
		}            
	             
        lista.push_back(id);
        prox = anaLex->verPedaco();
    }

    if (anaLex->proximoPedaco() != DoisPontos && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Dois Pontos esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
	}        
    prox = anaLex->verPedaco();
    if (prox == Logico || prox == Inteiro)
    {
        prox = anaLex->proximoPedaco();
        if (prox == Inteiro)
            tipoVar = SimboloInteiro;
        else
            tipoVar = SimboloLogico;
            
        prox = anaLex->proximoPedaco();
        
        if (prox != PontoVirgula && this->NaoHaErro())
        {
        	this->erro = "Ha erro";
        	
        	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << "Ponto e Virgula esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
                 
            return;
		}            
		
        int i(0);

        int tamanhoLista(lista.size());
        for (; i < tamanhoLista; i++)
        {
            id = *(lista.begin());
            Simbolo*simb=new Simbolo(id, this->nivelAtual, tipoVar);

            //Var* variavel = new Var(id, this->nivelAtual, tipoVar);

            this->tabela.guarde(simb);
            lista.pop_front();
        }
        lista.erase(lista.begin(), lista.end());
        return;
    } //nao e uma constante literal
    
    if (this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    
	    cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
	         << "Tipo Primitivo esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
	}       
}

bool AnalisadorSintatico::EhIdDeBool(string nomeSimbolo) throw()
{
    Simbolo *simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);
    bool ehVariavel = this->EhBool(*simbolo);
    return encontrou && ehVariavel;
}

bool AnalisadorSintatico::EhIdDeVariavel(string nomeSimbolo) throw()
{
    Simbolo *simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);
    bool ehVariavel = this->EhVariavel(simbolo);
    return encontrou && ehVariavel ;
}
bool AnalisadorSintatico::EhIdDeProcedimento(string nomeSimbolo) throw()
{
    Simbolo *simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);
    return encontrou && EhMetodo(simbolo) && simbolo->getTipoRetorno()==SimboloVacuo;
}
bool AnalisadorSintatico::EhMetodo(Simbolo* simbolo)throw()
{
    /*try{
        simbolo->teste();
        return true;
    }
    catch(exception){
        return false;
    }*/
    /*string s;
    s = typeid(*simbolo).name();*/
    return simbolo->getTipoSimbolo() == TipoMetodo;

        //(s.compare("Metodo")==0);
   //     !simbolo->teste();
}
bool AnalisadorSintatico::EhIdDeFuncao(string nomeSimbolo) throw()
{
    Simbolo *simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    bool encontrou = this->tabela.encontrar(nomeSimbolo, simbolo);

    return encontrou && EhFuncao(simbolo);
}

bool AnalisadorSintatico::EhOperadorAritmetico(TipoPedaco tipo) throw()
{
    return (tipo == Soma) || (tipo == Subtracao) ||
    (tipo == Multiplicacao) || (tipo == Divisao) ||(tipo == Resto);
}
bool AnalisadorSintatico::EhOperadorLogico(TipoPedaco tipo)throw()
{
    return (tipo == E) || (tipo == Ou);
}
bool AnalisadorSintatico::EhFuncao(Simbolo* simbolo) throw()
{
    return EhMetodo(simbolo) && (simbolo->getTipoRetorno() != SimboloVacuo);
}
bool AnalisadorSintatico::FuncaoRetornaInteiro(Simbolo* simbolo) throw()
{
    return simbolo->getTipoRetorno() == SimboloInteiro && EhMetodo(simbolo);
}
bool AnalisadorSintatico::FuncaoRetornaBool(Simbolo* simbolo) throw()
{
    return simbolo->getTipoRetorno() == SimboloLogico && EhMetodo(simbolo);
}
bool AnalisadorSintatico::EhVariavel(Simbolo* simbolo) throw()
{
    return !EhMetodo(simbolo);
}
bool AnalisadorSintatico::EhInteiro(Simbolo simbolo) throw()
{
    return simbolo.getTipoRetorno() == SimboloInteiro;
}
bool AnalisadorSintatico::EhOperadorRelacional(TipoPedaco tipo) throw()
{
    return tipo == Comparacao || tipo == Maior || tipo == Menor || tipo == Diferente || tipo == MaiorOuIgual || tipo == MenorOuIgual;
}
bool AnalisadorSintatico::EhValorLogico(TipoPedaco tipo) throw()
{
    return tipo == Verdadeiro || tipo == Falso;
}
bool AnalisadorSintatico::EhBool(Simbolo simbolo) throw()
{
    return simbolo.getTipoRetorno() == SimboloLogico;
}
void AnalisadorSintatico::CompChamadaDeVariavel() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->verPedaco();
    if (prox != Identificador && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
    }
    else
    {
        prox = anaLex->proximoPedaco();
    }

    if ((!EhIdDeVariavel(anaLex->getLiteral())) && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador de variavel invalido:"<<this->anaLex->getLiteral();
             
        return;
	}        

    Simbolo *simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    if ((!this->tabela.encontrar(anaLex->getLiteral(), simbolo)) && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Variavel nao foi declarada:"<<this->anaLex->getLiteral();
             
        return;
	}        
//
    prox = anaLex->verPedaco();

    //string nome = anaLex->getLiteral();
    if (prox == Atribuicao)
    {
        prox = anaLex->proximoPedaco();

        if (simbolo->getTipoRetorno() == SimboloInteiro)
        {
            CompOperandoInteiro();
        }
        else if (simbolo->getTipoRetorno() == SimboloLogico)
        {
            CompOperandoBooleano();
        }

        prox = anaLex->proximoPedaco();

        if (prox != PontoVirgula && this->NaoHaErro())
        {
        	this->erro = "Ha erro";
        	
        	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Ponto e virgula esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
             
            return;
		}        
    }
}
void AnalisadorSintatico::CompChamadaDeProcedimento() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Identificador && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
	}        

    string nomeProc = anaLex->getLiteral();

    if ((!EhIdDeProcedimento(nomeProc)) && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador de procedimento esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
	}        

    if (anaLex->proximoPedaco() != AbreParenteses && this->NaoHaErro()) //Era proximoPedaco
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Abre parenteses esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
	}        

	this->compilandoProcedimento = true;

    Simbolo *simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    this->tabela.encontrar(nomeProc, simbolo);
    int qtosParametros = (simbolo)->getQuantosParametros();
    Simbolo parFormal;
    //Simbolo *parReal;
    //string nomeParReal;
    int i;
    //compilar parametros....
    for (i = 0; i < qtosParametros; i++)
    {
        if (i > 0)
            anaLex->proximoPedaco(); //virgula
        parFormal = (simbolo)->getParametro(i);
        //prox = anaLex->verPedaco();
        //if (prox != Identificador)
        //{
        if (parFormal.getTipoRetorno() == SimboloInteiro)
        {
           /* if (prox == Numero)
                goto verif;
            else //tbm pode ser expressao booleana
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                     << "Inteiro esperado, mas "+this->anaLex->getLiteral()+" encontrado!";*/
                CompOperandoInteiro();
        }
        else
        {
            /*if (prox == Verdadeiro || prox == Falso)
                goto verif;
            else //tbm pode ser expressao aritmetica
                cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                     << "Booleano esperado, mas "+this->anaLex->getLiteral()+" encontrado!";*/
                CompOperandoBooleano();
        }
        //}

        /*nomeParReal = anaLex->getLiteral();
        if (!this->tabela.encontrar(nomeParReal, parReal))
            cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << "Identificador nao declarada !";
        //achou o parametro real na tabela de simbolos
        if ((*parReal).getTipoRetorno() != parFormal.getTipoRetorno())
            cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << "Tipo do parametro real e diferente do parametro formal";
        if (EhIdDeFuncao(nomeParReal))
            CompChamadaDeFuncao();
        if (EhIdDeProcedimento(nomeParReal))
            CompChamadaDeProcedimento();
    verif:*/

        if (anaLex->verPedaco() != Virgula && i < qtosParametros - 1 && this->NaoHaErro())
        {
        	this->erro = "Ha erro";
        	
        	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << "Virgula esperada, mas "+this->anaLex->getLiteral()+" encontrado!";
                 
            return;
		}            
    }//fim do for

    if (anaLex->proximoPedaco() != FechaParenteses && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Fecha parenteses esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
             
        return;
	}        

	this->compilandoProcedimento = false;
}
//CompChamadaDeFuncao consome ; se for retorno da pr贸pria funcao
//se for s贸 uma chamada de fora da funcao, nao consome ;
void AnalisadorSintatico::CompChamadaDeFuncao(string nomeFuncEncontrado) throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    string nomeId("");
    if (prox != Identificador && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
	}
        
    if ((!EhIdDeFuncao(nomeFuncEncontrado)) && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador de funcao esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
	}
	        
    if (nomeFuncEncontrado==this->nomeFuncAtual)
    {
        prox = anaLex->proximoPedaco();
        //POR ENQUANTO NaO TEM RECURSaO

        if (prox != Atribuicao && this->NaoHaErro())
        {
        	this->erro = "Ha erro";
        	
        	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << ":= esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
                 
            return;
		}
            
        prox = anaLex->verPedaco();
        if (this->retornoFuncInt)
        {
            CompOperandoInteiro();
        }
        else
        { //funcao retorna bool
            CompOperandoBooleano();
        } //FIM DO IF(FUNCAORETONAINT)
        prox = anaLex->proximoPedaco();
        if (prox != PontoVirgula && this->NaoHaErro())
        {
        	this->erro = "Ha erro";
        	
        	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << "; esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
		}
            
        this->jaRetornou=true;
        return;
    } //FIM DO IF NOME DA FUNcaO e IGUAL AO ENCONTRADO

    if (anaLex->proximoPedaco() != AbreParenteses && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Abre parenteses esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
        
        return;
	}        

    Simbolo *simbolo = new Simbolo("", this->nivelAtual, SimboloVacuo);
    this->tabela.encontrar(nomeFuncEncontrado, simbolo);
    int qtosParametros = (simbolo)->getQuantosParametros();
    Simbolo parFormal;
    /*Simbolo *parReal;
    string nomeParReal;*/
    int i;
    //compilar parametros....
    for (i = 0; i < qtosParametros; i++)
    {
        if (i > 0)
            anaLex->proximoPedaco(); //virgula
        parFormal = (simbolo)->getParametro(i);
        //prox = anaLex->verPedaco();
         if (parFormal.getTipoRetorno() == SimboloInteiro)
         {
		           CompOperandoInteiro();
         }
         else
         {
                CompOperandoBooleano();
         }
       //anaLex->proximoPedaco();
        if (anaLex->verPedaco() != Virgula && i < qtosParametros - 1 && this->NaoHaErro())
        {
        	this->erro = "Ha erro";
        	
        	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << "Virgula esperada, mas "+this->anaLex->getLiteral()+" encontrado!";
                 
            return;
		}            
    }

    if (anaLex->proximoPedaco() != FechaParenteses && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Fecha parenteses esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
             
        return;
	}        
}
void AnalisadorSintatico::CompEnquanto() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Enquanto && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Enquanto esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
    }

    CompOperandoBooleano();

    prox = anaLex->proximoPedaco();
    if (prox != Faca && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Do esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
    }

    prox = anaLex->verPedaco();
    if (prox == Comeco)
    {
        CompComandoComposto();
    }
    else
    {
        CompComando();
    }
}
//sintaxe do nossa declaracao de funcao repeticao de 0 a n
//function + identificador+ (           + [<parametros>] + )+ : boolean/integer + begin + ..
void AnalisadorSintatico::CompFuncao() throw()
{
    if (this->erro.compare("") != 0)
        return;
    TipoPedaco prox = anaLex->proximoPedaco();
    if (prox != Funcao && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Funcao esperada, mas "+this->anaLex->getLiteral()+" encontrado!";
             
        return;
    }

    prox = anaLex->proximoPedaco();
    if (prox != Identificador && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Identificador esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
    }

    string nomeFunc = anaLex->getLiteral();
    this->nomeFuncAtual =nomeFunc;
    std::list<Simbolo> listaParametros;
    //std::list<Simbolo>::iterator it;
    //it = listaParametros.begin();
    int tamanhoLista = 0;

    prox = anaLex->proximoPedaco();
    if (prox != AbreParenteses && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Abre Parenteses esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
    }

    prox = anaLex->verPedaco();
    this->nivelAtual++;
    while (prox == Inteiro || prox == Logico)
    {
        TipoPedaco tipoParametro = prox;
        TipoRetorno retornoParametro;

        switch (tipoParametro)
        {
        case Inteiro:
            retornoParametro = SimboloInteiro;

            break;
        case Logico:
            retornoParametro = SimboloLogico;

            break;
        }

        anaLex->proximoPedaco();
        prox = anaLex->proximoPedaco();

        if (prox != Identificador && this->NaoHaErro())
        {
        	this->erro = "Ha erro";
        	
        	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
                 << "Identificador esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
                 
            return;
		}
            
        Simbolo param(anaLex->getLiteral(), this->nivelAtual, retornoParametro);
        listaParametros.push_back(param);
        tamanhoLista++;
        prox = anaLex->verPedaco();
        switch (prox)
        {
        case FechaParenteses:
            goto foraLoop;
            break;
        case Virgula:
            anaLex->proximoPedaco();
            break;
        default:
        	if (this->NaoHaErro())
        	{
        		this->erro = "Ha erro";
        	
	            cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
	                 << "Virgula ou Fecha Parenteses esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
	                 
	            return;
			}        	        	
        }
        prox = anaLex->verPedaco();

    } //fim do while
foraLoop:
    prox = anaLex->proximoPedaco();
    if (prox != FechaParenteses && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Fecha Parenteses esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
             
        return;
	}
        
    prox = anaLex->proximoPedaco();
    if (prox != DoisPontos && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Dois Pontos esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
             
        return;
	}
        
    prox = anaLex->proximoPedaco();
    if ((!(prox == Inteiro || prox == Logico)) && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Tipo de retorno esperado, mas "+this->anaLex->getLiteral()+" encontrado!";
             
        return;
	}
        
    TipoRetorno retorno;
    switch (prox)
    {
    case Inteiro:
        retorno = SimboloInteiro;
        this->retornoFuncInt = true;
        break;
    case Logico:
        retorno = SimboloLogico;
        this->retornoFuncInt = false;
        break;
    }

    Simbolo *vetor = new Simbolo[tamanhoLista];
    int i;
    for (i = 0; i < tamanhoLista; i++)
    {
        *(vetor + i) = listaParametros.front();
        listaParametros.pop_front();
    }
    this->nivelAtual--;

    Simbolo *funcao = new Simbolo(nomeFunc, this->nivelAtual, vetor, tamanhoLista, retorno);

    prox = anaLex->proximoPedaco();
    if (prox != PontoVirgula && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Ponto e Virgula esperado"<<", mas "<<this->anaLex->getLiteral()<<" encontrado !";
             
        return;
    }
    this->tabela.guarde(funcao);
    prox = anaLex->verPedaco();
    this->nivelAtual++;
    while (prox == Variavel)
    {
        CompDeclaracaoVariavel();
        prox = anaLex->verPedaco();
    }

    while (prox == Procedimento)
    {
        this->nomeFuncAtual="";
        CompProcedimento();
		prox = anaLex->verPedaco();
    }
    while (prox == Funcao)
    {
        this->nomeFuncAtual="";
        CompFuncao();
		prox = anaLex->verPedaco();
    }
    this->nomeFuncAtual =nomeFunc;
    this->retornoFuncInt = retorno == SimboloInteiro;
    this->jaRetornou = false;
    prox = anaLex->verPedaco();
    if (prox != Comeco && this->NaoHaErro()){
        this->erro = "Inicio esperado, mas "+this->anaLex->getLiteral()+" encontrado !";
        
        cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << this->erro;
        return;
    }
    Simbolo *paramAtual;
    for (i = 0; i < tamanhoLista; i++)
    {
        tabela.guarde(vetor + i);
    }
    this->nivelAtual--;
    //comando composto j谩 vai incrementar nivel atual
    CompComandoComposto();

    if ((!jaRetornou && (this->nomeFuncAtual!="")) && this->NaoHaErro())
    {
    	this->erro = "Ha erro";
    	
    	cout ;cout <<'\n'<<"Linha atual :"<< this->anaLex->getLinhaAtual() ;cout <<'\n'
             << "Funcao nao retorna nenhum valor!";
             
        return;
	}
        
    this->nomeFuncAtual="";
    this->jaRetornou = false;
}
