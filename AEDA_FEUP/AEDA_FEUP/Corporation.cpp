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

void Corporation::login() {

	string password, user;
	bool foundUser = false;
	bool foundSupplier = false;

	cout << "Username:  "; getline(cin, user);

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.MainMenu();
	}

	cout << "\nPassword:  "; cin >> password;

	u1.cinClear();

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.MainMenu();
	}

	for (size_t i = 0; i != usersVec.size(); i++) {
		if (usersVec.at(i).getUsername() == user && usersVec.at(i).getPassword() == password) {
			Corporation::instance()->username = user;
			foundUser = true;
			u1.clearScreen();
			corpMenu.UsersMenu();
			return;
		}
	}

	for (size_t i = 0; i != suppliersVec.size(); i++) {
		if (suppliersVec.at(i).getName() == user && suppliersVec.at(i).getPassword() == password) {
			Corporation::instance()->supplierName = user;
			foundSupplier = true;
			u1.clearScreen();
			corpMenu.SuppliersMenu();
			return;
		}
	}

	if (!foundUser && !foundSupplier) {
		cout << "\n  ERROR: The username/password you inserted do not exist. Please try again.";
		Sleep(2000);
		return;
	}

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

	ofstream f("temp.txt");

	for (size_t i = 0; i < usersVec.size(); i++) {
		f << usersVec[i].getUsername() << " ; " << usersVec[i].getPassword() << " ; " << usersVec[i].getNif() << " ; " << usersVec[i].getPoints() << endl;
	}

	f.close();

	remove(usersFile.c_str());
	rename("temp.txt", usersFile.c_str());

	return;
}

