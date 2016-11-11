#include "Corporation.h"

Utilities u1;

Corporation * Corporation::instance()
{

	if (!singleton_instance) {
		singleton_instance = new Corporation;
	}

	return singleton_instance;
}

//Checks existance of the users file
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

//Loads the users file to memory (Users vector)
/*void loadReservations()
{
	string name,name_rent type, type_type, d1, d2;
	unsigned int n_people;
	fstream f;

	f.open("reservations.txt");

	while (!f.eof()) {
	getline(f, line)

		string  name= line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string  name_rent = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string type = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string type_type = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int n_people = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		string d1 = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string d2 = line.substr(0, line.length());

		reservationVec.push_back(Reservation(name, type, type_type, n_people,Date(d1),Date(d2)));
	}
	f.close();
}*/