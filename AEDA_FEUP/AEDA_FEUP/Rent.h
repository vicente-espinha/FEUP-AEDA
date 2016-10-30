#pragma once

/*
* Aluguer.h
*
*  Created on: 22/10/2016
*      Author: angrydodo
*/

#include "Date.h"
#include <iostream>
#include <string>
#include <vector>
#include "Utilities.h" // Tem a função invalidInput

using namespace std;


/*
A FAZER:

2 - No menu, tem que haver dois tipos de acessos, um de fornecedor e outro de clientes. O Fornecedor serve para adicionar
alugueres, o de clientes para pesquisar e reservar possibilidades de acordo com os alugueres disponiveis

3 - Classes que faltam do aluguer

5 - Criar uma classe de Fornecedores, que tem um vetor de alugueres, e informacao. Mais concretamente:
" Quando um fornecedor se regista no sistema, deve incluir os seus dados (nome, NIF, morada), e a lista de ofertas
que deseja disponibilizar, com as respectivas características"

7 - Panisguices incrivelmente bonitas!

*/

//template <class T>	 // IMPORTANTE!!! A função buildRent retorna objetos da classe respetiva, i.e. Hotel retorna Hotel e whatnot
class Rent
{
protected:

	// Todas estas variaveis sao comuns a todos os alugueres, por isso é que as ponho aqui
	string city;                // Pretty obvious, I guess
	Date dataBegin, dataEnd;    // Será melhor pormos a data como float ou whatevs? Acho melhor
								// assim por causa da extracao de um istream;
								// Outra cena, é dataInicio e fim porque o fornecedor tem de explicitar
								// quais sao as datas em que o aluguer esta disponivel;

	int durationRent;		    // Estas duas trabalham juntas, porque o fornecedor tem de dizer quanto
						        // tempo uma pessoa pode ter um determinado aluguer, funcionando do género
								// "A duração do aluguer será em noites, semanas, ou meses?" , extrai para o tipoEstadia
								// "Quantos noites/semanas/meses serão? " texto varia com tipoEstadia, extrai para duracaoEstadia

	int numPeople;              // O numero de pessoas que vai para um determinado aluguer, (quarto duplo, triplo, etc...)
	
public:
	Rent(string cidade, Date dataI, Date dataF, int duracao, int numOcupantes);

	virtual void getNome() {}        // getNome do Hotel, nao faz sentido as outras classes terem nomes
	virtual int getNumOcupantes() {}
	Date getDataInicio() { return dataBegin; }
	Date getDataFim() { return dataEnd; }
	int getDuracao() { return durationRent; }
	virtual T buildRent() {}
};


class Hotel : public Rent
{
	string nameHotel;               // Podera ser utilizado para, apos fazer sort ao vetor de aluguer, fazer display bonito
	int numPeople;                  // Definido pelo tipo de aluguer que é
	string type;                    // Tipo de Quarto que quer
	float price;
public:
	Hotel(string nome, string cidade, Date dataI, Date dataF, string tipo, int duracao, float preco, int numOcupantes);
	string getType() { return type; }

	string getName() { return nameHotel; }
	float getPrice() { return price; }
	void buildRent(); // Pressupostamente constroi um hotel, mas ainda tenho que pensar como implementar isto
	
};


