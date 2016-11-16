#include "Corporation.h"

using namespace std;

Utilities u1;
Menu corpMenu;



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

	cout << "\n Name:  ";
	getline(cin, username);

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

bool Corporation::foundSuppliersFile(string suppliersFile) {

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

void Corporation::loadSuppliers() {

	string line;
	fstream f;

	vector<Rent> rent;
	f.open(suppliersFile);


	while (getline(f, line)) {
		cout << "Cenas maradas\n";
		string supplierName = line.substr(0, line.find(" ; "));
		cout << "Cenas maradas\n"; line.erase(0, line.find(" ; ") + 3);
		string password = line.substr(0, line.find(" ; "));
		cout << "Cenas maradas\n"; line.erase(0, line.find(" ; ") + 3);
		cout << "Cenas maradas\n"; unsigned int nif = stoi(line.substr(0, line.find(" ; ")));
		cout << "Cenas maradas\n"; line.erase(0, line.find(" ; ") + 3);
		string address = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string typeRent = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		if (typeRent == "Hotel") {
			string nameHotel = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			string city = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startDay = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startMonth = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endDay = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endMonth = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			string roomType = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			float price = stof(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int numPeople = stoi(line.substr(0, line.length()));
		
			rent.push_back(Hotel(typeRent, nameHotel, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), roomType, price, numPeople));
			suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
		
		}
		else if (typeRent == "Bed'n'Breakfast") {
			string nameBB = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			string city = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startDay = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startMonth = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endDay = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endMonth = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			float price = stof(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int numPeople = stoi(line.substr(0, line.length()));

			rent.push_back(bedNbreakfast(typeRent, nameBB, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
			suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));

		}
		else if (typeRent == "Shared House") {
			string nameSH = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			string city = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startDay = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startMonth = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endDay = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endMonth = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			float price = stof(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int numPeople = stoi(line.substr(0, line.length()));

			rent.push_back(sharedHouse(typeRent, nameSH, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
			suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));

		}
		else if (typeRent == "Flat") {
			string nameFlat = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			string city = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startDay = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startMonth = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endDay = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endMonth = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			float price = stof(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int numPeople = stoi(line.substr(0, line.length()));

			rent.push_back(flat(typeRent, nameFlat, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
			suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));

		}
		else if (typeRent == "Apartment") {
			/*string nameApartment = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			string city = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startDay = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startMonth = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endDay = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endMonth = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			float price = stof(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int numPeople = stoi(line.substr(0, line.length()));

			rent.push_back(flat(typeRent, nameApartment, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
			suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));

		}*/
		}
		f.close();
		return;

	}
}

//Loads suppliersVec to the .txt file
void Corporation::saveSuppliers()
{
	ofstream f;

	f.open("suppliers.txt", ofstream::app);

	for (size_t i = 0; i < suppliersVec.size(); i++) {
		f << suppliersVec[i].getName() << " ; " << suppliersVec[i].getPassword() << " ; " << suppliersVec[i].getNif() << " ; " << suppliersVec[i].getAddress() << "; ";
		for (int j = 0; j < suppliersVec[i].getVector().size(); j++)
		{
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Hotel")
			{
				cout << "Saving Hotel...\n";
				cout << "Completed!\n";
				f << "Hotel ; " << suppliersVec[i].getVector()[j].getName() << " ; " << suppliersVec[i].getVector()[j].getCity() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getType() << " ; " << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << "\n";
				cout << "Completed!\n";
			}

			if (suppliersVec[i].getVector()[j].getTypeRent() == "Bed'n'Breakfast")
			{
				cout << "Saving Bed'n'Breakfast...\n";
				f << "Bed'n'Breakfast ; " << suppliersVec[i].getVector()[j].getName() << " ; " << suppliersVec[i].getVector()[j].getCity() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << "\n";
				cout << "Completed!\n";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Shared House")
			{
				cout << "Saving Shared House...\n";
				f << "Shared House ; " << suppliersVec[i].getVector()[j].getName() << " ; " << suppliersVec[i].getVector()[j].getCity() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << "\n";
				cout << "Completed!\n";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Flat")
			{
				cout << "Saving Flat...\n";
				f << "Flat ; " << suppliersVec[i].getVector()[j].getName() << " ; " << suppliersVec[i].getVector()[j].getCity() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << "\n";
				cout << "Completed!\n";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Apartment")
			{
				cout << "Saving Apartment...\n";
				f << "Apartment ; " << suppliersVec[i].getVector()[j].getName() << " ; " << suppliersVec[i].getVector()[j].getCity() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << " ; ";
				f << suppliersVec[i].getVector()[j].getNumRooms() << " ; ";
				f << suppliersVec[i].getVector()[j].getKitchen() << " ; " << suppliersVec[i].getVector()[j].getSuite() << " ; " << suppliersVec[i].getVector()[j].getLivingRoom() << "\n";
				cout << "Completed!\n";
			}

		}
	}

	f.close();
}

//Adds a supplier to the suppliers vector
void Corporation::addRentToSupplier(Supplier s)
{
	bool isIn;

	isIn = true;
	int numIteration;
	
	while (isIn)
	{
		cout << "\nHow many rents do you wish to be made available?\n";
		cin >> numIteration;
		if (u1.invalidInputRetry())
			continue;
		if (!u1.invalidInputRetry())
		{
			numIteration = 0;
			isIn = false;
		}
	}


	vector<Rent> v;
	int choice;
	Date d1, d2;
	for (int i = 0; i < numIteration; i++)
	{
		u1.clearScreen();
		cout << "What is the type of rent? \n1 - Hotel\n2 - Bed'n'Breakfast\n3 - Apartment\n4 - Flat\n5 - Shared House";
		cin >> choice;
		vector<Rent> temp;
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

		if (choice == 1)
		{
			Hotel h;
			temp = s.getVector();
			temp.push_back(h.buildRent());
			s.setVector(temp);
			break;
		}
		if (choice == 2)
		{
			bedNbreakfast bnb;
			temp = s.getVector();
			temp.push_back(bnb.buildRent());
			s.setVector(temp);
			break;
		}
		if (choice == 3)
		{
			flat fl;
			temp = s.getVector();
			temp.push_back(fl.buildRent());
			s.setVector(temp);
			break;
		}
		if (choice == 4)
		{
			apartment ap;
			temp = s.getVector();
			temp.push_back(ap.buildRent());
			s.setVector(temp);
			break;
		}
		if (choice == 5)
		{
			sharedHouse sh;
			temp = s.getVector();
			temp.push_back(sh.buildRent());
			s.setVector(temp);
			break;
		}
	}

	cout << "\n\nThe program will now return to the main menu.\n\n";
	

	return;

}

void Corporation::registerSupplier()
{
	bool isIn = true;
	u1.clearScreen();
	string s, ad, password;
	unsigned int nif;
	while (isIn)
	{
		cout << "What is your username?\nUsername: ";
		cin >> s;
		for (int i = 0; i < suppliersVec.size(); i++)
		{
			if (s == suppliersVec[i].getName())
			{
				cout << "The username is already taken! Do you wish to try again? (y/n)";
				string choice;
				cin >> choice;
				if (choice == "Y" || choice == "y")
					continue;
				if (choice == "n" || choice == "N")
				{
					cout << "\nThe program will now return.\n";
					isIn = false;
					return;
				}
				else
				{
					u1.cinClear();
					i--;
					continue;
				}
			}
		}
		cout << "\nPassword: ";
		cin >> password;
		cout << "\nWhat is your FIN? (Fiscal Identification Number)\nFIN: ";
		cin >> nif;
		if (u1.invalidInputRetry())
			continue;
		if (!u1.invalidInputRetry())
		{
		
			cout << "\nThe program will now return.\n";
			isIn = false;
			return;
		}
		cout << "\nWhat is your address?\nAddress: ";
		cin >> ad;
		vector<Rent> v2;
		Supplier x (s, password, nif, ad, v2);
		suppliersVec.push_back(x);
		cout << "\nSuccess!!! The program will now return.";
		Sleep(1000); 
		isIn = false;
}

/*Checks existance of the reservations file
bool Corporation::foundReservationsFile(string reservationsFile)
{
	fstream f;

	f.open(reservationsFile);

	if (f.fail()) {
		f.close();
		u1.setColor(12); cerr << "\n  ERROR: " << reservationsFile << " (suppliers file) could not be found!\n         Verify the directory!\n\n"; u1.setColor(15);
		return false;
	}

	f.close();

	this->reservationsFile = reservationsFile;
	return true;
}
*/
//Loads the users file to memory (Users vector)

/*void Corporation::loadReservations()
{
	string name,name_rent,type, type_type, d1, d2;
	unsigned int n_people;
	Rent *c;
	fstream f;
	string line;
	f.open("reservations.txt");

	while (!f.eof()) {
		getline(f, line);

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


		reservationsVec.push_back(Reservation(name, type, type_type, n_people,Date(d1),Date(d2),c));
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


/*void Corporation::saveReservations()
{
	ofstream f;

	f.open(reservationsFile, ofstream::app);

	for (size_t i = 0; i < reservationsVec.size(); i++) {
		f << reservationsVec.at(i).getname() << " ; " << reservationsVec.at(i).getrent().getName() << " ; " << reservationsVec.at(i).gettype_rent << " ; " << reservationsVec.at(i).gettype_type_rent() << " ; " << reservationsVec.at(i).getn_people() << " ; " << reservationsVec.at(i).getDate1() << " ; " << reservationsVec.at(i).getDate2();
	}

	f.close();

	return;
}*/
