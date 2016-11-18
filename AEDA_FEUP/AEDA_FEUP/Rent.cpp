#include "Rent.h"
#include "Corporation.h"


Utilities u2;

// ALUGUER
Rent::Rent(string typeRent, string name2 ,string c, Date dataI, Date dataF, float p, int n)
{
	city = c; dataBegin = dataI; dataEnd = dataF; numPeople = n; price = p; this->typeRent = typeRent; name = name2;
}

// HOTEL

Hotel::Hotel(string typeRent, string name, string cidade, Date dataI, Date dataF, string type, float preco, int numOcupantes) : Rent(typeRent, name, cidade, dataI, dataF, preco, numOcupantes)
{
	nameHotel = name;
	this->type = type;

}

Hotel Hotel::buildRent()
{
	string city;
	int n;
	float price;
	string name;
	cout << "What is the name of the hotel?\n\n";
	cin >> name;
	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição
	city = Corporation::instance()->cities();
	isIn = true;

	while (isIn) // Preco
	{
		cout << "\nWhat is the price this room is going to cost?\n";
		cin >> price;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "\n\n The input was invalid. Retrying last segment.\n\n";
			continue;
		}
		else
		{
			this->price = price;
			isIn = false;
			break;
		}
	}
	isIn = true;

	int day1, day2, month1, month2, year1, year2;
	Date d1, d2;

	while (isIn) // Datas
	{
		cout << "/nBeginning date:\nDay: ";
		cin >> day1;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month1;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year1;
		if (u2.invalidInputNoRetry())
			continue;
		d1 = Date(day1, month1, year1);
		if (d1.isValid() == false)
		{
			cout << "\nThis date is invalid. Repeating this date.\n";
		}
	}

	while (isIn) // Datas
	{
		cout << "/nEnding date:\nDay: ";
		cin >> day2;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month2;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year2;
		if (u2.invalidInputNoRetry())
			continue;
		d2 = Date(day2, month2, year2);

		if (d2.isValid() == false)
		{
			cout << "\nThis date is invalid. Repeating this date.\n";
		}

		if (d2 < d1)
		{
			cout << "Ending date is earlier than beginnig date. Repeating this date.\n";
			continue;
		}
	}

	while (isIn) // NumOcupantes
	{
		cout << "\nWhat is the type of room you want to add? You may add:" << endl;
		cout << "1 - Simple Room\n2 - Double room\n3 - Double room with aditional bed\n4 - Triple Room" << endl;
		cin >> n;
		// pode levar mais panisguices aqui malta

		if (n == 1) {
			numPeople = 1;
			return Hotel("Hotel", name, city, d1, d2, "Simple Room", price, numPeople);
		}
		else if (n == 2) {
			numPeople = 2;
			return Hotel("Hotel", name, city, d1, d2, "Double Room", price, numPeople);
		}
		else if (n == 3) {
			numPeople = 3;
			return Hotel("Hotel", name, city, d1, d2, "Double Room with additional bed", price, numPeople);
		}
		else if (n == 4) {
			numPeople = 3;
			return Hotel("Hotel", name, city, d1, d2, "Triple Room", price, numPeople);
		}
		else
		{
			u2.invalidInputNoRetry();
			continue;
		}

	}
}

// BED'N'BREAKFAST

bedNbreakfast::bedNbreakfast(string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes) : Rent(typeRent, name ,cidade, dataI, dataF, preco, numOcupantes)
{
	this->namebnb = name;
}

