#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Utilities.h"
#include "Date.h"

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

template <typename T>	 // IMPORTANTE!!! A função buildRent retorna objetos da classe respetiva, i.e. Hotel retorna Hotel e whatnot
class Rent
{
protected:

	// Todas estas variaveis sao comuns a todos os alugueres, por isso é que as ponho aqui
	string city;                // Pretty obvious, I guess
	Date dataBegin, dataEnd;    // Será melhor pormos a data como float ou whatevs? Acho melhor
								// assim por causa da extracao de um istream;
								// Outra cena, é dataInicio e fim porque o fornecedor tem de explicitar
								// quais sao as datas em que o aluguer esta disponivel;

	
	int numPeople;              // O numero de pessoas que vai para um determinado aluguer, (quarto duplo, triplo, etc...)
	
public:
	Rent(string tipoRent, string cidade, Date dataI, Date dataF, int numOcupantes);
	virtual int getNumOcupantes() {}
	Date getDataInicio() { return dataBegin; }
	Date getDataFim() { return dataEnd; }
	virtual T buildRent() {}
};

template <typename T>
class Hotel : public Rent<T>
{
	string nameHotel;               // Podera ser utilizado para, apos fazer sort ao vetor de aluguer, fazer display bonito
	int numPeople;                  // Definido pelo tipo de aluguer que é
	string type;                    // Tipo de Quarto que quer
	float price;
public:
	Hotel(string typeRent, string nome, string cidade, Date dataI, Date dataF, string tipo, float preco, int numOcupantes);
	string getType() { return type; }

	string getName() { return nameHotel; }
	float getPrice() { return price; }
	T buildRent(); // Pressupostamente constroi um hotel, mas ainda tenho que pensar como implementar isto
	
};

template <typename T>
class bedNbreakfast : public Rent<T>
{
protected:
	string namebnb;
public:
	bedNbreakfast(string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes);
	T buildRent();
	string getName() { return  namebnb; }
};

template<typename T>
class sharedHouse : public Rent<T>
{
protected:
	string nameSH;
public:
	sharedHouse(string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes);
	T buildRent();
};

template<typename T>
class flat : public Rent<T>
{
protected:
	string nameFlat;
	bool hasKitchen;
public:
	flat(string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes);
	T buildRent();
};


