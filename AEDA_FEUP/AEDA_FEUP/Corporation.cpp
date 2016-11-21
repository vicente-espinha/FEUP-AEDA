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

	cout << "Username:  ";
	getline(cin, user);

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.MainMenu();
	}

	cout << "\nPassword:  "; cin >> password;
	
	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}

	u1.cinClear();


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
		cout << "\n  ERROR: The username/password you inserted does not exist.";
		Sleep(1000);
		u1.cinClear();
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

	if (user == "")
	{
		u1.setColor(12); cerr << "  ERROR: Must register from Main Menu, please log out first. "; u1.setColor(15); Sleep(1500);
		return;
	}

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
			u1.cinClear();
			corpMenu.RegisterMenu();
		}
	}

	for (unsigned int index2 = 0; index2 != usersVec.size(); index2++) {
		if (usersVec.at(index2).getUsername() == user) {
			u1.setColor(12); cerr << "  ERROR: The username you selected already exists. Please choose another one. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			u1.cinClear();
			corpMenu.RegisterMenu();
		}
	}

	cout << "\n Password:  "; cin >> password;
	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}
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
	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}
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



	usersVec.push_back(Users(user, password, stoi(nif), 0));
	u1.clearScreen();
	return;
}

void Corporation::printSuppliersRents()
{
	int counter = 1;
	for (int i = 0; i < rentsVec.size(); i++)
		for (int j = 0; j < suppliersVec.size(); j++)
			if (Corporation::instance()->supplierName == suppliersVec[j].getName()) {
				Rent x = rentsVec[i];
				cout << counter << "- ";
				cout << "The rent is in " << x.getCity() << ", starts on " << x.getDataInicio() << ", ends on " << x.getDataFim() << ".\n";
				if (x.getTypeRent() == "Hotel")
				{
					cout << "It is a hotel, more specifically a " << x.getType() << ", named " << x.getName() << ", with " << x.getNumPeople() << "ocupants. \nIt's price per night is " << x.getPrice() << ".\n";
					counter++;
				}
				if (x.getTypeRent() == "Apartment")
				{
					cout << "It is an apartment, under the name of " << x.getName() << "housing " << x.getNumPeople() << "ocupants, from " << x.getDataInicio() << " to " << x.getDataFim() << ".\n";
					if (x.getKitchen())
						cout << "It has a kitchen, ";
					else
						cout << "It has no kitchen, ";
					if (x.getSuite())
						cout << "has a suite, ";
					else
						cout << "doesn't have a suite, ";
					if (x.getLivingRoom())
						cout << " and has a living room.";
					else
						cout << " and it doesn't have a living room.";
					cout << "The total price per night is " << x.getPrice() << ".\n";
					counter++;
				}
				if (x.getTypeRent() == "Flat")
				{
					cout << "It is a flat, under the name of " << x.getName() << "housing " << x.getNumPeople() << "ocupants, from " << x.getDataInicio() << " to " << x.getDataFim() << ".\n";
					if (x.getKitchen())
						cout << "It has a kitchen, ";
					else
						cout << "It has no kitchen, ";

					cout << "and the total price per night is " << x.getPrice() << ".\n";
					counter++;
				}
				if (x.getTypeRent() == "Shared House")
				{
					cout << "It is a shared house, under the name of " << x.getName() << "housing " << x.getNumPeople() << "ocupants, from " << x.getDataInicio() << " to " << x.getDataFim() << ".\n";

					cout << "The the total price per night is " << x.getPrice() << ".\n";
					counter++;
				}
				else
				{
					cout << "It is a Bed'n'Breakfast, named of " << x.getName() << "housing " << x.getNumPeople() << "ocupants, from " << x.getDataInicio() << " to " << x.getDataFim() << ".\n";

					cout << "The the total price per night is " << x.getPrice() << ".\n";
					counter++;
				}

			}
	if (counter == 1) {
		cout << "You currently have no rents... You can add a rent in the Menu.\n";
	}
	u1.pressToContinueMessage();

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

void Corporation::loadRents()
{
	Rent tmp;
	fstream r;
	float price;
	r.open("rents.txt");
	string lineRents;
	while (getline(r, lineRents)) {
		int nif = stoi(u1.trim(lineRents.substr(0, lineRents.find(" ; "))));
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
			price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents);
			lineRents.erase(0, lineRents.length());
			tmp = Hotel(nif, typeRent, nameHotel, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), roomType, price, numPeople);

		}
		else if (typeRent == "Bed'n'Breakfast") {
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
			price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents);
			lineRents.erase(0, lineRents.length());

			tmp = bedNbreakfast(nif, typeRent, nameBB, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople);

		}
		else if (typeRent == "Shared House") {
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
			price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents);
			lineRents.erase(0, lineRents.length());
			tmp = sharedHouse(nif, typeRent, nameSH, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople);

		}
		else if (typeRent == "Flat") {
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
			price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents);
			lineRents.erase(0, lineRents.length());
			tmp = flat(nif, typeRent, nameFlat, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople);
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
			price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			int numRooms = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			bool k, s, l;
			string x = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			if (x == "true")
				k = true;
			else
				k = false;
			x = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			if (x == "true")
				s = true;
			else
				s = false;
			x = u1.trim(lineRents);
			lineRents.erase(0, lineRents.length());
			if (x == "true")
				l = true;
			else
				l = false;

			tmp = apartment(nif, typeRent, nameApartment, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople, numRooms, k, s, l);
		}
		string reservationsLine;
		getline(r, reservationsLine);
		int numIterations = stoi(u1.trim(reservationsLine.substr(0, reservationsLine.find(" ; "))));
		reservationsLine.erase(0, reservationsLine.find(" ; ") + 3);
		for (int j = 0; j < numIterations; j++) {

			float nifR = stoi(u1.trim(reservationsLine.substr(0, reservationsLine.find(" ; "))));
			reservationsLine.erase(0, reservationsLine.find(" ; ") + 3);

			Date d1, d2;
			d1 = reservationsLine.substr(0, reservationsLine.find(" ; "));
			reservationsLine.erase(0, reservationsLine.find(" ; ") + 3);

			d2 = reservationsLine.substr(0, reservationsLine.find(" ; "));

			if (j == (numIterations - 1))
				reservationsLine.erase(0, reservationsLine.length());
			else
				reservationsLine.erase(0, reservationsLine.find(" ; ") + 3);
			price = (d2.minus(d1))*price;
			Reservation newR(nifR, price, d1, d2);
			tmp.setReservation(newR);
		}
		rentsVec.push_back(tmp);
	}
}

