#include "Date.h"
#include "Rent.h"

using namespace std;
template <typename T>
class Reservation {
private:
	Date d1, d2;
	double total_price;
	int n_people;
	string name, type_rent,type_type_rent;
	Rent<T> *rent;
public:
	Reservation(string name, string type, string type_type, int n,double price, Date d1, Date d2,Rent<T> * rent);
	string getname() { return name; };
	string gettype_rent() { return type_rent; };
	string gettype_type_rent() { return type_type_rent; };
	double getprice() { return total_price; };
	Date getDate1() {return d1;};
	Date getDate2() { return d2;};
	int getn_people() { return n_people; };
	Rent<T> getrent() { return rent; };
};