//Adds a user to the users vector
void Corporation::registerUser() {

	string user, password, nif;

	cout << "\n Name:  "; getline(cin, user);

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}

	for (unsigned int index = 0; index != user.size(); index++) {
		if (!isalpha(user[index]) && user[index] != ' ') {
			u1.setColor(12); cerr << "  ERROR: Name must only contain alphabetic characters. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	for (unsigned int index2 = 0; index2 != usersVec.size(); index2++) {
		if (usersVec.at(index2).getUsername() == user) {
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
		if (!isdigit(nif[index4])) {
			u1.setColor(12); cerr << "  ERROR: NIF can only contain digits. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	for (unsigned int index5 = 0; index5 != usersVec.size(); index5++) {
		if (usersVec.at(index5).getNif() == stoi(nif)) {
			u1.setColor(12); cerr << "  ERROR: The NIF you selected was already found in our system. Probably you already have an account. "; u1.setColor(15);
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

	usersVec.push_back(Users(user, password, stoi(nif), 0));
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

	string line, lineRents;
	fstream f, r;

	vector<Rent> rent;

	f.open(suppliersFile);
	r.open("rents.txt");
	while (getline(f, line)) {

		string supplierName = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string password = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int nif = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		string address = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);

		suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
	}
	while (getline(r, lineRents)) {

		vector<Rent> xVec;
		string name = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
		lineRents.erase(0, lineRents.find(" ; ") + 3);
		orderSuppliersVec();
		int x;
		for (int i = 0; i < suppliersVec.size(); i++)
			if (name == suppliersVec[i].getName())
			{
				x = i;
				xVec = suppliersVec[i].getVector();
			}


		lineRents.erase(0, lineRents.find(" ; ") + 3);
		string typeRent = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
		lineRents.erase(0, lineRents.find(" ; ") + 3);
		if (typeRent == "Hotel") {

			string nameHotel = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string city = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int startDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int endDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string roomType = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			float price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents.substr(0, lineRents.find(" ;")));
			lineRents.erase(0, lineRents.find(" ;") + 2);

			rent.push_back(Hotel(typeRent, nameHotel, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), roomType, price, numPeople));

			suppliersVec[x].setVector(xVec.push_back(rent));
		}
		else if (typeRent == "Bed'n'Breakfast") {
			cout << lineRents << endl;
			string nameBB = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string city = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int startDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int endDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			float price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents.substr(0, lineRents.find(" ;")));
			lineRents.erase(0, lineRents.find(" ;") + 2);

			rent.push_back(bedNbreakfast(typeRent, nameBB, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
			cout << "NumRents : " << numRents << endl;
			cout << "Rent.size: " << rent.size();
			if (numRents == 1)
			{

				cout << "sera que ";
				suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
				//		cout << endl << "getVector.size() : " << suppliersVec[i].getVector().size() << endl;

			}
			cout << lineRents << " merda " << numRents << " " << endl;

			continue;
		}
		else if (typeRent == "Shared House") {
			cout << lineRents << endl;
			string nameSH = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string city = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int startDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int endDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			float price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents.substr(0, lineRents.find(" ;")));
			lineRents.erase(0, lineRents.find(" ;") + 2);

			rent.push_back(sharedHouse(typeRent, nameSH, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
			cout << "NumRents : " << numRents << endl;
			cout << "Rent.size: " << rent.size();
			if (numRents == 1)
			{
				suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
				//		cout << endl << "getVector.size() : " << suppliersVec[i].getVector().size() << endl;

			}
			cout << lineRents << endl;

			continue;
		}
		else if (typeRent == "Flat") {
			cout << lineRents << endl;
			string nameFlat = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string city = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int startDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int endDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			float price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents.substr(0, lineRents.find(" ;")));
			lineRents.erase(0, lineRents.find(" ;") + 2);
			cout << lineRents << endl;

			rent.push_back(flat(typeRent, nameFlat, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
			cout << "NumRents : " << numRents << endl;
			cout << "Rent.size: " << rent.size();
			if (numRents == 1)
			{
				suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
				//		cout << endl << "getVector.size() : " << suppliersVec[i].getVector().size() << endl;

			}
			cout << lineRents << endl;


		}
		else if (typeRent == "Apartment") {
			string nameApartment = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string city = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int startDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int endDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			float price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			int numRooms = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			bool k, s, l;
			string x = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			if (x == "true")
				k = true;
			else
				k = false;
			x = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			if (x == "true")
				s = true;
			else
				s = false;
			x = lineRents.substr(0, lineRents.find(" ;"));
			lineRents.erase(0, lineRents.find(" ;") + 2);
			if (x == "true")
				l = true;
			else
				l = false;
			rent.push_back(apartment(typeRent, nameApartment, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople, numRooms, k, s, l));
			//	cout << "NumRents : " << numRents << endl;
			//	cout << "Rent.size: " << rent.size();
			if (numRents == 1)
			{
				suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
				//		cout << endl << "getVector.size() : " << suppliersVec[i].getVector().size() << endl;

			}



		}
		f.close();
		r.close();
		return;

	}
}

void Corporation::printSuppliers()
{
	cout << endl;
	for (int i = 0; i < suppliersVec.size(); i++)
	{
		cout << suppliersVec[i].getName() << " , " << suppliersVec[i].getPassword() << " , " << suppliersVec[i].getNif() << " , " << suppliersVec[i].getAddress() << " , ";
		for (int j = 0; j < suppliersVec[i].getVector().size(); j++)
		{
			cout << "\ni: " << i << " j : " << j << endl;
			cout << "supVecsize: " << suppliersVec.size() << " getVectorSize: " << suppliersVec[i].getVector().size() << endl;
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Hotel")
			{

				//cout << "Saving Hotel...\n";
				cout << "Hotel ; " << suppliersVec[i].getVector()[j].getName() << " ; " << suppliersVec[i].getVector()[j].getCity() << " ; ";
				cout << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				cout << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				cout << suppliersVec[i].getVector()[j].getType() << " ; " << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << "\n";
				//cout << "Completed!\n";

			}

			if (suppliersVec[i].getVector()[j].getTypeRent() == "Bed'n'Breakfast")
			{
				//cout << "Saving Bed'n'Breakfast...\n";
				cout << "Bed'n'Breakfast ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				cout << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				cout << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				cout << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << "\n";
				//	cout << "Completed!\n";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Shared House")
			{
				//	cout << "Saving Shared House...\n";
				cout << "Shared House ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				cout << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				cout << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				cout << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << "\n";
				//	cout << "Completed!\n";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Flat")
			{
				//cout << "Saving Flat...\n";
				cout << "Flat ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				cout << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				cout << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				cout << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << "\n";
				//cout << "Completed!\n";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Apartment")
			{
				//cout << "Saving Apartment...\n";
				cout << "Apartment ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				cout << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				cout << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << " ; ";
				cout << suppliersVec[i].getVector()[j].getNumRooms() << " ; ";
				cout << suppliersVec[i].getVector()[j].getKitchen() << " ; " << suppliersVec[i].getVector()[j].getSuite() << " ; " << suppliersVec[i].getVector()[j].getLivingRoom() << "\n";
				//cout << "Completed!\n";
			}
		}

	}
}

//Loads suppliersVec to the .txt file
void Corporation::saveSuppliers()
{
	ofstream f("tempSuppliers.txt");
	ofstream r("rents.txt");

	for (int i = 0; i < suppliersVec.size(); i++)
	{
		f << suppliersVec[i].getName() << " ; " << suppliersVec[i].getPassword() << " ; " << suppliersVec[i].getNif() << " ; " << suppliersVec[i].getAddress() << "\n";
		for (int j = 0; j < suppliersVec[i].getVector().size(); j++)
		{

			if (suppliersVec[i].getVector()[j].getTypeRent() == "Hotel")
			{
				r << suppliersVec[i].getName() << " ; ";
				r << "Hotel ; " << suppliersVec[i].getVector()[j].getName() << " ; " << suppliersVec[i].getVector()[j].getCity() << " ; ";
				r << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				r << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				r << suppliersVec[i].getVector()[j].getType() << " ; " << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople();
				r << " ; \n";

			}

			if (suppliersVec[i].getVector()[j].getTypeRent() == "Bed'n'Breakfast")
			{
				r << suppliersVec[i].getName() << " ; ";
				r << "Bed'n'Breakfast ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				r << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				r << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				r << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople();
				r << " ; \n";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Shared House")
			{
				r << suppliersVec[i].getName() << " ; ";
				r << "Shared House ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				r << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				r << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				r << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople();
				r << " ; \n";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Flat")
			{
				r << suppliersVec[i].getName() << " ; ";
				r << "Flat ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				r << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				r << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				r << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople();
				f << " ; \n";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Apartment")
			{
				r << suppliersVec[i].getName() << " ; ";
				r << "Apartment ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				r << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				r << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << " ; ";
				r << suppliersVec[i].getVector()[j].getNumRooms() << " ; ";
				r << suppliersVec[i].getVector()[j].getKitchen() << " ; " << suppliersVec[i].getVector()[j].getSuite() << " ; " << suppliersVec[i].getVector()[j].getLivingRoom();
				r << " ; \n";
			}
		}

	}
	f.close();

	remove(suppliersFile.c_str());
	rename("tempSuppliers.txt", suppliersFile.c_str());

	return;
}

//Adds a supplier to the suppliers vector
void Corporation::registerSupplier() {

	string user, password, nif, address;
	vector<Rent> rent;

	cout << "\n Name:  "; getline(cin, user);

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}

	for (unsigned int index = 0; index != user.size(); index++) {
		if (!isalpha(user.at(index)) && user.at(index) != ' ') {
			u1.setColor(12); cerr << "  ERROR: Name must only contain alphabetic characters. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	for (unsigned int index2 = 0; index2 != suppliersVec.size(); index2++) {
		if (suppliersVec.at(index2).getName() == user) {
			u1.setColor(12); cerr << "  ERROR: The username you selected already exists. Please choose another one. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	cout << "\n Password:  "; cin >> password;

	u1.cinClear();

	for (unsigned int index3 = 0; index3 != password.size(); index3++) {
		if (!isalnum(password.at(index3))) {
			u1.setColor(12); cerr << "  ERROR: Password cannot contain special characters. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	cout << "\n NIF:  "; cin >> nif;
	u1.cinClear();

	for (unsigned int index4 = 0; index4 != nif.size(); index4++) {
		if (!isdigit(nif.at(index4))) {
			u1.setColor(12); cerr << "  ERROR: NIF can only contain digits. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	for (unsigned int index5 = 0; index5 != suppliersVec.size(); index5++) {
		if (suppliersVec.at(index5).getNif() == stoi(nif)) {
			u1.setColor(12); cerr << "  ERROR: The NIF you selected was already found in our system. Probably you already have an account. "; u1.setColor(15);
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

	cout << "\n Address:  "; cin >> address;

	u1.cinClear();

	for (unsigned int i = 0; i != suppliersVec.size(); i++) {
		if (suppliersVec.at(i).getAddress() == address) {
			u1.setColor(12); cerr << "  ERROR: The address you selected was already found in our system. Probably you already have an account. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}

	suppliersVec.push_back(Supplier(user, password, stoi(nif), address, rent));
	u1.clearScreen();
	return;
}

void Corporation::orderSuppliersVec()
{
	int i, j;
	for (i = 0; i < (suppliersVec.size() - 1); i++) {
		for (j = 0; j < suppliersVec.size() - 1; j++)
		{
			if (suppliersVec[j].getName() > suppliersVec[j + 1].getName())
			{
				string before, after;
				after = suppliersVec[j].getName();
				before = suppliersVec[j + 1].getName();
				suppliersVec[j + 1].setName(after);
				suppliersVec[j].setName(before);
			}
		}
	}

}

void Corporation::makeRent() {

	bool isIn = true;
	vector<Rent> v;
	Date d1, d2;
	string cinNumIter, cinChoice;
	int numIteration, choice;

	while (isIn) {

		u1.setColor(14); cout << "\n  ::| CREATE RENT |::\n"; u1.setColor(15);

		cout << "\nHow many rents do you wish to be made available? :  ";
		cin >> cinNumIter;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.SuppliersMenu();
		}

		for (size_t i = 0; i < cinNumIter.size(); i++) {
			if (!isdigit(cinNumIter.at(i))) {
				u1.setColor(12); cerr << endl << "  ERROR: Input can only contain digits. "; u1.setColor(15);
				Sleep(1500);
				cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
				Sleep(1500);
				u1.cinClear();
				u1.clearScreen();
			}
			else {

				numIteration = stoi(cinNumIter);
				cin.clear();
				isIn = false;
			}
		}
	}

	isIn = true;
	vector<Rent> x;
	int xnum;
	for (int j = 0; j < suppliersVec.size(); j++)
		if (suppliersVec[j].getName() == Corporation::instance()->username) {
			x = suppliersVec[j].getVector();
			xnum = j;
		}

	for (int i = 0; i < numIteration; i++) {


		u1.clearScreen();
		cout << "What is the type of rent? \n1 - Hotel\n2 - Bed'n'Breakfast\n3 - Apartment\n4 - Flat\n5 - Shared House\n\n";
		cout << "Select the number corresponding to the option you wish to select: ";
		cin >> cinChoice;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.SuppliersMenu();
		}

		if (stoi(cinChoice) < 1 || stoi(cinChoice) > 5) {
			u1.setColor(12); cerr << endl << "  ERROR: Input can only range from 1 to 5. "; u1.setColor(15);
			Sleep(1500);
			u1.cinClear();
			corpMenu.SuppliersMenu();
		}

		for (size_t i = 0; i < cinChoice.size(); i++) {
			if (!isdigit(cinChoice.at(i))) {
				u1.setColor(12); cerr << endl << "  ERROR: Input can only contain digits. "; u1.setColor(15);
				Sleep(1500);
				u1.cinClear();
				corpMenu.SuppliersMenu();
			}
		}

		choice = stoi(cinChoice);

		if (choice == 1) {
			u1.clearScreen();
			Hotel h;
			x.push_back(h.buildRent());
		}
		if (choice == 2) {
			u1.clearScreen();
			bedNbreakfast bnb;
			x.push_back(bnb.buildRent());
		}
		if (choice == 3) {
			u1.clearScreen();
			flat fl;
			x.push_back(fl.buildRent());
			break;
		}
		if (choice == 4) {
			u1.clearScreen();
			apartment ap;
			x.push_back(ap.buildRent());
			break;
		}
		if (choice == 5) {
			u1.clearScreen();
			sharedHouse sh;
			x.push_back(sh.buildRent());
			break;
		}
	}
	suppliersVec[xnum].setVector(x);
	u1.successMessage();

	return;

}

//Checks existance of the reservations file
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

//Loads the users file to memory (Reservations vector)
void Corporation::loadReservations()
{
	Rent *c = nullptr;
	fstream f;
	string line;
	f.open("reservations.txt");

	while (!f.eof()) {
		getline(f, line);

		string  name = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string  city = line.substr(0, line.find(" ; "));
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
			if (rentsVec.at(i).getCity() == city && rentsVec.at(i).getName() == name_rent) {
				c = &rentsVec.at(i);
			}
		}

		reservationsVec.push_back(Reservation(name, city, type, type_type, n_people, Date(d1), Date(d2), c));
	}
	free(c);
	f.close();
}


/*void Corporation::makeReservation() // o unico erro é como dar display das rents e ainda vai haver modificacoes na estrutura da funcao
{
	string city;
	cout << "City : ";
	getline(cin, city);

	cout << "List of possibilities : " << endl;
	for (int i = 0; i < rentsVec.size(); i++)
	{
		if (city == rentsVec.at(i).getCity())
			cout << " -> " << rentsVec.at(i) << endl; // maneira de display?
	}
	string d1, d2, name_rent;

	cout << " Name of the Rent Place : ";
	getline(cin, name_rent);

	for (int i = 0; i << rentsVec.size();i++)
	{
		if (name_rent == rentsVec.at(i).getName()) {

			unsigned int n_people;
			cout << "Number of persons : ";
			cin >> n_people;

			if (n_people > rentsVec.at(i).getNumPeople())
			{
				cout << "Invalid number of persons." << endl;
				break;
			}

				cout << " Date of check-in : ";
				getline(cin, d1);
				cout << "Date of check-out : ";
				getline(cin, d2);

				Date date1 = Date(d1);
				Date date2 = Date(d2);
				Rent * c = nullptr;

				if ((date1 > rentsVec.at(i).getDataInicio() || date1 == rentsVec.at(i).getDataInicio()) && (date2 < rentsVec.at(i).getDataFim()) || date2 == rentsVec.at(i).getDataFim())
				{
					string answer;
					cout << rentsVec.at(i) << endl << "Do you want to confirm? ";
					if (answer == "yes" || answer == "Yes")
					{
						c = &rentsVec.at(i);
						reservationsVec.push_back(Reservation(username, city, rentsVec.at(i).getType(), rentsVec.at(i).getTypeRent(), n_people, date1, date2,c));
						free(c);
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


void Corporation::saveReservations()
{
	ofstream f;

	f.open(reservationsFile, ofstream::app);

	for (size_t i = 0; i < reservationsVec.size(); i++) {
		f << reservationsVec.at(i).getusername() << " ; " << reservationsVec.at(i).getcity() << " ; " << reservationsVec.at(i).getrent().getName() << "; " << reservationsVec.at(i).gettype_rent() << "; " << reservationsVec.at(i).gettype_type_rent() << "; " << reservationsVec.at(i).getn_people() << "; " << reservationsVec.at(i).getDate1() << "; " << reservationsVec.at(i).getDate2() << endl;
	}

	f.close();

	return;
}


void Corporation::cancelReservation()
{
#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);

	vector<Reservation>temp;
	unsigned int j = 0;
	cout << "List of your reservations : " << endl;
	for (int i = 0; i < reservationsVec.size(); i++)
	{
		if (username == reservationsVec.at(i).getusername()) {
			cout << i + 1 << " -> " << reservationsVec.at(i) << endl; // maneira display?
			j++;
			temp.push_back(reservationsVec.at(i));
		}
	}

	unsigned int n;
	cout << " Which one would you like to cancel :";
	cin >> n;
	if (n > j || n < 0) {
		cout << "Invalid Input" << endl;
		Sleep(3000);
		return;
	}

	string answer;
	cout << "Do you want to confirm ? (yes|No)";
	getline(cin, answer);
	if (answer == "Yes" || answer == "yes")
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if ((i + 1) == n) {
				Date x = temp.at(i).getDate1() - real_date;
				if (x.getYear() != 0 || x.getMonth() > 0)
					cout << " You will receive " << temp.at(i).getprice() << " euros." << endl;
				else if (x.getDay() >= 15)
					cout << "You will receive " << temp.at(i).getprice() / 2 << " euros." << endl;
				else
					cout << "You will not receive any money." << endl;
			}
		}

		for (int i = 0; i < reservationsVec.size(); i++)
		{
			if (reservationsVec.at(i) == temp.at(n - 1)) {
				reservationsVec.erase(reservationsVec.begin() + i);
				cout << "Operation concluded!" << endl;
				Sleep(2000);
				return;
			}
		}
	}
	else
	{
		cout << "You canceled the operation." << endl;
		Sleep(2000);
		return;
	}

}


bool Corporation::foundRentsFile(string rentsFile)
{
	fstream f;

	f.open(rentsFile);

	if (f.fail()) {
		f.close();
		u1.setColor(12); cerr << "\n  ERROR: " << rentsFile << " (suppliers file) could not be found!\n         Verify the directory!\n\n"; u1.setColor(15);
		return false;
	}

	f.close();

	this->rentsFile = rentsFile;
	return true;
}

void Corporation::loadRents()
{
	string line;
	fstream f;


}

string Corporation::cities() {

	string *item = new string[18];
	int counter = 1, option;
	string cinOption;
	bool run = true;

	item[0] = "Aveiro";
	item[1] = "Beja";
	item[2] = "Braga";
	item[3] = "Bragança";
	item[4] = "Castelo Branco";
	item[5] = "Coimbra";
	item[6] = "Evora";
	item[7] = "Faro";
	item[8] = "Guarda";
	item[9] = "Leiria";
	item[10] = "Lisboa";
	item[11] = "Portalegre";
	item[12] = "Porto";
	item[13] = "Santarem";
	item[14] = "Setubal";
	item[15] = "Viana do Castelo";
	item[16] = "Vila Real";
	item[17] = "Viseu";

	u1.setColor(11); cout << "Cities available: \n\n"; u1.setColor(15);
	for (size_t i = 0; i < 18; i++) {
		cout << counter << " - " << item[i] << endl;
		counter++;
	}

	u1.setColor(14); cout << "\nInsert the number corresponding to the city\nin which you wish to make your rent available:  "; u1.setColor(15);
	cin >> cinOption;

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.SuppliersMenu();
	}

	if (stoi(cinOption) < 1 || stoi(cinOption) > 18) {
		u1.setColor(12); cerr << endl << "  ERROR: Input can only range from 1 to 18. "; u1.setColor(15);
		Sleep(1500);
		cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
		Sleep(1500);
		u1.cinClear();
	}

	for (size_t i = 0; i < cinOption.size(); i++) {
		if (!isdigit(cinOption.at(i))) {
			u1.setColor(12); cerr << endl << "  ERROR: Input can only contain digits. "; u1.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.cinClear();
		}
	}

	option = stoi(cinOption);

	switch (option) {

	case 1:
		u1.clearScreen();
		cout << item[0];
		Sleep(2000);
		return item[0];
	case 2:
		return item[1];
	case 3:
		return item[2];
	case 4:
		return item[3];
	case 5:
		return item[4];
	case 6:
		return item[5];
	case 7:
		return item[6];
	case 8:
		return item[7];
	case 9:
		return item[8];
	case 10:
		return item[9];
	case 11:
		return item[10];
	case 12:
		return item[11];
	case 13:
		return item[12];
	case 14:
		return item[13];
	case 15:
		return item[14];
	case 16:
		return item[15];
	case 17:
		return item[16];
	case 18:
		return item[17];
	}
}


/*
	vector<Rent> rent;

	f.open(suppliersFile);

	while (getline(f, line)) {

		string typeRent = u1.trim(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);

		if (typeRent == "Hotel") {
			string nameHotel = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			string city = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startDay = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int startMonth = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int startYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endDay = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int endMonth = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int endYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			string roomType = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			float price = stof(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int numPeople = stoi(line.substr(0, line.length()));

			rentsVec.push_back(Hotel(typeRent, nameHotel, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), roomType, price, numPeople));

		}
		else if (typeRent == "Bed'n'Breakfast") {
			string nameBB = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			string city = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startDay = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int startMonth = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int startYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endDay = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int endMonth = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int endYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			float price = stof(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int numPeople = stoi(line.substr(0, line.length()));

			rent.push_back(bedNbreakfast(typeRent, nameBB, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));

		}
		else if (typeRent == "Shared House") {
			string nameSH = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			string city = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startDay = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int startMonth = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int startYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endDay = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int endMonth = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int endYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			float price = stof(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int numPeople = stoi(line.substr(0, line.length()));

			rent.push_back(sharedHouse(typeRent, nameSH, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));

		}
		else if (typeRent == "Flat") {
			string nameFlat = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			string city = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startDay = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int startMonth = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int startYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endDay = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int endMonth = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int endYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			float price = stof(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int numPeople = stoi(line.substr(0, line.length()));

			rent.push_back(flat(typeRent, nameFlat, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));

		}
		else if (typeRent == "Apartment") {
			string nameApartment = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			string city = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int startDay = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int startMonth = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int startYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int endDay = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int endMonth = stoi(line.substr(0, line.find("/")));
			line.erase(0, line.find("/") + 1);
			unsigned int endYear = stoi(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			float price = stof(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			unsigned int numPeople = stoi(line.substr(0, line.find(" ; ")));
			int numRooms = stof(line.substr(0, line.find(" ; ")));
			bool k, s, l;
			string x = line.substr(0, line.find(" ; "));
			if (x == "true")
				k = true;
			else
				k = false;
			x = line.substr(0, line.find(" ; "));
			if (x == "true")
				s = true;
			else
				s = false;
			x = line.substr(0, line.find(" ; "));
			if (x == "true")
				l = true;
			else
				l = false;

			rent.push_back(apartment(typeRent, nameApartment, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople, numRooms, k, s, l));

		}
	}
	f.close();
	return;
}*/