void Corporation::loadSuppliers() {

	string line, lineRents;
	fstream f;
	vector<Rent> xVec;

	double price;
	f.open(suppliersFile);

	while (getline(f, line)) {

		string supplierName = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string password = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int nif = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		string address = line;
		line.erase(0, line.length());

		suppliersVec.push_back(Supplier(supplierName, password, nif, address));
	}

	f.close();

	return;
}

//Loads suppliersVec to the .txt file
void Corporation::saveSuppliers()
{
	ofstream f("tempSuppliers.txt");

	for (int i = 0; i < suppliersVec.size(); i++)
	{
		int j;
		f << suppliersVec[i].getName() << " ; " << suppliersVec[i].getPassword() << " ; " << suppliersVec[i].getNif() << " ; " << suppliersVec[i].getAddress() << "\n";
	}


	f.close();
	remove(suppliersFile.c_str());
	rename("tempSuppliers.txt", suppliersFile.c_str());

	return;
}

void Corporation::saveRents()
{
	int j;
	ofstream r("rents.txt");
	for (j = 0; j < rentsVec.size(); j++)
	{
		vector<Rent> x;
		x = rentsVec;
		if (x[j].getTypeRent() == "Hotel")
		{
			r << rentsVec[j].getNif() << " ; ";
			r << "Hotel ; " << x[j].getName() << " ; " << x[j].getCity() << " ; ";
			r << x[j].getDataInicio() << " ; ";
			r << x[j].getDataFim() << " ; ";
			r << x[j].getType() << " ; " << x[j].getPrice() << " ; " << x[j].getNumPeople();
			r << "\n";
		}

		if (x[j].getTypeRent() == "Bed'n'Breakfast")
		{
			r << rentsVec[j].getNif() << " ; ";
			r << "Bed'n'Breakfast ; " << x[j].getName() << " ; " << u1.trim(x[j].getCity()) << " ; ";
			r << x[j].getDataInicio() << " ; ";
			r << x[j].getDataFim() << " ; ";
			r << x[j].getPrice() << " ; " << x[j].getNumPeople();
			r << "\n";
		}
		if (x[j].getTypeRent() == "Shared House")
		{
			r << rentsVec[j].getNif() << " ; ";
			r << "Shared House ; " << x[j].getName() << " ; " << u1.trim(x[j].getCity()) << " ; ";
			r << x[j].getDataInicio() << " ; ";
			r << x[j].getDataFim() << " ; ";
			r << x[j].getPrice() << " ; " << x[j].getNumPeople();
			r << "\n";
		}
		if (x[j].getTypeRent() == "Flat")
		{
			r << rentsVec[j].getNif() << " ; ";
			r << "Flat ; " << x[j].getName() << " ; " << u1.trim(x[j].getCity()) << " ; ";
			r << x[j].getDataInicio() << " ; ";
			r << x[j].getDataFim() << " ; ";
			r << x[j].getPrice() << " ; " << x[j].getNumPeople();
			r << "\n";
		}
		if (x[j].getTypeRent() == "Apartment")
		{
			r << rentsVec[j].getNif() << " ; ";
			r << "Apartment ; " << x[j].getName() << " ; " << u1.trim(x[j].getCity()) << " ; ";
			r << x[j].getDataInicio() << " ; ";
			r << x[j].getDataFim() << " ; ";
			r << x[j].getPrice() << " ; " << x[j].getNumPeople() << " ; ";
			r << x[j].getNumRooms() << " ; ";
			r << x[j].getKitchen() << " ; " << x[j].getSuite() << " ; " << x[j].getLivingRoom();
			r << "\n";
		}
		if (x[j].getReservations().size() == 0)
			r << x[j].getReservations().size() << " ;\n";
		else {
			r << x.at(j).getReservations().size() << " ; ";
			for (int k = 0; k < x.at(j).getReservations().size(); k++)
			{
				if (k == (x[j].getReservations().size() - 1))
					r << x[j].getReservations()[k].getnif() << " ; " << x[j].getReservations()[k].getDate1() << " ; " << x[j].getReservations()[k].getDate2();
				else
					r << x[j].getReservations()[k].getnif() << " ; " << x[j].getReservations()[k].getDate1() << " ; " << x[j].getReservations()[k].getDate2() << " ; ";
			}
			r << endl;
		}

	}
	r.close();
	return;
}

