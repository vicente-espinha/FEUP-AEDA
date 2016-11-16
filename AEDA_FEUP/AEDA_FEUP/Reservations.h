#include "Date.h"
#include "Rent.h"

using namespace std;

class Reservation {
private:
	Date d1, d2;
	double total_price;
	int n_people;
	string username, type_rent, type_type_rent, city;
	Rent *rent;
public:
	Reservation(string name,string city, string type, string type_type, int n, Date d1, Date d2, Rent *rent);
	string getusername() { return username; };
	string gettype_rent() { return type_rent; };
	string gettype_type_rent() { return type_type_rent; };
	double getprice() { return total_price; };
	Date getDate1() {return d1;};
	Date getDate2() { return d2;};
	int getn_people() { return n_people; };
	Rent getrent() { return *rent; };
	string getcity() { return city; };
};