bedNbreakfast bedNbreakfast::buildRent()
{
	Utilities u;
	string city;
	int n;
	float price;
	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição
	cout << "What is the city where you wish to make your Bed'n'Breakfast rent available?\n\n";
	cin >> city;
	cout << "\n What is the name of the B'n'B?\nName:";
	string name;
	cin >> name;

	while (isIn) // NumOcupantes
	{
		cout << "\nWhat is the number of people staying in the B'n'B?\n\n" << endl;
		int numPeople;
		cin >> numPeople;
		if (cin.fail())
		{
			u2.cinClear();
			cout << "\n\n The input was invalid. Retrying last segment.\n\n";
			continue;
		}
	}
	isIn = true;

	while (isIn) // Preco
	{
		cout << "\nWhat is the price it is going to cost?\n";
		cin >> price;
		if (cin.fail())
		{
			u2.cinClear();
			cout << "\n\n The input was invalid. Retrying last segment.\n\n";
			continue;
		}
		else
		{
			this->price = price;
			isIn = false;
			break;
		}
	}
	isIn = true;

	int day1, day2, month1, month2, year1, year2;
	Date d1, d2;

	while (isIn) // Datas
	{
		cout << "/nBeginning date:\nDay: ";
		cin >> day1;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month1;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year1;
		if (u2.invalidInputNoRetry())
			continue;
		d1 = Date(day1, month1, year1);
		if (d1.isValid() == false)
		{
			cout << "\nThis date is invalid. Repeating this date.\n";
		}
	}

	while (isIn) // Datas
	{
		cout << "/nEnding date:\nDay: ";
		cin >> day2;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month2;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year2;
		if (u2.invalidInputNoRetry())
			continue;
		d2 = Date(day2, month2, year2);

		if (d2.isValid() == false)
		{
			cout << "\nThis date is invalid. Repeating this date.\n";
		}

		if (d2 < d1)
		{
			cout << "Ending date is earlier than beginnig date. Repeating this date.\n";
			continue;
		}
	}
	return bedNbreakfast("Bed'n'Breakfast", name, city, d1, d2, price, numPeople);


}


// SHARED-HOUSE

sharedHouse::sharedHouse(string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes) : Rent(typeRent, name, cidade, dataI, dataF, preco, numOcupantes)
{
	this->nameSH = name;
}


sharedHouse sharedHouse::buildRent()
{
	string city, name;
	int n;
	float price;
	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição

	city = Corporation::instance()->cities();

	u2.cinClear();

	cout << "\nRent's name : ";
	cin >> name;

	while (isIn) // NumOcupantes
	{
		cout << "\nNumber of people the house can accomodate:  ";
		int numPeople;
		cin >> numPeople;
		if (cin.fail()){

			u2.cinClear();
			cout << "\n\n The input was invalid. Retrying last segment.\n\n";
			continue;
		}
		isIn = false;
	}
	
	isIn = true;

	while (isIn) // Price
	{
		cout << "\nCost per night:  ";
		cin >> price;
		if (cin.fail())
		{
			u2.cinClear();
			cout << "\n\n The input was invalid. Retrying last segment.\n\n";
			continue;
		}
		else
		{
			this->price = price;
			isIn = false;
		}
	}

	isIn = true;

	int day1, day2, month1, month2, year1, year2;
	Date d1, d2;

	while (isIn) // Datas
	{
		cout << "/nBeginning date:\nDay: ";
		cin >> day1;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month1;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year1;
		if (u2.invalidInputNoRetry())
			continue;
		d1 = Date(day1, month1, year1);
		if (d1.isValid() == false)
		{
			cout << "\nThis date is invalid. Repeating this date.\n";
		}
		else {
			isIn = false;
		}
	}

	isIn = true;
	while (isIn) // Datas
	{
		cout << "/nEnding date:\nDay: ";
		cin >> day2;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month2;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year2;
		if (u2.invalidInputNoRetry())
			continue;
		d2 = Date(day2, month2, year2);

		if (d2.isValid() == false)
		{
			cout << "\nThis date is invalid. Repeating this date.\n";
		}

		if (d2 < d1)
		{
			cout << "Ending date is earlier than beginnig date. Repeating this date.\n";
			continue;
		}
		else {
			isIn = false;
		}
	}

	return sharedHouse("Shared House", name, city, d1, d2, price, numPeople);
}

// FLAT

flat::flat(string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes) : Rent(typeRent, name ,cidade, dataI, dataF,preco, numOcupantes)
{
	this->nameFlat = name;
}