void Corporation::deleteRents()
{
	bool isIn = true;
	int i;
	int nif;
	vector <int> v;
	for (int k = 0; k < suppliersVec.size(); k++)
		if (suppliersVec[k].getName() == Corporation::instance()->supplierName) {
			nif = suppliersVec[k].getNif();
		}
	while (isIn) {
		//u1.clearScreen();
		u1.setColor(14); cout << "\n  ::| DELETE RENT |::\n"; u1.setColor(15);
		cout << "\n\nHere are all your available rents. Type the number of the rent you wish to delete.\n\n";
		int counter = 1, tmp = 0;
		for (i = 0; i < rentsVec.size(); i++) {
			if (nif == rentsVec[i].getNif())
			{
				Rent x = rentsVec[i];
				cout << counter << "- ";
				cout << "City: " << x.getCity() << endl << "Beginning date: " << x.getDataInicio() << "\nEnd date: " << x.getDataFim() << endl;
				if (x.getTypeRent() == "Hotel")
				{
					cout << "Hotel - " << x.getName() << endl << "Type: " << x.getType() << "\nNumber of ocupants: " << x.getNumPeople() << "\nPrice: " << x.getPrice() << endl << endl;
					counter++;
					v.push_back(i);
				}
				if (x.getTypeRent() == "Apartment")
				{
					cout << "Apartment - " << x.getName() << "Beginning date: " << x.getDataInicio() << "\nEnd date: " << x.getDataFim() << "\nNumber of people: " << x.getNumPeople() << endl;
					if (x.getKitchen())
						cout << "With kitchen, ";
					else
						cout << "No kitchen, ";
					if (x.getSuite())
						cout << "with suite, ";
					else
						cout << "no suite, ";
					if (x.getLivingRoom())
						cout << "and with living room\n";
					else
						cout << " and without living room\n";
					cout << "Price: " << x.getPrice() << endl << endl;
					counter++;
					v.push_back(i);
				}
				if (x.getTypeRent() == "Flat")
				{
					cout << "Flat -" << x.getName() << "\nBeginning date: " << x.getDataInicio() << "\nEnd date:" << x.getDataFim() << "\nNumber of people: " << x.getNumPeople() << endl;
					if (x.getKitchen())
						cout << "With kitchen.\n";
					else
						cout << "Without kitchen.\n";

					cout << "Price " << x.getPrice() << endl << endl;
					counter++;
					v.push_back(i);
				}
				if (x.getTypeRent() == "Shared House")
				{
					cout << "Shared House - " << x.getName() << "\nBeginning date: " << x.getDataInicio() << "\nEnd date:" << x.getDataFim() << "\nNumber of people: " << x.getNumPeople() << endl;

					cout << "\nPrice :" << x.getPrice() << ".\n" << endl;
					counter++;
					v.push_back(i);
				}
				if (x.getTypeRent() == "Bed'n'Breakfast")
				{
					cout << "Bed'n'Breakfast - " << x.getName() << "\nBeginning date: " << x.getDataInicio() << "\nEnd date:" << x.getDataFim() << "\nNumber of people: " << x.getNumPeople() << endl;

					cout << "Price : " << x.getPrice() << endl << endl;
					counter++;
					v.push_back(i);
				}


			}
		}
		if (counter == 1) {
			cout << "You currently have no rents... You can add a rent in the Menu.\n";
			break;
		}
		isIn = false;
	}
	isIn = true;
	while (isIn) {

		int choice;
		cout << "Option: ";
		cin >> choice;
		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.RegisterMenu();
		}
		if (cin.fail()) {
			cout << "\nInvalid input. Retrying last step.\n";
			continue;
		}
		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.SuppliersMenu();
		}

		if (choice < 1 || choice > i) {
			u1.setColor(12); cerr << endl << "  ERROR: Input can only range positive numbers.\n"; u1.setColor(15);
			Sleep(1500);
			u1.cinClear();
			corpMenu.SuppliersMenu();
		}


		if (rentsVec[v[choice-1]].getReservations().size() > 0) {
			u1.setColor(12); cout << "WARNING : There are already reservations in that rent! Do you wish to continue? (y/n)\n"; u1.setColor(15);
			string option;
			cin >> option;
			if (option == "yes" || option == "y") {
				rentsVec.erase(rentsVec.begin() + (v[choice-1]));
				cout << "\n  Operation completed successfully.\n";
				Sleep(1000);
			}
			else {
				cout << "\n  Returning to Main Menu.\n";
				Sleep(1000);
			}
			isIn = false;
			break;

		}
		else
		{
			rentsVec.erase(rentsVec.begin() + (v[choice - 1]));
			cout << "\n  Operation completed successfully.\n";
			Sleep(1000);
		}

		isIn = false;
	}
	u1.clearScreen();

}

