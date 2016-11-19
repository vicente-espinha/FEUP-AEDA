#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Clients.h"
#include "Supplier.h"
#include "Utilities.h"
#include "Menu.h"
#include <malloc.h>


using namespace std;
/*! \brief Brief description.
*
*  
*/
class Corporation
{
private:
	static Corporation* singleton_instance;
	string usersFile, suppliersFile,rentsFile;
	vector<Users> usersVec;
	vector<Supplier> suppliersVec;
	vector<Rent> rentsVec;

	
public:
	string username, supplierName;

	static Corporation* instance();

	void login();

	bool foundUsersFile(string userFiles);
	void loadUsers();
	void saveUsers();
	void registerUser();


	bool foundSuppliersFile(string suppliersFile);
	void loadSuppliers();
	void saveSuppliers();
	void registerSupplier();
	void orderSuppliersVec();
	void orderRentsVec();
	void makeRent();
	
	string cities();

	//void makeReservation();
	void cancelReservation();

	bool foundRentsFile(string rentsFile);
	void loadRents();
};

