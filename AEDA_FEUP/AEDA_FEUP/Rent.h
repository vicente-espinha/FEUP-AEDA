#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"
#include "Date.h"
#include "Clients.h"
#include "Reservations.h"

using namespace std;



/*! \brief Brief description.
*
* Classe made for the rents (mother class)
*/
class Rent
{
protected:

	// Todas estas variaveis sao comuns a todos os alugueres, por isso é que as ponho aqui
	long nif; /*!< "nif" is the numero de identificacao fiscal do Supplier*/
	string city;/*!< "city" is the city that you want to make a rent*/
	Date dataBegin, dataEnd;/*!< "dataBegin" is the date of begin of rent and "dataEnd" is the date of the end of the rent*/
	string name;/*!< "name" is the name of the rent*/
	float price;/*!< "price" is the price of the rent per night*/
	int numPeople;/*!< "numPeople" is the number of people that will be in rent*/
	string typeRent;/*!< "typeRent" is type of the rent (example:hotel,flat...)*/
	string type;/*!< "type" is the specification of the "typeRent"*/
	vector<Reservation> reserved;/*!< "reserved" is the vector of reservations*/
public:
	Rent() {}
	virtual bool isValid(Date, Date);//!< a function that checks if dates are valid
	int lastRent() const;
	bool operator<(const Rent x) const;
	virtual long getNif() { return nif; }//!< a function that returns nif of supplier
	virtual void setNif(int n) { nif = n; }//!< a function that sets nif
	virtual void setPrice(float n) { price = n; }//!< a function that sets price
	Rent(long nif, string tipoRent, string name2, string cidade, Date dataI, Date dataF, float price, int numOcupantes);
	virtual void setReservation(Reservation r) { reserved.push_back(r); }//!< a function that adds reservation to "reserved"
	virtual vector<Reservation> getReservations() { return reserved; }//!< a function that returns the vector of reservations
	virtual void setReservationVector(vector<Reservation>v) { reserved = v; }//!< a function that sets the "reserved"
	virtual int getNumPeople() { return numPeople;  }//!< a function that returns number of people
	virtual float getPrice() const { return price; }//!< a function that returns the price
	virtual string getCity() { return city; }//!< a function that returns the city
	virtual Date getDataInicio() { return dataBegin; }//!< a function that returns the date of begin
	virtual Date getDataFim() { return dataEnd; }//!< a function that returns the date of end
	auto buildRent(int nif) {}//!< a function that builds rent
	virtual string getTypeRent() { return typeRent; }//!< a function that returns the typeRent
	virtual string getName() { return name; }//!< a function that returns the name
	virtual string getType() { return type; }//!< a function that returns the Type
	virtual int getNumRooms() { int i =0; return i; }//!< a function that returns the number of rooms
	virtual bool getKitchen() {bool i = true; return i; }//!< a function that returns true if has kitchen, if not returns false
	virtual bool getSuite() { bool x = true; return x; }//!< a function that returns true if has Suite, if not returns false
	virtual bool getLivingRoom() { bool x = true; return x; }//!< a function that returns true if has LivingRoom, if not returns false

};


/*! \brief Brief description.
*
* Classe made for the hotels(rents)
*/
class Hotel : public Rent
{
	string nameHotel;/*!< "nameHotel" is name of the hotel(rent)*/   
	int numPeople;/*!< "numPeople" is the number of people that will be in rent*/

	
public:
	Hotel(){ }
	Hotel(long nif, string typeRent, string nome, string cidade, Date dataI, Date dataF, string type, float preco, int numOcupantes);
	string getType() { return type; }//!< a function that returns the Type
	string getName() { return nameHotel; }//!< a function that returns the name
	Hotel buildRent(long nif); //!< a function that builds rent
	
};

/*! \brief Brief description.
*
* Classe made for the bedNbreakfast(rents)
*/
class bedNbreakfast : public Rent
{
protected:
	string namebnb;/*!< "namebnb" is name of the bedNbreakfast(rent)*/   
public:
	bedNbreakfast(){}
	bedNbreakfast(long nif, string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes);
	bedNbreakfast buildRent(long nif);//!< a function that builds rent
	string getName() { return  namebnb; }//!< a function that returns the name
};

/*! \brief Brief description.
*
* Classe made for the sharedHouse(rents)
*/
class sharedHouse : public Rent
{
protected:
	string nameSH;/*!< "nameSH" is name of the sharedHouse(rent)*/   
public:
	sharedHouse() {}
	sharedHouse(long nif, string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes);
	sharedHouse buildRent(long nif);//!< a function that builds rent
	string getName() { return nameSH; }//!< a function that returns the name
};

/*! \brief Brief description.
*
* Classe made for the flat(rents)
*/
class flat : public Rent
{
protected:
	string nameFlat;/*!< "nameFlat" is name of the flat(rent)*/   
	bool hasKitchen;/*!< "haskitchen" is bool and checks if it has or not a kitchen*/   
public:
	flat() {}
	flat(long nif, string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes);
	flat buildRent(long nif);//!< a function that builds rent
	bool getKitchen() { return hasKitchen; }//!< a function that returns true if has kitchen, if not returns false
	string getName() { return nameFlat; }//!< a function that returns the name
};

/*! \brief Brief description.
*
* Classe made for the apartment(rents)
*/
class apartment : public Rent
{
protected: 
	string nameApartment;/*!< "nameApartment" is name of the apartment(rent)*/ 
	int numRooms;/*!< "numRooms" is the number of rooms that the apartment has*/  
	bool hasKitchen, hasSuite, hasLivingRoom;/*!< "haskitchen", "hasSuite" and "hasLivingRoom" are bool and checks if it has or not, a kitchen or a Suite or a LivingRoom*/  
public:
	apartment() {}
	apartment(long nif, string tipoRent, string name, string cidade, Date dataI, Date dataF, float price, int numOcupantes, int numrooms, bool kitchen, bool suite, bool livingroom);
	apartment buildRent(long nif);//!< a function that builds rent
	string getName() { return nameApartment; }//!< a function that returns the name
	int getNumRooms() { return numRooms; }//!< a function that returns the number of rooms
	bool getKitchen() { return hasKitchen; }//!< a function that returns true if has kitchen, if not returns false
	bool getSuite() { return hasSuite; }//!< a function that returns true if has Suite, if not returns false
	bool getLivingRoom() { return hasLivingRoom; }//!< a function that returns true if has LivingRoom, if not returns false
};