//Adds a supplier to the suppliers vector
void Corporation::registerSupplier() {

	string user, password, nif, address;
	if (user == "")
	{
		u1.setColor(12); cerr << "  ERROR: Must register from Main Menu, please log out first. "; u1.setColor(15); Sleep(1500);
		return;
	}

	cout << "\n Name:  ";
	getline(cin, user);

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}

	for (unsigned int index = 0; index != user.size(); index++) {
		if (!isalpha(user.at(index)) && user.at(index) != ' ') {
			u1.setColor(12); cerr << "  ERROR: Name must only contain alphabetic characters. "; u1.setColor(15);
			Sleep(1500);
			cerr << "  ERROR: Name must only contain alphabetic characters. ";
			u1.clearScreen();
			u1.cinClear();
			corpMenu.RegisterMenu();
		}
	}


	for (unsigned int index2 = 0; index2 != suppliersVec.size(); index2++) {
		if (suppliersVec.at(index2).getName() == user) {
			u1.setColor(12); cerr << "  ERROR: The username you selected already exists. Please choose another one. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			u1.cinClear();
			corpMenu.RegisterMenu();
		}
	}
	

	cout << "\n Password:  "; cin >> password;
	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}
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
	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}
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

	cout << "\n Address:  "; cin >> address;

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.RegisterMenu();
	}

	u1.cinClear();

	for (unsigned int i = 0; i != suppliersVec.size(); i++) {
		if (suppliersVec.at(i).getAddress() == address) {
			u1.setColor(12); cerr << "  ERROR: The address you selected was already found in our system. Probably you already have an account. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			corpMenu.RegisterMenu();
		}
	}



	suppliersVec.push_back(Supplier(user, password, stoi(nif), address));
	u1.clearScreen();
	return;
}

