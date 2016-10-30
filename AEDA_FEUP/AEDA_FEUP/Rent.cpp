#include "Rent.h"

// ALUGUER

Rent::Rent(string c, Date dataI, Date dataF, int d, int n)
{
	city = c; dataBegin = dataI; dataEnd = dataF; durationRent = d; numPeople = n;
}

// HOTEL

Hotel::Hotel(string nome, string cidade, Date dataI, Date dataF, string tipo, int duracao, float preco, int numOcupantes) : Rent(cidade, dataI,dataF,duracao,numOcupantes)
{
	nameHotel = nome;
	type = tipo;
	price = preco;
}

Hotel Hotel::buildRent()
{
	string x;
	int n;
	float price;
	bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição
	cout << "What is the city where you wish to make your hotel rent available?\n\n";
	cin >> x;
	this->city = x;  // Cidade

	while (isIn) // NumOcupantes
	{
		cout << "\nWhat is the type of room you want to add? You may add:" << endl;
		cout << "1 - Simple Room\n2 - Double room\n3 - Double room with aditional bed\n4 - Triple Room" << endl;
		// pode levar mais panisguices aqui malta

		if (n == 1)
			numPeople = 1;
		else if (n == 2)
			numPeople = 2;
		else if (n == 3)
			numPeople = 3;
		else if (n == 4)
			numPeople = 3;
		else
		{
			invalidInputNoRetry();
			continue;
		}
		
	}
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
		if(invalidInputNoRetry())
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


}
