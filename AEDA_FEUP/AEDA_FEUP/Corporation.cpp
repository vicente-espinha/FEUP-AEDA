#include "Corporation.h"

Utilities u1;
Menu corpMenu;
//Hotel h;
//bedNbreakfast bnb;
//sharedHouse sh;
//apartment ap;
//flat fl;

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

	string password, nif;

	cout << "\n Name:  "; getline(cin, username);

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}

	for (unsigned int index = 0; index != username.size(); index++) {
		if (!isalpha(username[index]) && username[index] != ' ') {
			u1.setColor(12); cerr << "  ERROR: Name must only contain alphabetic characters. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	for (unsigned int index2 = 0; index2 != usersVec.size(); index2++) {
		if (usersVec.at(index2).getUsername() == username) {
			u1.setColor(12); cerr << "  ERROR: The username you selected already exists. Please choose another one. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	cout << "\n Password:  "; cin >> password;

	u1.cinClear();

	for (unsigned int index3 = 0; index3 != password.size(); index3++) {
		if (!isalnum(password[index3])) {
			u1.setColor(12); cerr << "  ERROR: Password cannot contain special characters. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	cout << "\n NIF:  "; cin >> nif;
	u1.cinClear();

	for (unsigned int index4 = 0; index4 != nif.size(); index4++) {
		if (!isdigit(nif[index4]) && username[index4] != ' ') {
			u1.setColor(12); cerr << "  ERROR: NIF can only contain digits. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	for (unsigned int index5 = 0; index5 != usersVec.size(); index5++) {
		if (usersVec.at(index5).getNif() == stoi(nif)) {
			u1.setColor(12); cerr << "  ERROR: The NIF you selected already exists. Probably you already have an account. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}

	}

	if (nif.size() != 9) {
		u1.setColor(12); cerr << "  ERROR: The NIF must have 9 digits. "; u1.setColor(15);
		Sleep(3000);
		u1.clearScreen();
		corpMenu.RegisterMenu();
	}

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}

	usersVec.push_back(Users(username, password, stoi(nif), 0));
	u1.clearScreen();
	return;
}

bool Corporation::foundSuppliersFile(string suppliersFile){

	fstream f;

	f.open(suppliersFile);

	if (f.fail()) {
		f.close();
		u1.setColor(12); cerr << "\n  ERROR: " << suppliersFile << " (suppliers file) could not be found!\n         Verify the directory!\n\n"; u1.setColor(15);
		return false;
	}

	f.close();

	this->suppliersFile = suppliersFile;
	return true;
}

void Corporation::loadSuppliers(){

	string line;
	fstream f;

	f.open(suppliersFile);

	while (getline(f, line)) {

		string supplierName = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string password = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int nif = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		string address = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int points = stoi(line.substr(0, line.length()));

		//suppliersVec.push_back(Suppliers(username, password, nif, points));
	}
	f.close();
	return;

}

//Loads suppliersVec to the .txt file
void Corporation::saveSuppliers()
{
	ofstream f;

	f.open("suppliers.txt", ofstream::app);

	/*for (size_t i = 0; i < suppliersVec.size(); i++) {
		f << suppliersVec[i].getName() << " ; " << suppliersVec[i].getAddress() << " ; " << suppliersVec[i].getNif() << " ; ";
		for (int j = 0; j < suppliersVec[i].getVector().size(); j++)
		{		}	//f << suppliersVec[i].getVector()[j].
	}*/

	f.close();
}

//Adds a supplier to the suppliers vector
void Corporation::registerSupplier()
{
	/*bool isIn = true;
	u1.clearScreen();
	string n, ad;
	unsigned int nif;
	while (isIn)
	{
		cout << "What is your name?\nName: ";
		cin >> n;
		cout << "\nWhat is your FIN? (Fiscal Identification Number)\nFIN : ";
		cin >> nif;
		if (u1.invalidInputRetry())
			continue;
		if (!u1.invalidInputRetry())
		{
			isIn = false;

		}
		else
		{
			cout << "\nThe program will now return.\n";
			isIn = false;
			return;
		}
		isIn = false;
	}

	isIn = true;

	cout << "\nWhat is your address?\n";
	cin >> ad;

	int numIteration;
	vector<Rent> v;
	int choice;

	for (int i = 0; i < numIteration; i++)
	{
		u1.clearScreen();
		cout << "What is the type of rent? \n1 - Hotel\n2 - Bed'n'Breakfast\n3 - Apartment\n4 - Flat\n5 - Apartment\n6 - Shared House";
		cin >> choice;

		if (u1.invalidInputRetry())
		{
			i--;
			continue;
		}
		if (!u1.invalidInputRetry())
		{
			i = numIteration;
			break;
		}

		switch (choice)
		{
		case 1:
			//v.push_back(h.buildRent());
			break;
		case 2:
			//v.push_back(bnb.buildRent());
			break;
		case 3:
			//v.push_back(ap.buildRent());
			break;
		case 4:
			//v.push_back(fl.buildRent());
			break;
		case 5:
			//v.push_back(ap.buildRent());
			break;
		case 6:
			//v.push_back(sh.buildRent());
			break;
		}
	}

	cout << "\n\nThe program will now return to the main menu.\n\n";

	
	//suppliersVec.push_back(Supplier(n,ad,nif,v));
	return;*/

}

//Loads the users file to memory (Users vector)
/*
void Corporation::loadReservations()
{
	string name,name_rent type, type_type, d1, d2;
	unsigned int n_people;
	fstream f;
	Rent<T> *c;

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

		for (int i = 0; i < rentsVec.size(); i++)
		{
			if (name_rent == rentsVec.at(i).getName())
				c = rentsVec.at(i).getName();
		}


		reservationVec.push_back(Reservation(name, type, type_type, n_people,Date(d1),Date(d2),c));
	}
	f.close();
}*/

/*void Corporation::makeReservation()
{
	string city;
	cout << "City : ";
	getline(cin, city);

	cout << "List of possibilities : " << endl;
	for (int i = 0; i < rentsVec; i++)
	{
		if(city == rentsVec.at(i).getCity())
		cout << " -> " << rentsVec.at(i) << endl;
	}

	string d1, d2,name_rent;
	Rent<T> c;

	cout << " Name of the Rent Place : ";
	getline(cin, name_rent);

	for (int i = 0; i < rentsVec.size(); i++)
	{
		int n_people;

		cout << "Number of persons : ";
		cin >> n_people;

		if (n_people > rentsVec.at(i).getNumOcupantes())
		{
			cout << "Invalid number of persons." << endl;
			break;
		}

		if (name_rent == rentsVec.at(i).getName())
		{
			cout << " Date of check-in : ";
			getline(cin, d1);
			cout << "Date of check-out : ";
			getline(cin, d2);

			Date d1 = Date(d1);
			Date d2 = Date(d2);

			if (d1 >= rentsVec.at(i).getDataInicio() && d2 <= rentsVec.at(i).getDataFim())
			{
				string answer;
				cout << rentsVEc.at(i) << endl << "Do you want to confirm? ";
				if (answer == "yes" || answer == "Yes")
				{
					reservationsVec.push_back(Reservation())
						break;
				}
				else
					continue;
			}
			else
				cout << "invalid period of time" << endl;
		}
	}



}*/