flat flat::buildRent()
{
	string city;
	int n;
	float price;
	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição
	cout << "What is the city where you wish to make your shared-house rent available?\n\n";
	cin >> city;
	string name;
	cout << "\nUnder which name would you like to make the rent available?\n";
	cin >> name;

	while (isIn) // NumOcupantes
	{
		cout << "\nWhat is the number of people staying?\n\n" << endl;
		int numPeople;
		cin >> numPeople;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "\n\n The input was invalid. Retrying last segment.\n\n";
			continue;
		}
	}
	isIn = true;

	while (isIn) // Preco
	{
		cout << "\nWhat is the price it is going to cost?\n";
		cin >> price;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "\n\n The input was invalid. Retrying last segment.\n\n";
			continue;
		}
		else
		{
			this->price = price;
			isIn = false;
			break;
		}
	}
	isIn = true;

	int day1, day2, month1, month2, year1, year2;
	Date d1, d2;

	while (isIn) // Datas
	{
		cout << "/nBeginning date:\nDay: ";
		cin >> day1;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month1;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year1;
		if (u2.invalidInputNoRetry())
			continue;
		d1 = Date(day1, month1, year1);
		if (d1.isValid() == false)
		{
			cout << "\nThis date is invalid. Repeating this date.\n";
		}
	}

	while (isIn) // Datas
	{
		cout << "/nEnding date:\nDay: ";
		cin >> day2;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month2;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year2;
		if (u2.invalidInputNoRetry())
			continue;
		d2 = Date(day2, month2, year2);

		if (d2.isValid() == false)
		{
			cout << "\nThis date is invalid. Repeating this date.\n";
		}

		if (d2 < d1)
		{
			cout << "Ending date is earlier than beginnig date. Repeating this date.\n";
			continue;
		}
	}

	return flat("Flat", name, city, d1, d2, price, numPeople);

}

// APARTMENT

apartment::apartment(string tipoRent, string name, string cidade, Date dataI, Date dataF, float price, int numOcupantes, int numrooms, bool kitchen, bool suite, bool livingroom) : Rent(tipoRent, name, cidade, dataI, dataF, price, numOcupantes)
{
	nameApartment = name;
	hasKitchen = kitchen;
	hasSuite = suite;
	hasLivingRoom = livingroom;
}

apartment apartment::buildRent()
{
	string city;
	int n;
	float price;
	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição
	cout << "What is the city where you wish to make your apartment rent available?\n\n";
	cin >> city;

	string name;
	cout << "\nUnder which name would you like to make the rent available?\n";
	cin >> name;

	while (isIn) // NumOcupantes
	{
		cout << "\nWhat is the number of people staying?\n\n" << endl;
		int numPeople;
		cin >> numPeople;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "\n\n The input was invalid. Retrying last segment.\n\n";
			continue;
		}
	}
	isIn = true;

	while (isIn) // Preco
	{
		cout << "\nWhat is the price it is going to cost?\n";
		cin >> price;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "\n\n The input was invalid. Retrying last segment.\n\n";
			continue;
		}
		else
		{
			this->price = price;
			isIn = false;
			break;
		}
	}
	isIn = true;

	bool k, lr, s;
	string x;
	while (isIn)
	{
		cout << "Is it a suite? (y/n)\n";
		cin >> x;
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
			continue;
		}
	}
	while (isIn)
	{
		cout << "Does it have a living room? (Y for yes)\n";
		cin >> x;
		if (x == "Y" || x == "y" || x == "yes")
		{
			lr = "Yes";
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
			continue;
		}
	}

	while (isIn)
	{
		cout << "Does it have a kitchen? (y/n)\n";
		cin >> x;
		if (x == "Y" || x == "y" || x == "yes")
		{
			k = "Yes";
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
			continue;
		}
	}
	int day1, day2, month1, month2, year1, year2;
	Date d1, d2;

	while (isIn) // Datas
	{
		cout << "/nBeginning date:\nDay: ";
		cin >> day1;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month1;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year1;
		if (u2.invalidInputNoRetry())
			continue;
		d1 = Date(day1, month1, year1);
		if (d1.isValid() == false)
		{
			cout << "\nThis date is invalid. Repeating this date.\n";
		}
	}
	int people, rooms;
	while (isIn)
	{
		cout << "How many rooms will there be available?\n";
		cin >> rooms;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "How many people per room?\n";
		cin >> people;
		if (u2.invalidInputNoRetry())
			continue;
		if (people < 0 || people > 4)
		{
			cout << "\nToo many people per room. Repeating last step.\n";
			continue;
		}
		isIn = false;
	}
	while (isIn) // Datas
	{
		cout << "/nEnding date:\nDay: ";
		cin >> day2;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month2;
		if (u2.invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year2;
		if (u2.invalidInputNoRetry())
			continue;
		d2 = Date(day2, month2, year2);

		if (d2.isValid() == false)
		{
			cout << "\nThis date is invalid. Repeating this date.\n";
		}

		if (d2 < d1)
		{
			cout << "Ending date is earlier than beginning date. Repeating this date.\n";
			continue;
		}
	}
	return apartment("Apartment", name, city, d1, d2, price, people, rooms, k, s, lr);
}
