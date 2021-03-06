#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <queue>
#include <unordered_set>
#include <malloc.h>


#include "Rent.h"
#include "BSTNew.h"
#include "Clients.h"
#include "Supplier.h"

using namespace std;

struct eqstr {
	bool operator() (const Users &s1,const Users &s2) const {
		return s1 == s2;
	}
};

struct hstr {
	int operator() ( const Users &s1) const {
		int v = 7 * s1.getNif();
		return v%127;
	}
};


typedef tr1::unordered_set<Users, hstr, eqstr> Ash_Users_inactive;



/*! \brief Brief description.
*
* Classe Base that contains every function that changes the information of the suppliers,users,rents and reservations(create,delete,register)
*/
class Corporation
{
private:
	static Corporation* singleton_instance;/*!<  "singleton_instance" instances variables*/
	string usersFile, suppliersFile, rentsFile;/*!< "usersFile" is the file that contais the information about the users,"suppliersFile" is the file that contais the information about the suppliers and "rentsFile" is the file that contais the information about the rents and reservations,*/
	vector<Users> usersVec; /*!<  "usersVec" is the vector that contains the users information*/
	vector<Supplier> suppliersVec;/*!<  "suppliersVec" is the vector that contains the suppliers information*/
	vector<Rent> rentsVec;/*!<  "rentsVec" is the vector that contains the rents and reservations information*/
	priority_queue<Rent> discountsRents;/*!<  "discountsRents" is the priority_queue that contains the rents in order that the first rent is the one which has the most time since last reservation*/
	Ash_Users_inactive usersInactives;/*!<  "usersInactives" is the hash that contains the inactive users*/
	BST<Users> receipt;/*!< "receipt" is the BST that contains the receipts of the users in alphabetical order*/
public:

	string username, supplierName;//!< saves the username and password that were loged in.
	long nif;
	
	static Corporation* instance();//!< a function instances variables.

	void login();//!< a function that logins
	void managmentLogin(); //!< A function used for logging in the manager account

	// PRIORITY_QUEUE

	void createPriorityQueueFromRents();//!< a function that creates and updates the priority_queue "discountsRents"
	vector<Rent> setDiscounts(vector<Rent> v);//!< a function that sets the discounts
	void displayDiscounts();//!< a function that displays the discounts made by the company

	// BST

	void createBST();//!< a function that creates the BST
	void displayBST();//!< a function that displays the Users that the BST has
	bool checkExistance(int nif);

	bool foundUsersFile(string userFiles);//!< a function that checks if the file is correct.
	void loadUsers();//!< a function that saves the information that of the file in the vector
	void saveUsers();//!< a function that saves the information that of the vector in the file
	void registerUser();//!< a function that registers a user

	void printSuppliersRents();//!< a function that prints the suppliers rents
	bool foundSuppliersFile(string suppliersFile);//!< a function that checks if the file is correct.
	void loadSuppliers();//!< a function that saves the information that of the file in the vector
	void saveSuppliers();//!< a function that saves the information that of the vector in the file
	void registerSupplier();//!< a function that registers a supplier
	void orderSuppliersVec();//!< a function that puts in order the suppliersVec
	void orderRentsVec();//!< a function that puts in order the rentsVec
	void makeRent();//!< a function that creates a rent

	string cities();//!< a function that helps you choose the cities
	void printUsersReservations();//!< a function that prints the reservations
	void makeReservation();//!< a function that creates a reservation
	void cancelReservation();//!< a function that cancels the reservation

	bool foundRentsFile(string rentsFile);//!< a function that checks if the file is correct.
	void loadRents();//!< a function that saves the information that of the file in the vector
	void saveRents();//!< a function that saves the information that of the vector in the file

	void deleteRents();//!< a function that deletes the rents


	void createHashUsersInactive();//!< a function that creates or updates the hash that contains the inactive users
	void displayUsersInactive();//!< a function that displays the users that the hash contains
};

