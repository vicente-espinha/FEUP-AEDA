#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Clients.h"
#include "Utilities.h"

using namespace std;

class Corporation
{
private:
	static Corporation* singleton_instance;
	string usersFile;
	string username, password;
	unsigned int nif;
	vector<Users> usersVec;
public:
	static Corporation* instance();
	bool foundUsersFile(string userFiles);
	void loadUsers();
	void saveUsers();
	void registerUser();
};