//Orders Suppliers
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

void Corporation::orderRentsVec()
{
	int i;
	if (rentsVec.size() == 1)
		return;
	for (i = 0; i < (rentsVec.size() - 1); i++) {
		if (rentsVec[i].getPrice() > rentsVec[i + 1].getPrice())
		{
			Rent before, after;
			after = rentsVec[i];
			before = rentsVec[i + 1];
			rentsVec[i + 1] = after;
			rentsVec[i] = before;
		}
	}

}

//Adds rent to logged-in supplier
void Corporation::makeRent() {

	bool isIn = true;
	Date d1, d2;
	string cinNumIter, cinChoice;
	int numIteration, choice;

	while (isIn) {

		u1.setColor(14); cout << "\n  ::| CREATE RENT |::\n"; u1.setColor(15);

		cout << "\nHow many rents do you wish to be made available:  ";
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

	long nif;
	isIn = true;

	for (int i = 0; i < suppliersVec.size(); i++)
		if (suppliersVec[i].getName() == Corporation::instance()->supplierName) {
			nif = suppliersVec[i].getNif();
		}


	for (int i = 0; i < numIteration; i++) {


		//u1.clearScreen();
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
			rentsVec.push_back(h.buildRent(nif));
			continue;
		}
		if (choice == 2) {
			u1.clearScreen();
			bedNbreakfast bnb;
			rentsVec.push_back(bnb.buildRent(nif));
			continue;
		}
		if (choice == 3) {
			u1.clearScreen();
			flat fl;
			rentsVec.push_back(fl.buildRent(nif));
			continue;
		}
		if (choice == 4) {
			u1.clearScreen();
			apartment ap;
			rentsVec.push_back(ap.buildRent(nif));
			continue;
		}
		if (choice == 5) {
			u1.clearScreen();
			sharedHouse sh;
			rentsVec.push_back(sh.buildRent(nif));
			continue;
		}
	}
	u1.successMessage();

	return;

}

