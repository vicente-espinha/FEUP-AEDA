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
			Corporation::instance()->nif = usersVec.at(i).getNif();
			foundUser = true;
			u1.clearScreen();
			corpMenu.UsersMenu();
			return;
		}
	}

	for (size_t i = 0; i != suppliersVec.size(); i++) {
		if (suppliersVec.at(i).getName() == user && suppliersVec.at(i).getPassword() == password) {
			Corporation::instance()->supplierName = user;
			Corporation::instance()->nif = suppliersVec.at(i).getNif();
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

	string line;
	fstream f;

	vector<Rent> rent;

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
		unsigned int numRents = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);

		if (numRents == 0) {
			suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
		}

		for (int i = 0; numRents != 0; numRents--, i++)
		{
			string typeRent = u1.trim(line.substr(0, line.find(" ; ")));
			line.erase(0, line.find(" ; ") + 3);
			cout << "\nTypeRent : " << typeRent << endl;
			if (typeRent == "Hotel") {
				string nameHotel = line.substr(0, line.find(" ; "));
				line.erase(0, line.find(" ; ") + 3);
				string city = line.substr(0, line.find(" ; "));
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
				unsigned int numPeople = stoi(line.substr(0, line.find(" ;")));
				line.erase(0, line.find(" ;") + 2);



				rent.push_back(Hotel(typeRent, nameHotel, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), roomType, price, numPeople));
				cout << "NumRents : " << numRents << endl;
				cout << "Rent.size: " << rent.size();
				//	cout << "NumRents : " << numRents << endl;
				//	cout << "Rent.size: " << rent.size();
				if (numRents == 1)
				{
					suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
					//		cout << endl << "getVector.size() : " << suppliersVec[i].getVector().size() << endl;

				}
			}
			else if (typeRent == "Bed'n'Breakfast") {
				string nameBB = line.substr(0, line.find(" ; "));
				line.erase(0, line.find(" ; ") + 3);
				string city = line.substr(0, line.find(" ; "));
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
				unsigned int numPeople = stoi(line.substr(0, line.find(" ;")));
				line.erase(0, line.find(" ;") + 2);

				rent.push_back(bedNbreakfast(typeRent, nameBB, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
				//	cout << "NumRents : " << numRents << endl;
				//	cout << "Rent.size: " << rent.size();
				if (numRents == 1)
				{
					suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
					//		cout << endl << "getVector.size() : " << suppliersVec[i].getVector().size() << endl;

				}
			}
			else if (typeRent == "Shared House") {
				string nameSH = line.substr(0, line.find(" ; "));
				line.erase(0, line.find(" ; ") + 3);
				string city = line.substr(0, line.find(" ; "));
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
				unsigned int numPeople = stoi(line.substr(0, line.find(" ;")));
				line.erase(0, line.find(" ;") + 2);

				rent.push_back(sharedHouse(typeRent, nameSH, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
				//	cout << "NumRents : " << numRents << endl;
				//	cout << "Rent.size: " << rent.size();
				if (numRents == 1)
				{
					suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
					//		cout << endl << "getVector.size() : " << suppliersVec[i].getVector().size() << endl;

				}

			}
			else if (typeRent == "Flat") {
				string nameFlat = line.substr(0, line.find(" ; "));
				line.erase(0, line.find(" ; ") + 3);
				string city = line.substr(0, line.find(" ; "));
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
				unsigned int numPeople = stoi(line.substr(0, line.find(" ;")));
				line.erase(0, line.find(" ;") + 2);


				rent.push_back(flat(typeRent, nameFlat, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
				//	cout << "NumRents : " << numRents << endl;
				//	cout << "Rent.size: " << rent.size();
				if (numRents == 1)
				{
					suppliersVec.push_back(Supplier(supplierName, password, nif, address, rent));
					//		cout << endl << "getVector.size() : " << suppliersVec[i].getVector().size() << endl;

				}

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
				int numRooms = stoi(line.substr(0, line.find(" ; ")));
				bool k, s, l;
				string x = line.substr(0, line.find(" ; "));
				line.erase(0, line.find(" ; ") + 3);
				if (x == "true")
					k = true;
				else
					k = false;
				x = line.substr(0, line.find(" ; "));
				line.erase(0, line.find(" ; ") + 3);
				if (x == "true")
					s = true;
				else
					s = false;
				x = line.substr(0, line.find(" ;"));
				line.erase(0, line.find(" ;") + 2);
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

		} rent.erase(rent.begin(), rent.end());
	}
	f.close();
	return;

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

	for (int i = 0; i < suppliersVec.size(); i++)
	{
		f << suppliersVec[i].getName() << " ; " << suppliersVec[i].getPassword() << " ; " << suppliersVec[i].getNif() << " ; " << suppliersVec[i].getAddress() << " ; ";
		f << suppliersVec[i].getVector().size() << " ; ";
		for (int j = 0; j < suppliersVec[i].getVector().size(); j++)
		{

			if (suppliersVec[i].getVector()[j].getTypeRent() == "Hotel")
			{

				f << "Hotel ; " << suppliersVec[i].getVector()[j].getName() << " ; " << suppliersVec[i].getVector()[j].getCity() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getType() << " ; " << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople();
				if (j == (suppliersVec[i].getVector().size() - 1))
					f << " ; \n";
				else
					f << " ; ";

			}

			if (suppliersVec[i].getVector()[j].getTypeRent() == "Bed'n'Breakfast")
			{
				f << "Bed'n'Breakfast ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				f << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople();
				if (j == (suppliersVec[i].getVector().size() - 1))
					f << " ; \n";
				else
					f << " ; ";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Shared House")
			{
				f << "Shared House ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				f << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople();
				if (j == (suppliersVec[i].getVector().size() - 1))
					f << " ; \n";
				else
					f << " ; ";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Flat")
			{
				f << "Flat ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				f << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getDataFim().getDay() << "/" << suppliersVec[i].getVector()[j].getDataFim().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataFim().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople();
				if (j == (suppliersVec[i].getVector().size() - 1))
					f << " ; \n";
				else
					f << " ; ";
			}
			if (suppliersVec[i].getVector()[j].getTypeRent() == "Apartment")
			{
				f << "Apartment ; " << suppliersVec[i].getVector()[j].getName() << " ; " << u1.trim(suppliersVec[i].getVector()[j].getCity()) << " ; ";
				f << suppliersVec[i].getVector()[j].getDataInicio().getDay() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getMonth() << "/" << suppliersVec[i].getVector()[j].getDataInicio().getYear() << " ; ";
				f << suppliersVec[i].getVector()[j].getPrice() << " ; " << suppliersVec[i].getVector()[j].getNumPeople() << " ; ";
				f << suppliersVec[i].getVector()[j].getNumRooms() << " ; ";
				f << suppliersVec[i].getVector()[j].getKitchen() << " ; " << suppliersVec[i].getVector()[j].getSuite() << " ; " << suppliersVec[i].getVector()[j].getLivingRoom();
				if (j == (suppliersVec[i].getVector().size() - 1))
					f << " ; \n";
				else
					f << " ; ";
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
			v.push_back(h.buildRent());
		}
		if (choice == 2) {
			u1.clearScreen();
			bedNbreakfast bnb;
			v.push_back(bnb.buildRent());
		}
		if (choice == 3) {
			u1.clearScreen();
			flat fl;
			v.push_back(fl.buildRent());
			break;
		}
		if (choice == 4) {
			u1.clearScreen();
			apartment ap;
			v.push_back(ap.buildRent());
			break;
		}
		if (choice == 5) {
			u1.clearScreen();
			sharedHouse sh;
			v.push_back(sh.buildRent());
			break;
		}
	}

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


void Corporation::makeReservation() // o unico erro é como dar display das rents e ainda vai haver modificacoes na estrutura da funcao
{
	string city, nameRent, typeRent, type;
	unsigned int n_people, n, counter = 1, option;
	bool isIn = true;
	float xPrice;

#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);

	city = Corporation::instance()->cities();
	u1.clearScreen();

	string dateB, dateE;

	while (isIn) {
		cout << "\nDate of check-in: "; cin >> dateB;

		Date date1 = Date(dateB);

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.UsersMenu();
		}

		if (!date1.isValid() || (real_date > date1)) {
			u1.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid."; u1.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.cinClear();
			u1.clearScreen();
		}
		else {
			u1.cinClear();
			isIn = false;
		}
	}

	isIn = true;
	while (isIn) {
		cout << "\nDate of check-out : "; cin >> dateE; cout << endl;

		Date date2 = Date(dateE);

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.UsersMenu();
		}

		if (!date2.isValid() || (real_date > date2)) {
			u1.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid. Please use the format dd/mm/yyyy"; u1.setColor(15);
			Sleep(2000);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.cinClear();
			u1.clearScreen();
		}
		else {
			u1.cinClear();
			isIn = false;
		}
	}

	Date date1 = Date(dateB);
	Date date2 = Date(dateE);
	Rent * c = nullptr;

	isIn = true;

	while (isIn) {
		u1.setColor(11); cout << "Rooms available between " << date1 << " and " << date2 << " in " << city << ": \n\n"; u1.setColor(15);

		for (size_t i = 0; i < rentsVec.size(); i++, counter++) {
			if ((date1 > rentsVec.at(i).getDataInicio() || date1 == rentsVec.at(i).getDataInicio()) && (date2 < rentsVec.at(i).getDataFim() || date2 == rentsVec.at(i).getDataFim()) && city == rentsVec.at(i).getCity()) {
				if (rentsVec.at(i).getTypeRent() == "Hotel") {
					cout << "Option " << counter << endl;
					cout << "Type of accommodation: " << rentsVec.at(i).getTypeRent() << endl;
					cout << "Name: " << rentsVec.at(i).getName() << endl;
					cout << "Available from: " << rentsVec.at(i).getDataInicio();
					cout << "  To: " << rentsVec.at(i).getDataFim() << endl;
					cout << "Room type: " << rentsVec.at(i).getType() << endl;
					cout << "Price per night: " << rentsVec.at(i).getPrice() << endl;
					cout << "Room's capacity: " << rentsVec.at(i).getNumPeople() << endl << endl;
				} else if(rentsVec.at(i).getTypeRent() == "Apartment"){
					cout << "Option " << counter << endl;
					cout << "Type of accommodation: " << rentsVec.at(i).getTypeRent() << endl;
					cout << "Name: " << rentsVec.at(i).getName() << endl;
					cout << "Available from: " << rentsVec.at(i).getDataInicio();
					cout << "  To: " << rentsVec.at(i).getDataFim() << endl;
					cout << "Has Kitchen: " << rentsVec.at(i).getKitchen() << endl;
					cout << "Has Living Room: " << rentsVec.at(i).getLivingRoom() << endl;
					cout << "Has Suite: " << rentsVec.at(i).getSuite() << endl;
					cout << "Price per night: " << rentsVec.at(i).getPrice() << endl;
					cout << "Room's capacity: " << rentsVec.at(i).getNumPeople() << endl << endl;
				}
				else {
					cout << "Option " << counter << endl;
					cout << "Type of accommodation: " << rentsVec.at(i).getTypeRent() << endl;
					cout << "Name: " << rentsVec.at(i).getName() << endl;
					cout << "Available from: " << rentsVec.at(i).getDataInicio();
					cout << "  To: " << rentsVec.at(i).getDataFim() << endl;
					cout << "Price per night: " << rentsVec.at(i).getPrice() << endl;
					cout << "Room's capacity: " << rentsVec.at(i).getNumPeople() << endl << endl;
				}
			}
		}

		cout << "Insert the option's number: ";
		cin >> option;

		xPrice = rentsVec[option - 1].getPrice();

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.UsersMenu();
		}

		if (cin.fail()) {
			u1.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u1.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.cinClear();
			u1.clearScreen();
		}
	}

	isIn = true;
	
	while (isIn) {
		u1.setColor(14); cout << "\n\nCity: " << city << "  From: " << date1 << "  To: " << date2 << endl;
		cout << "\nNumber of people: ";
		cin >> n_people;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.UsersMenu();
		}

		if (cin.fail()) {
			u1.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u1.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.cinClear();
			u1.clearScreen();
		}

		for (int i = 0; i < rentsVec.size(); i++) {
			if (n_people > rentsVec.at(i).getNumPeople()) {
				u1.setColor(12); cerr << endl << "  ERROR: The value you inserted exceeds the room's maximum capacity."; u1.setColor(15);
				Sleep(1500);
				cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
				Sleep(1500);
				u1.cinClear();
			}
			else {
				cin.clear();
				isIn = false;
			}
		}
	}

	for (size_t i = 0; i < rentsVec.size(); i++) {

	}


		reservationsVec.push_back(Reservation(nif, (xPrice*(date2.minus(date1)), date1, date2));
}


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

	f.open(rentsFile);

	while (getline(f, line)) {

		string typeRent = u1.trim(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		cout << "\nTypeRent Rents : " << typeRent << endl;
		Sleep(3000);
		if (typeRent == "Hotel") {
			string nameHotel = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			string city = line.substr(0, line.find(" ; "));
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
			unsigned int numPeople = stoi(line.substr(0, line.find(" ;")));
			line.erase(0, line.find(" ;") + 2);

			rentsVec.push_back(Hotel(typeRent, nameHotel, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), roomType, price, numPeople));
		}
		else if (typeRent == "Bed'n'Breakfast") {
			string nameBB = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			string city = line.substr(0, line.find(" ; "));
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
			unsigned int numPeople = stoi(line.substr(0, line.find(" ;")));
			line.erase(0, line.find(" ;") + 2);

			rentsVec.push_back(bedNbreakfast(typeRent, nameBB, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
		}
		else if (typeRent == "Shared House") {
			string nameSH = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			string city = line.substr(0, line.find(" ; "));
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
			unsigned int numPeople = stoi(line.substr(0, line.find(" ;")));
			line.erase(0, line.find(" ;") + 2);

			rentsVec.push_back(sharedHouse(typeRent, nameSH, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));
		}
		else if (typeRent == "Flat") {
			string nameFlat = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			string city = line.substr(0, line.find(" ; "));
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
			unsigned int numPeople = stoi(line.substr(0, line.find(" ;")));
			line.erase(0, line.find(" ;") + 2);


			rentsVec.push_back(flat(typeRent, nameFlat, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));

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
			int numRooms = stoi(line.substr(0, line.find(" ; ")));
			bool k, s, l;
			string x = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			if (x == "true")
				k = true;
			else
				k = false;
			x = line.substr(0, line.find(" ; "));
			line.erase(0, line.find(" ; ") + 3);
			if (x == "true")
				s = true;
			else
				s = false;
			x = line.substr(0, line.find(" ;"));
			line.erase(0, line.find(" ;") + 2);
			if (x == "true")
				l = true;
			else
				l = false;
			rentsVec.push_back(apartment(typeRent, nameApartment, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople, numRooms, k, s, l));
		}

	}

	f.close();
	return;

	/*string line;
	fstream f;

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

			rentsVec.push_back(bedNbreakfast(typeRent, nameBB, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));

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

			rentsVec.push_back(sharedHouse(typeRent, nameSH, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));

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

			rentsVec.push_back(flat(typeRent, nameFlat, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople));

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

			rentsVec.push_back(apartment(typeRent, nameApartment, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople, numRooms, k, s, l));

		}
	}
	f.close();
	return;*/
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