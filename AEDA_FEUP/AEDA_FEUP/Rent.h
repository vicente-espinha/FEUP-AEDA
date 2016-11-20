#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"
#include "Date.h"
#include "Clients.h"
#include "Reservations.h"

using namespace std;


/*
A FAZER:

2 - No menu, tem que haver dois tipos de acessos, um de fornecedor e outro de clientes. O Fornecedor serve para adicionar
alugueres, o de clientes para pesquisar e reservar possibilidades de acordo com os alugueres disponiveis


*/

class Rent
{
protected:

	// Todas estas variaveis sao comuns a todos os alugueres, por isso é que as ponho aqui
	long nif;
	string city;                // Pretty obvious, I guess
	Date dataBegin, dataEnd;    // Será melhor pormos a data como float ou whatevs? Acho melhor
								// assim por causa da extracao de um istream;
								// Outra cena, é dataInicio e fim porque o fornecedor tem de explicitar
								// quais sao as datas em que o aluguer esta disponivel;
	string name;
	float price;
	int numPeople;              // O numero de pessoas que vai para um determinado aluguer, (quarto duplo, triplo, etc...)
	string typeRent;
	string type;
	vector<Reservation> reserved;
public:
	Rent() {}
	virtual bool isValid(Date, Date);

	virtual long getNif() { return nif; }
	virtual void setNif(int n) { nif = n; }
	Rent(long nif, string tipoRent, string name2, string cidade, Date dataI, Date dataF, float price, int numOcupantes);
	virtual void setReservation(Reservation r) { reserved.push_back(r); }
	virtual vector<Reservation> getReservations() { return reserved; }
	virtual void setReservationVector(vector<Reservation>v) { reserved = v; }
	virtual int getNumPeople() { return numPeople;  }
	virtual float getPrice() { return price; }
	virtual string getCity() { return city; }
	virtual Date getDataInicio() { return dataBegin; }
	virtual Date getDataFim() { return dataEnd; }
	auto buildRent(int nif) {}
	virtual string getTypeRent() { return typeRent; }
	virtual string getName() { return name; }
	virtual string getType() { return type; }
	virtual int getNumRooms() { int i =0; return i; }
	virtual bool getKitchen() {bool i = true; return i; }
	virtual bool getSuite() { bool x = true; return x; }
	virtual bool getLivingRoom() { bool x = true; return x; }
};

class Hotel : public Rent
{
	string nameHotel;               // Podera ser utilizado para, apos fazer sort ao vetor de aluguer, fazer display bonito
	int numPeople;                  // Definido pelo tipo de aluguer que é
                   // Tipo de Quarto que quer
	
public:
	Hotel(){ }
	Hotel(long nif, string typeRent, string nome, string cidade, Date dataI, Date dataF, string type, float preco, int numOcupantes);
	string getType() { return type; }
	string getName() { return nameHotel; }
	Hotel buildRent(long nif); // Pressupostamente constroi um hotel, mas ainda tenho que pensar como implementar isto
	
};


class bedNbreakfast : public Rent
{
protected:
	string namebnb;
public:
	bedNbreakfast(){}
	bedNbreakfast(long nif, string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes);
	bedNbreakfast buildRent(long nif);
	string getName() { return  namebnb; }
};


class sharedHouse : public Rent
{
protected:
	string nameSH;
public:
	sharedHouse() {}
	sharedHouse(long nif, string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes);
	sharedHouse buildRent(long nif);
	string getName() { return nameSH; }
};


class flat : public Rent
{
protected:
	string nameFlat;
	bool hasKitchen;
public:
	flat() {}
	flat(long nif, string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes);
	flat buildRent(long nif);
	bool getKitchen() { return hasKitchen; }
	string getName() { return nameFlat; }
};

class apartment : public Rent
{
protected: 
	string nameApartment;
	int numRooms;
	bool hasKitchen, hasSuite, hasLivingRoom;
public:
	apartment() {}
	apartment(long nif, string tipoRent, string name, string cidade, Date dataI, Date dataF, float price, int numOcupantes, int numrooms, bool kitchen, bool suite, bool livingroom);
	apartment buildRent(long nif);
	string getName() { return nameApartment; }
	int getNumRooms() { return numRooms; }
	bool getKitchen() { return hasKitchen; }
	bool getSuite() { return hasSuite; }
	bool getLivingRoom() { return hasLivingRoom; }
};