void Corporation::makeReservation() // o unico erro é como dar display das rents e ainda vai haver modificacoes na estrutura da funcao
{

	string city, nameRent, typeRent, type;
	unsigned int n_people, n, counter = 1, option;
	bool isIn = true;
	int temp = 0;
	float xPrice;

#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);
	vector<int> v;
	city = Corporation::instance()->cities();
	u1.clearScreen();

	
	string dateB, dateE;

	while (isIn) {
		cout << "Date of check-in: "; cin >> dateB;

		Date date1 = Date(dateB);

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.UsersMenu();
		}

		if (!date1.isValid() || (real_date > date1)) {
			u1.setColor(12); cerr << endl << " ERROR: The date you inserted is not valid."; u1.setColor(15); Sleep(500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.cinClear();
			u1.clearScreen();
			continue;
		}
		else {
			u1.cinClear();
			isIn = false;
		}

		cout << "\nDate of check-out : "; cin >> dateE; cout << endl;

		Date date2 = Date(dateE);

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.UsersMenu();
		}

		if (!date2.isValid() || (real_date > date2)) {
			u1.setColor(12); cerr <<"  ERROR: The date you inserted is not valid. Please use the format dd/mm/yyyy"; u1.setColor(15);
			Sleep(2000);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.cinClear();
			u1.clearScreen();
			continue;
		}
		else {
			u1.cinClear();
			isIn = false;
		}

		Rent * c = nullptr;

		u1.setColor(11); cout << "Rooms available between " << date1 << " and " << date2 << " in " << city << ": \n\n"; u1.setColor(15);

		for (size_t i = 0; i < rentsVec.size(); i++) {
			if (rentsVec[i].isValid(date1, date2) && (rentsVec[i].getCity() == city)) {
				if (rentsVec.at(i).getTypeRent() == "Hotel") {
					u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
					cout << "Type of accommodation: " << rentsVec.at(i).getTypeRent() << endl;
					cout << "Name: " << rentsVec.at(i).getName() << endl;
					cout << "Available from: " << rentsVec.at(i).getDataInicio();
					cout << "  To: " << rentsVec.at(i).getDataFim() << endl;
					cout << "Room type: " << rentsVec.at(i).getType() << endl;
					cout << "Price per night: " << rentsVec.at(i).getPrice() << endl;
					cout << "Room's capacity: " << rentsVec.at(i).getNumPeople() << endl << endl;
					counter++;
					v.push_back(i);
				}
				else if (rentsVec.at(i).getTypeRent() == "Apartment") {
					u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
					cout << "Type of accommodation: " << rentsVec.at(i).getTypeRent() << endl;
					cout << "Name: " << rentsVec.at(i).getName() << endl;
					cout << "Available from: " << rentsVec.at(i).getDataInicio();
					cout << "  To: " << rentsVec.at(i).getDataFim() << endl;
					cout << "Has Kitchen: " << rentsVec.at(i).getKitchen() << endl;
					cout << "Has Living Room: " << rentsVec.at(i).getLivingRoom() << endl;
					cout << "Has Suite: " << rentsVec.at(i).getSuite() << endl;
					cout << "Price per night: " << rentsVec.at(i).getPrice() << endl;
					cout << "Room's capacity: " << rentsVec.at(i).getNumPeople() << endl << endl;
					counter++;
					v.push_back(i);

				}
				else {
					u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
					cout << "Type of accommodation: " << rentsVec.at(i).getTypeRent() << endl;
					cout << "Name: " << rentsVec.at(i).getName() << endl;
					cout << "Available from: " << rentsVec.at(i).getDataInicio();
					cout << "  To: " << rentsVec.at(i).getDataFim() << endl;
					cout << "Price per night: " << rentsVec.at(i).getPrice() << endl;
					cout << "Room's capacity: " << rentsVec.at(i).getNumPeople() << endl << endl;
					counter++;		
					v.push_back(i);

				}
			}
			else
				temp++;
		}

		if (counter == 1) {
			u1.setColor(12); cerr << "  There are no rents available between the dates specified."; u1.setColor(15);
			Sleep(500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1000);
			u1.clearScreen();
			continue;
		}

		cout << "Insert the option's number: ";
		cin >> option;

		xPrice = rentsVec[v[option-1]].getPrice();

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
			continue;
		}
		else {
			u1.cinClear();
			isIn = false;
		}
	}

	isIn = true;

	while (isIn) {

		Date date1 = Date(dateB);
		Date date2 = Date(dateE);


		if (!(rentsVec[v[option - 1]].getTypeRent() == "Hotel")) {
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
				continue;
			}

			for (int index = 0; index < rentsVec.size(); index++) {
				if (n_people > rentsVec.at(index).getNumPeople()) {
					u1.setColor(12); cerr << endl << "  ERROR: The value you inserted exceeds the room's maximum capacity."; u1.setColor(15);
					Sleep(1500);
					cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
					Sleep(1500);
					u1.cinClear();
					continue;
				}
				else {
					cin.clear();
					isIn = false;
				}
			}
		}

		isIn = false;
	}
	Date date1 = Date(dateB);
	Date date2 = Date(dateE);
	int nif;
	isIn = true;
	while (isIn) {
		if (Corporation::instance()->username == "")
		{
			cout << "What is your NIF?\nNIF:" << endl;
			cin >> nif;
			if (cin.eof()) {
				u1.cancelMessage();
				corpMenu.RegisterMenu();
			}
			if (cin.fail())
			{
				cout << "\nInvalid input. Retrying last step.\n";
				continue;
			}
		}
		else
		{
			nif = rentsVec[v[option -1]].getNif();
			isIn = false;
		}
		isIn = false;
			
	}
	
	float totalPrice = xPrice*(date2.minus(date1));
	rentsVec[v[option - 1]].setReservation(Reservation(nif, totalPrice, date1, date2));

	u1.successMessage();
	return;
}

