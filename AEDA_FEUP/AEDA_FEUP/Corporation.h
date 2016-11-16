#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Clients.h"
#include "Supplier.h"
#include "Utilities.h"
#include "Reservations.h"
#include "Menu.h"


using namespace std;

class Corporation
{
private:
	static Corporation* singleton_instance;
	string usersFile, suppliersFile, reservationsFile,rentsFile;
	vector<Users> usersVec;
	vector<Reservation>reservationsVec;
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
	void addRentToSupplier(Supplier s);
	void registerSupplier();
	void makeRent();
	void printSuppliers();

	bool foundReservationsFile(string reservationsFile);
	//void makeReservation();
	//void loadReservations();
	//void saveReservations();
	//void cancelReservation();

	bool foundRentsFile(string rentsFile);
	void loadRents();
};

