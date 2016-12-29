#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "Clients.h"
#include "Supplier.h"
#include "Utilities.h"
#include "Menu.h"
#include "BST.h"
#include "Rent.h"
#include <malloc.h>


using namespace std;
<<<<<<< HEAD

/*! \brief Brief description.
*
* struct that contains the equal function needed for the hash
*/
struct eqstr {
	bool operator() (const Users &s1,const Users &s2) const {
		return s1 == s2;
	}
};


/*! \brief Brief description.
*
* struct that contains the hash function
*/
struct hstr {
	int operator() ( const Users &s1) const {
		int v = 7 * s1.getNif();
		return v%127;
	}
};


typedef tr1::unordered_set<Users, hstr, eqstr> Ash_Users_inactive;



=======
>>>>>>> parent of 4dfd8db... tabela de dispersão ainda incompleto
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
	priority_queue<Rent> discountsRents;
<<<<<<< HEAD
	Ash_Users_inactive usersInactives; /*!<  "Ash_Users_inactive" is the ash that contains inactive users (havent made a reservation in 60 or more days) */
	BST<Reservation> bills;
=======
>>>>>>> parent of 4dfd8db... tabela de dispersão ainda incompleto

public:
	string username, supplierName;//!< saves the username and password that were loged in.
	
	void createPriorityQueueFromRents();
	vector<Rent> setDiscounts(vector<Rent> v);
	void displayDiscounts();

	static Corporation* instance();//!< a function instances variables.

	void login();//!< a function that logins

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
<<<<<<< HEAD

	void addBill(const Reservation &r1);
	void createHashUsersInactive();//!< a function that creates a hash containing the users that havent made a reservation in more than 60 days
	void displayUsersInactive();//!< a function that displays the users that are in the hash usersInactives;

	void displayBST();

=======
>>>>>>> parent of 4dfd8db... tabela de dispersão ainda incompleto
};