void Corporation::cancelReservation()
{
	if (Corporation::instance()->username == "")
	{
		u1.setColor(14);
		cout << "Only registered users can access this feature. Sign in to take full advantage of our service!";  u1.setColor(15);
		return;
	}
#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);

	long nif_user;
	for (int i = 0; i < usersVec.size(); i++)
	{
		if (usersVec.at(i).getUsername() == username)
			nif_user = usersVec.at(i).getNif();
	}

	bool found = false;
	for (int j = 0; j < rentsVec.size(); j++)
	{
		for (int k = 0; k < rentsVec.at(j).getReservations().size(); k++)
		{
			if (rentsVec.at(j).getReservations().at(k).getnif() == nif_user)
			{
				found = true;
			}
		}
	}

	if (found)
	{
		cout << "List of your reservations : " << endl << endl;
		for (int j = 0; j < rentsVec.size(); j++)
		{
			for (int k = 0; k < rentsVec.at(j).getReservations().size(); k++)
			{
				if (rentsVec.at(j).getReservations().at(k).getnif() == nif_user)
				{
					cout << "City : " << rentsVec.at(j).getCity() << endl;
					cout << "Type of accommodation : " << rentsVec.at(j).getTypeRent() << endl;
					cout << "Name : " << rentsVec.at(j).getName() << endl;
					cout << "Date of Check-in : " << rentsVec.at(j).getReservations().at(k).getDate1();
					cout << "Date of Check-out : " << rentsVec.at(j).getReservations().at(k).getDate2() << endl;
					cout << "Price : " << rentsVec.at(j).getReservations().at(k).getPrice() << endl;
					cout << "Room's capacity: " << rentsVec.at(j).getNumPeople() << endl;
					if (rentsVec.at(j).getLivingRoom() && rentsVec.at(j).getSuite() && rentsVec.at(j).getKitchen())
						cout << "Includes : LivingRoom, Suite and Kitchen" << endl;
					else if (rentsVec.at(j).getLivingRoom() && rentsVec.at(j).getKitchen())
						cout << "Includes : LivingRoom and Kitchen" << endl;
					else if (rentsVec.at(j).getLivingRoom() && rentsVec.at(j).getSuite())
						cout << "Includes : LivingRoom and Suite" << endl;
					else if (rentsVec.at(j).getSuite() && rentsVec.at(j).getKitchen())
						cout << "Includes : Suite and Kitchen" << endl;
					else if (rentsVec.at(j).getKitchen())
						cout << "Includes : Kitchen" << endl;
					else if (rentsVec.at(j).getSuite())
						cout << "Includes : Suite" << endl;
					else if (rentsVec.at(j).getLivingRoom())
						cout << "Includes : LivingRoom" << endl;
				}
				cout << endl;
			}
		}
	}
	else
	{
		cout << " \n You havent made any reservations yet!" << endl;
		Sleep(2000);
		return;
	}

	string name_answer;
	cout << " Which one would you like to cancel :";
	getline(cin, name_answer);

	vector<Reservation>x_vec;
	for (int i = 0; i < rentsVec.size(); i++)
	{
		for (int j = 0; j < rentsVec.at(i).getReservations().size(); j++)
		{
			if (name_answer == rentsVec.at(i).getName() && nif_user == rentsVec.at(i).getReservations().at(j).getnif())
			{
				string answer;
				cout << "Do you want to confirm ? (yes|No)";
				getline(cin, answer);
				if (cin.eof()) {
					u1.cancelMessage();
					corpMenu.RegisterMenu();
				}
				if (answer == "Yes" || answer == "yes")
				{
					Date x = rentsVec.at(i).getReservations().at(j).getDate1() - real_date;
					if (x.getYear() != 0 || x.getMonth() > 0)
						cout << " You will receive " << rentsVec.at(i).getReservations().at(j).getPrice() << " euros." << endl;
					else if (x.getDay() >= 15)
						cout << "You will receive " << rentsVec.at(i).getReservations().at(j).getPrice() / 2 << " euros." << endl;
					else
						cout << "You will not receive any money." << endl;


					x_vec = rentsVec.at(i).getReservations();
					x_vec.erase(x_vec.begin() + j);
					Sleep(2000);
				}
				else
				{
					cout << "You canceled the operation." << endl;
					Sleep(2000);
					return;
				}
			}
		}
	}

	for (int i = 0; i < rentsVec.size(); i++)
	{
		for (int j = 0; j < rentsVec.at(i).getReservations().size(); j++)
		{
			if (name_answer == rentsVec.at(i).getName() && nif_user == rentsVec.at(i).getReservations().at(j).getnif())
			{
				rentsVec.at(i).setReservationVector(x_vec);
			}
		}
	}
}

void Corporation::printUsersReservations()
{
	int counter = 1;
	for (int i = 0; i < rentsVec.size(); i++)
		if (Corporation::instance()->username == usersVec[i].getUsername())
		{
			vector<Reservation> x = rentsVec[i].getReservations();
			for (int j = 0; j < x.size(); j++)
			{
				cout << "Reservation " << counter << ":\nBeginning date: " << x[j].getDate1().getDay() << "/" << x[j].getDate1().getMonth() << "/" << x[j].getDate1().getYear() << ", whose price totals " << x[j].getPrice() << ".\n";
				counter++;
			}
			Sleep(1000);
			for (int j = 0; j < rentsVec[i].getReservations().size(); j++) {
				cout << "Reservation numeber " << counter << " starting on date " << rentsVec[i].getReservations()[j].getDate1() << " ,finishing on date " << rentsVec[i].getReservations()[j].getDate2() << " ,whose price totals " << rentsVec[i].getReservations()[j].getPrice() << ".\n";
				counter++;
			}
		}
	if (counter == 1) {
		cout << "There are currently no reservations made in your name... \nYou can add a reservation in your name in the Menu.\n";
	}
	u1.pressToContinueMessage();


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