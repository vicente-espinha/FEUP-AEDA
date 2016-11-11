#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Clients.h"
#include "Utilities.h"
<<<<<<< HEAD
#include "Rent.h"
#include "Supplier.h"

=======
#include "Reservations.h"
#include "Date.h"
#include "Rent.h"
>>>>>>> origin/master

using namespace std;

class Corporation
{
private:
	static Corporation* singleton_instance;
	string usersFile;
	string username, password;
	unsigned int nif;
	vector<Users> usersVec;
<<<<<<< HEAD
	vector<Supplier> suppliersVec;
=======
	//template<typename T>
	//vector<Reservation<T>>reservationVec;
	//template<typename T>
	//vector<Rent<T>>rentsVec;
>>>>>>> origin/master
public:
	static Corporation* instance();
	bool foundUsersFile(string userFiles);
	//void loadReservations();
	void loadUsers();
	void saveUsers();
	void registerUser();
<<<<<<< HEAD

	void loadSuppliers();
	void saveSuppliers();
	void registerSuppliers();

=======
	//void makeReservation();
>>>>>>> origin/master
};

