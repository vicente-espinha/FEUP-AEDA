#include "Rent.h"

// ALUGUER

template <typename T>
Rent<T>::Rent(string typeRent, string c, Date dataI, Date dataF, int n)
{
	city = c; dataBegin = dataI; dataEnd = dataF; numPeople = n;
}

// HOTEL

template <typename T>
Hotel<T>::Hotel(string typeRent, string name, string cidade, Date dataI, Date dataF, string tipo, float preco, int numOcupantes) //: Rent(typeRent, cidade, dataI, dataF, numOcupantes)
{
	nameHotel = name;
	type = tipo;
	price = preco;
}

template <typename T>
T Hotel<T>::buildRent()
{
	string city;
	int n;
	float price;
	string name;
	cout << "What is the name of the hotel?\n\n";
	cin >> name;
	bool isIn = true; // Este boleano � s� um sistema que usei para implementar uma dete��o de erro, com possibilidade de repeti��o
	cout << "What is the city where you wish to make your hotel rent available?\n\n";
	cin >> city;
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
		if (invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month1;
		if (invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year1;
		if (invalidInputNoRetry())
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
		if (invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month2;
		if (invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year2;
		if (invalidInputNoRetry())
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
		// pode levar mais panisguices aqui malta

		if (n == 1) {
			numPeople = 1;
			return Hotel("Hotel", string name, string city, d1, d2, "Simple Room", price, numPeople);
		}
		else if (n == 2) {
			numPeople = 2;
			return Hotel("Hotel", string name, string city, d1, d2, "Double Room", price, numPeople);
		}
		else if (n == 3) {
			numPeople = 3;
			return Hotel("Hotel", string name, string city, d1, d2, "Double Room with additional bed", price, numPeople);
		}
		else if (n == 4) {
			numPeople = 3;
			return Hotel("Hotel", string name, string city, d1, d2, "Triple Room", price, numPeople);
		}
		else
		{
			invalidInputNoRetry();
			continue;
		}

	}
}

// BED'N'BREAKFAST

template <typename T>
bedNbreakfast<T>::bedNbreakfast(string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes) : Rent(cidade, dataI, dataF, numOcupantes)
{
	this->namebnb = name;
}

template <typename T>
T bedNbreakfast<T>::buildRent()
{
	string city;
	int n;
	float price;
	bool isIn = true; // Este boleano � s� um sistema que usei para implementar uma dete��o de erro, com possibilidade de repeti��o
	cout << "What is the city where you wish to make your Bed'n'Breakfast rent available?\n\n";
	cin >> city;

	while (isIn) // NumOcupantes
	{
		cout << "\nWhat is the number of people staying in the B'n'B?\n\n" << endl;
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
		if (invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month1;
		if (invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year1;
		if (invalidInputNoRetry())
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
		if (invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month2;
		if (invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year2;
		if (invalidInputNoRetry())
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

template <typename T>
sharedHouse<T>::sharedHouse(string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes) : Rent(typeRent, cidade, dataI, dataF, numOcupantes)
{
	this->nameSH = name;
}


template <typename T>
T sharedHouse<T>::buildRent()
{
	string city;
	int n;
	float price;
	bool isIn = true; // Este boleano � s� um sistema que usei para implementar uma dete��o de erro, com possibilidade de repeti��o
	cout << "What is the city where you wish to make your shared-house rent available?\n\n";
	cin >> city;

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
		if (invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month1;
		if (invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year1;
		if (invalidInputNoRetry())
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
		if (invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month2;
		if (invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year2;
		if (invalidInputNoRetry())
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

	return sharedHouse("Shared House", name, city, d1, d2, price, numPeople);
}

// FLAT

template <typename T>
flat<T>::flat(string typeRent, string name, string cidade, Date dataI, Date dataF, float preco, int numOcupantes) : Rent(typeRent, cidade, dataI, dataF, numOcupantes)
{
	this->nameFlat = name;
}

template <typename T>
T flat<T>::buildRent()
{

	string city;
	int n;
	float price;
	bool isIn = true; // Este boleano � s� um sistema que usei para implementar uma dete��o de erro, com possibilidade de repeti��o
	cout << "What is the city where you wish to make your shared-house rent available?\n\n";
	cin >> city;

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
		if (invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month1;
		if (invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year1;
		if (invalidInputNoRetry())
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
		if (invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month2;
		if (invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year2;
		if (invalidInputNoRetry())
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

template <typename T>
apartment<T>::apartment(string tipoRent, string name, string cidade, Date dataI, Date dataF, int numOcupantes, int numrooms, bool kitchen, bool suite, bool livingroom) : Rent(typeRent, cidade, dataI, dataF, numOcupantes)
{
	nameApartment = name;
	hasKitchen = kitchen;
	hasSuite = suite;
	hasLivingRoom = livingroom;
}

template<typename T>
T apartment<T>::buildRent()
{
	string city;
	int n;
	float price;
	bool isIn = true; // Este boleano � s� um sistema que usei para implementar uma dete��o de erro, com possibilidade de repeti��o
	cout << "What is the city where you wish to make your apartment rent available?\n\n";
	cin >> city;

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
		cout << "Does it have a living room? (y/n)\n";
		cin >> x;
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
			continue;
		}
	}

	while (isIn)
	{
		cout << "Does it have a kitchen? (y/n)\n";
		cin >> x;
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
			continue;
		}
	}
	int day1, day2, month1, month2, year1, year2;
	Date d1, d2;

	while (isIn) // Datas
	{
		cout << "/nBeginning date:\nDay: ";
		cin >> day1;
		if (invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month1;
		if (invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year1;
		if (invalidInputNoRetry())
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
		cin >> room;
		if (invalidInputNoRetry())
			continue;
		cout << "How many people per room?\n";
		cin >> people;
		if (invalidInputNoRetry())
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
		if (invalidInputNoRetry())
			continue;
		cout << "\nMonth:";
		cin >> month2;
		if (invalidInputNoRetry())
			continue;
		cout << "\nYear:";
		cin >> year2;
		if (invalidInputNoRetry())
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
	string n;
	cout << "Finally, under which name is the apartment rented?\n";
	cin >> n;
	
	return apartment("Apartment", n, city, d1, d2, price, people, rooms, k, s, lr);
}
