#include "Corporation.h"

Utilities u1;

template <typename T>
Corporation * Corporation::instance()
{

	if (!singleton_instance) {
		singleton_instance = new Corporation;
	}

	return singleton_instance;
}


//Checks existance of the users file
template <typename T>
bool Corporation::foundUsersFile(string usersFile) {

	fstream f;

	f.open(usersFile);

	if (f.fail()) {
		f.close();
		u1.setColor(12); cerr << "\n  ERROR: " << usersFile << " (users file) could not be found!\n         Verify the directory!\n\n"; u1.setColor(15);
		return false;
	}

	f.close();

	this->usersFile = usersFile;
	return true;
}

//Loads the users file to memory (Users vector)
template <typename T>
void Corporation::loadUsers() {

	string line;
	fstream f;

	f.open(usersFile);
	getline(f, line);

	while (getline(f, line)) {

		string username = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string password = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int nif = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int points = stoi(line.substr(0, line.length()));

		usersVec.push_back(Users(username, password, nif, points));
	}
	f.close();
	return;
}

//Loads memory to the users file
template <typename T>
void Corporation::saveUsers() {

	ofstream f;

	f.open(usersFile, ofstream::app);

	for (size_t i = 0; i < usersVec.size(); i++) {
		f << usersVec[i].getUsername() << " ; " << usersVec[i].getPassword() << " ; " << usersVec[i].getNif() << " ; " << usersVec[i].getPoints() << endl;
	}

	f.close();

	return;
}

//Adds a user to the users vector
template <typename T>
void Corporation::registerUser() {

	cout << "\n Name:  "; getline(cin, username);

	if (cin.eof()) {
		u1.cancelMessage();
		return;
	}

	for (unsigned int index = 0; index != username.size(); index++) {
		if (!isalpha(username[index]) && username[index] != ' ') {
			u1.setColor(12); cerr << "  ERROR: Name must only contain alphabetic characters. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			return;
		}
	}

	cout << "\n Password:  "; cin >> password;
	u1.cinClear();
	cout << "\n NIF:  "; cin >> nif;
	u1.cinClear();

	if (cin.eof()) {
		u1.cancelMessage();
		return;
	}

	usersVec.push_back(Users(username, password, nif, 0));

	for (size_t i = 0; i < usersVec.size(); i++) {
		cout << usersVec[i].getUsername() << " ; " << usersVec[i].getPassword() << " ; " << usersVec[i].getNif() << " ; " << usersVec[i].getPoints() << endl;
	}

	u1.clearScreen();
	return;
}


template <typename T>
void Corporation::registerSupplier()
{
	bool isIn = true;
	
	string n, ad;
	unsigned int nif;
	vector<Rent<T>> v;
	while (isIn)
	{
		cout << "What is your name?\nName: ";
		cin >> n;
		cout << "\nWhat is your FIN? (Fiscal Identification Number)\nFIN : ";
		cin >> nif;
		if (invalidInputRetry())
			continue;
		else
		{
			cout << "\nThe program will now return.\n";
			isIn = false;
			return;
		}
		isIn = false;
	}

	isIn = true;

	while (isIn)
	{

	}


	/*
	string name, address;
	unsigned int nif;
	vector<Rent<T>> v;
	*/



	
}