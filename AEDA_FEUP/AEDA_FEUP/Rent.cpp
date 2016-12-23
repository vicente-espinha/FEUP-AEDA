#include "Rent.h"
#include "Corporation.h"


Utilities u2;
Menu rentMenu;

// ALUGUER
Rent::Rent(long nif, string typeRent, string name2 ,string c, Date dataI, Date dataF, float p, int n)
{
	city = c; dataBegin = dataI; dataEnd = dataF; numPeople = n; price = p; this->typeRent = typeRent; name = name2; this->nif = nif;
}

int Rent::lastRent()
{
	//Gets the PC's date
#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);
	
	Date final = reserved[0].getDate1();
		for (int i = 0; i < reserved.size() - 1; i++)
		{
			if (reserved[i].getDate1() < reserved[i + 1].getDate1())
			{
				final = reserved[i + 1].getDate1();
			}
		}
	return real_date.minus(final);
}



bool Rent::operator<(Rent x)
{
	if (lastRent() > x.lastRent())
		return true;
	else
		return false;
}



bool Rent::isValid(Date d1, Date d2)
{
	bool valid = true;
	if (this->getDataInicio() > d1 || this->getDataFim() < d2)
		return false;
	for (int i = 0; i < reserved.size(); i++)
	{
		if ((reserved[i].getDate1() < d2) && (reserved[i].getDate2() > d2))
			valid = false;
		if ((reserved[i].getDate1() < d1) && (reserved[i].getDate2() > d1))
			valid = false;
		if ((reserved[i].getDate2() < d2) && (reserved[i].getDate1() > d1))
			valid = false;
	}
	return valid;
}

// HOTEL

Hotel::Hotel(long nif, string typeRent, string name, string cidade, Date dataI, Date dataF, string type, float preco, int numOcupantes) : Rent(nif, typeRent, name, cidade, dataI, dataF, preco, numOcupantes)
{
	nameHotel = name;
	this->type = type;

}



Hotel Hotel::buildRent(long nif)
{
	string city;
	int n;
	float price;
	string name;

	//Gets the PC's date
#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);

	city = Corporation::instance()->cities();
	u2.clearScreen();
	u2.cinClear();

	u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
	u2.setColor(14); cout << "City: " << city << endl << endl; u2.setColor(15);

	cout << "Rent's name: ";
	getline(cin, name);

	if (cin.eof()) {
		u2.cancelMessage();
		rentMenu.SuppliersMenu();
	}
	
	u2.clearScreen();

	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição
	
	while (isIn) // Preco
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << endl; u2.setColor(15);

		cout << "\nPrice per night: ";
		cin >> price;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (cin.fail())
		{
			u2.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else
		{
			this->price = price;
			isIn = false;
			u2.clearScreen();
		}
	}

	isIn = true;

	string date1, date2;
	Date d1, d2;

	while (isIn) {

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nPrice per night: " << price << endl; u2.setColor(15);

		cout << "\nBegin date: "; cin >> date1;

		Date d1 = Date(date1);

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (!d1.isValid() || (real_date > d1)) {
			u2.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else {
			u2.cinClear();
		}

		cout << "\nEnd date: "; cin >> date2; cout << endl;

		Date d2 = Date(date2);

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (!d2.isValid() || (real_date > d2)) {
			u2.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid. Please use the format dd/mm/yyyy"; u2.setColor(15);
			Sleep(2000);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else {
			u2.cinClear();
			u2.clearScreen();
			isIn = false;
		}
	}

	isIn = true;
	while (isIn) // NumOcupantes
	{

		Date d1 = Date(date1);
		Date d2 = Date(date2);

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nPrice per night: " << price << "\nBegin Date: " << d1 << "    End Date: " << d2 << endl; u2.setColor(15);

		u2.setColor(11); cout << "\nWhat is the type of room you want to add? You may add:" << endl << endl; u2.setColor(15);
		cout << "1 - Simple Room\n2 - Double room\n3 - Double room with aditional bed\n4 - Triple Room" << endl << endl;
		cout << "Inser the number corresponding to the type you wish to add: ";
		cin >> n;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		u2.clearScreen();

		if (n == 1) {
			numPeople = 1;
			return Hotel(nif, "Hotel", name, city, d1, d2, "Simple Room", price, numPeople);
		}
		else if (n == 2) {
			numPeople = 2;
			return Hotel(nif,"Hotel", name, city, d1, d2, "Double Room", price, numPeople);
		}
		else if (n == 3) {
			numPeople = 3;
			return Hotel(nif, "Hotel", name, city, d1, d2, "Double Room with additional bed", price, numPeople);
		}
		else if (n == 4) {
			numPeople = 3;
			return Hotel(nif, "Hotel", name, city, d1, d2, "Triple Room", price, numPeople);
		}
		else
		{
			u2.invalidInputNoRetry();
			continue;
		}

	}
}

// BED'N'BREAKFAST

bedNbreakfast::bedNbreakfast(long nif, string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes) : Rent(nif, typeRent, name ,cidade, dataI, dataF, preco, numOcupantes)
{
	this->namebnb = name;
}

bedNbreakfast bedNbreakfast::buildRent(long nif)
{
	string city;
	int n;
	float price;
	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição

#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);

	city = Corporation::instance()->cities();
	u2.clearScreen();
	u2.cinClear();

	u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
	u2.setColor(14); cout << "City: " << city << endl << endl; u2.setColor(15);

	cout << "Rent's name: ";
	string name;
	getline(cin, name);

	if (cin.eof()) {
		u2.cancelMessage();
		rentMenu.SuppliersMenu();
	}

	u2.clearScreen();

	while (isIn) // NumOcupantes
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << endl; u2.setColor(15);

		cout << "\nNumber of people the B'n'B can accommodate: ";
		int people;
		cin >> people;

		if (cin.fail())
		{
			u2.setColor(12); cerr << endl << "  ERROR: Input can only contain digits. "; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		u2.cinClear();
		this->numPeople = people;
		u2.clearScreen();
		break;
	}
	isIn = true;

	while (isIn) // Preco
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nBed n' Breakfast capacity: " << numPeople << endl; u2.setColor(15);

		cout << "\nPrice per night: ";
		cin >> price;
		if (cin.fail())
		{
			u2.setColor(12); cerr << endl << "  ERROR: Input can only contain digits. "; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else
		{
			u2.cinClear();
			this->price = price;
			u2.clearScreen();
			break;
		}
	}
	isIn = true;

	string date1, date2;

	while (isIn) // Datas
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nBed n' Breakfast capacity: " << numPeople << "\nPrice per night: " << price << endl; u2.setColor(15);

		cout << "\nBegin date: "; cin >> date1;

		Date d1 = Date(date1);

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (!d1.isValid() || (real_date > d1)) {
			u2.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else {
			u2.cinClear();
		}

		cout << "\nEnd date: "; cin >> date2; cout << endl;

		Date d2 = Date(date2);

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (!d2.isValid() || (real_date > d2)) {
			u2.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid. Please use the format dd/mm/yyyy"; u2.setColor(15);
			Sleep(2000);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else {
			u2.cinClear();
			u2.clearScreen();
			isIn = false;
		}
	}

	Date d1 = Date(date1);
	Date d2 = Date(date2);

	u2.clearScreen();

	return bedNbreakfast(nif, "Bed'n'Breakfast", name, city, d1, d2, price, numPeople);
}


// SHARED-HOUSE

sharedHouse::sharedHouse(long nif, string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes) : Rent(nif, typeRent, name, cidade, dataI, dataF, preco, numOcupantes)
{
	this->nameSH = name;
}


sharedHouse sharedHouse::buildRent(long nif)
{
	string city, name;
	int n;
	float price;
	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição

#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);

	city = Corporation::instance()->cities();
	u2.cinClear();
	u2.clearScreen();

	u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
	u2.setColor(14); cout << "City: " << city << endl << endl; u2.setColor(15);

	cout << "Rent's name: ";
	getline(cin, name);

	if (cin.eof()) {
		u2.cancelMessage();
		rentMenu.SuppliersMenu();
	}

	u2.clearScreen();

	while (isIn) // NumOcupantes
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << endl; u2.setColor(15);

		cout << "\nNumber of people the house can accomodate:  ";
		int people;
		cin >> people;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (cin.fail()){
			u2.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		this->numPeople = people;
		u2.clearScreen();
		isIn = false;
	}
	
	isIn = true;

	while (isIn) // Price
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nShared House capacity: " << numPeople << endl; u2.setColor(15);

		cout << "\nCost per night:  ";
		cin >> price;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (cin.fail())
		{
			u2.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else
		{
			this->price = price;
			u2.clearScreen();
			isIn = false;
		}
	}

	isIn = true;

	string date1, date2;

	while (isIn) // Datas
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nShared House capacity: " << numPeople << "\nPrice per night: " << price << endl; u2.setColor(15);

		cout << "\nBegin date: "; cin >> date1;

		Date d1 = Date(date1);

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (!d1.isValid() || (real_date > d1)) {
			u2.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else {
			u2.cinClear();
		}

		cout << "\nEnd date: "; cin >> date2; cout << endl;

		Date d2 = Date(date2);

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (!d2.isValid() || (real_date > d2)) {
			u2.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid. Please use the format dd/mm/yyyy"; u2.setColor(15);
			Sleep(2000);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else {
			u2.cinClear();
			u2.clearScreen();
			isIn = false;
		}
	}

	Date d1 = Date(date1);
	Date d2 = Date(date2);

	u2.clearScreen();

	return sharedHouse(nif,"Shared House", name, city, d1, d2, price, numPeople);
}

// FLAT

flat::flat(long nif, string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes) : Rent(nif, typeRent, name ,cidade, dataI, dataF,preco, numOcupantes)
{
	this->nameFlat = name;
}

flat flat::buildRent(long nif)
{
	string city;
	int n;
	float price;
	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição

#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);
	
	city = Corporation::instance()->cities();
	u2.clearScreen();
	u2.cinClear();

	u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
	u2.setColor(14); cout << "City: " << city << endl << endl; u2.setColor(15);

	string name;
	cout << "Rent's name: ";
	getline(cin, name);

	if (cin.eof()) {
		u2.cancelMessage();
		rentMenu.SuppliersMenu();
	}

	u2.clearScreen();

	while (isIn) // NumOcupantes
	{
		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << endl; u2.setColor(15);

		cout << "\nNumber of people the flat can accommodate: ";

		int people;
		cin >> people;

		if (cin.fail())
		{
			u2.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		this->numPeople = people;
		u2.clearScreen();
		u2.cinClear();
		break;
	}
	isIn = true;

	while (isIn) // Preco
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nFlat's capacity: " << numPeople << endl; u2.setColor(15);

		cout << "\nPrice per night: ";
		cin >> price;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (cin.fail())
		{
			u2.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else
		{
			this->price = price;
			u2.clearScreen();
			break;
		}
	}
	isIn = true;

	string date1, date2;

	while (isIn) // Datas
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nFlat's capacity: " << numPeople << "\nPrice per night: " << price << endl; u2.setColor(15);

		cout << "\nBegin date: "; cin >> date1;

		Date d1 = Date(date1);

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (!d1.isValid() || (real_date > d1)) {
			u2.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else {
			u2.cinClear();
		}

		cout << "\nEnd date: "; cin >> date2; cout << endl;

		Date d2 = Date(date2);

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (!d2.isValid() || (real_date > d2)) {
			u2.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid. Please use the format dd/mm/yyyy"; u2.setColor(15);
			Sleep(2000);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else {
			u2.cinClear();
			break;
		}
	}

	Date d1 = Date(date1);
	Date d2 = Date(date2);

	u2.clearScreen();

	return flat(nif, "Flat", name, city, d1, d2, price, numPeople);

}

// APARTMENT

apartment::apartment(long nif, string tipoRent, string name, string cidade, Date dataI, Date dataF, float price, int numOcupantes, int numrooms, bool kitchen, bool suite, bool livingroom) : Rent(nif, tipoRent, name, cidade, dataI, dataF, price, numOcupantes)
{
	nameApartment = name;
	hasKitchen = kitchen;
	hasSuite = suite;
	hasLivingRoom = livingroom;
	numRooms = numrooms;
}

apartment apartment::buildRent(long nif)
{
	string city;
	int n;
	float price;
	int people;
	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição

#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);
	
	city = Corporation::instance()->cities();
	u2.clearScreen();
	u2.cinClear();

	u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
	u2.setColor(14); cout << "City: " << city << endl << endl; u2.setColor(15);

	string name;
	cout << "Rent's name: ";
	getline(cin, name);

	if (cin.eof()) {
		u2.cancelMessage();
		rentMenu.SuppliersMenu();
	}

	u2.clearScreen();

	while (isIn) // NumOcupantes
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << endl; u2.setColor(15);

		cout << "\nNumber of people the apartment can accommodate: ";
		cin >> people;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (cin.fail())
		{
			u2.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		this->numPeople = people;
		u2.clearScreen();
		break;
	}

	isIn = true;

	int peoplePerRoom, rooms;
	while (isIn)
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nApartment's capacity: " << numPeople << endl; u2.setColor(15);

		cout << "\nRooms available: ";
		cin >> rooms;

		if (rooms > numPeople) {
			u2.setColor(12); cerr << endl << "  ERROR: Number of rooms cannot exceed the number of people the apartment can accommodate."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (cin.fail())
		{
			u2.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}

		this->numRooms = rooms;

		cout << "\nPeople per room: ";
		cin >> peoplePerRoom;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (peoplePerRoom > (people / numRooms)) {
			u2.setColor(12); cerr << endl << "  ERROR: The number of people per room cannot be greater than the number of people\n         the apartment can accomodate and the number of rooms ratio."; u2.setColor(15);
			Sleep(2000);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}

		if (cin.fail())
		{
			u2.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}

		if (peoplePerRoom < 0 || peoplePerRoom > 4)
		{
			u2.setColor(12); cerr << endl << "  ERROR: Invalid number of people per room."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}

		u2.clearScreen();
		isIn = false;
	}

	isIn = true;
	u2.cinClear();

	while (isIn) // Preco
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nApartment's capacity: " << numPeople << "\nNumber of rooms: " << rooms << "\nPeople per room: " << peoplePerRoom << endl; u2.setColor(15);

		cout << "\nPrice per night: ";
		cin >> price;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (cin.fail())
		{
			u2.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else
		{
			this->price = price;
			u2.clearScreen();
			break;
		}
	}
	isIn = true;

	bool k, lr, s;
	string x;
	while (isIn)
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nApartment's capacity: " << numPeople << "\nNumber of rooms: " << rooms << "\nPeople per room: " << peoplePerRoom
							  << "\nPrice per night : " << price << endl; u2.setColor(15);

		cout << "\nIs it a suite? (y/n) ";
		cin >> x;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (x == "Y" || x == "y" || x == "yes")
		{
			s = true;
			isIn = false;
			break;
		}
		if (x == "n" || x == "no" || x == "N")
		{
			s = false;
			isIn = false;
			break;
		}
		else
		{
			cout << "\nInvalid input. Retrying.\n";
			u2.clearScreen();
			continue;
		}
	}

	isIn = true;
	u2.cinClear();

	while (isIn)
	{
	
		cout << "\nDoes it have a living room? (y/n) ";
		cin >> x;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (x == "Y" || x == "y" || x == "yes")
		{
			lr = true;
			isIn = false;
			break;
		}
		if (x == "n" || x == "no" || x == "N")
		{
			lr = false;
			isIn = false;
			break;
		}
		else
		{
			cout << "\nInvalid input. Retrying.\n";
			u2.clearScreen();
			continue;
		}
	}

	isIn = true;
	u2.cinClear();

	while (isIn)
	{
		cout << "\nDoes it have a kitchen? (y/n) ";
		cin >> x;

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (x == "Y" || x == "y" || x == "yes")
		{
			k = true;
			isIn = false;
			break;
		}
		if (x == "n" || x == "no" || x == "N")
		{
			k = false;
			isIn = false;
			break;
		}
		else
		{
			cout << "\nInvalid input. Retrying.\n";
			u2.clearScreen();
			continue;
		}
	}

	u2.clearScreen();
	isIn = true;
	
	string date1, date2;

	while (isIn) // Datas
	{

		u2.setColor(11); cout << "Rent: \n\n"; u2.setColor(15);
		u2.setColor(14); cout << "City: " << city << "\nRent's name: " << name << "\nApartment's capacity: " << numPeople << "\nNumber of rooms: " << rooms << "\nPeople per room: " << peoplePerRoom
			                  << "\nPrice per night : " << price;

		if (s) {
			cout << "\nSuite: Yes";
		}
		else {
			cout << "\nSuite: No";
		}

		if (lr) {
			cout << "\nLiving Room: Yes";
		}
		else {
			cout << "\nLiving Room: No";
		}

		if (k) {
			cout << "\nKitchen: Yes\n";
		}
		else {
			cout << "\nKitchen: No\n";
		}

		u2.setColor(15);


		cout << "\nBegin date: "; cin >> date1;

		Date d1 = Date(date1);

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (!d1.isValid() || (real_date > d1)) {
			u2.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid."; u2.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else {
			u2.cinClear();
		}

		cout << "\nEnd date: "; cin >> date2; cout << endl;

		Date d2 = Date(date2);

		if (cin.eof()) {
			u2.cancelMessage();
			rentMenu.SuppliersMenu();
		}

		if (!d2.isValid() || (real_date > d2)) {
			u2.setColor(12); cerr << endl << "  ERROR: The date you inserted is not valid. Please use the format dd/mm/yyyy"; u2.setColor(15);
			Sleep(2000);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u2.cinClear();
			u2.clearScreen();
			continue;
		}
		else {
			u2.cinClear();
			isIn = false;
		}
	}

	Date d1 = Date(date1);
	Date d2 = Date(date2);

	cout << numRooms;
	Sleep(4000);


	u2.clearScreen();

	
	return apartment(nif, "Apartment", name, city, d1, d2, price, numPeople, numRooms, k, s, lr);
}