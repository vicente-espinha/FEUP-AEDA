#include "Date.h"
#include "Rent.h"

using namespace std;


/*! \brief Brief description.
*
*  Classe dedicada às reservas feitas pelos clientes.
*/
class Reservation {
private:
	Date d1, d2;/*!< date of the check-in and date of the check-out */
	double total_price;/*!< a double for the total price of the reservation */
	int n_people;/*!< an integer to the number of persons that will be in rented place */
	string username, type_rent, type_type_rent, city;/*!< "username" is the username of the client, "type_rent" is the type of rent, "type_type_rent" is for some types,for example for for the type hotel , you could have Single Room as type_type_rent and "city" is the city where they will stay*/
	Rent *rent;/*!< a pointer to a rent that corresponds to the reservation */
public:
	Reservation(string name,string city, string type, string type_type, int n, Date d1, Date d2, Rent *rent);
	string getusername() { return username; };//!< a function that returns the username.
	string gettype_rent() { return type_rent; };//!< a function that returns the typr_rent.
	string gettype_type_rent() { return type_type_rent; };//!< a function that returns the type_type_rent.
	double getprice() { return total_price; };//!< a function that returns the total price of the reservation.
	Date getDate1() {return d1;};//!< a function that returns the date of the check-in.
	Date getDate2() { return d2;};//!< a function that returns the date of the check-out.
	int getn_people() { return n_people; };//!< a function that returns the number of the people that will be in the rented place.
	Rent getrent() { return *rent; };//!< a function that returns a pointer to a rent that corresponds to the reservation.
	string getcity() { return city; };//!< a function that returns the city where they will stay.
	friend bool operator==(const Reservation &R1, Reservation &R2);//!< a function that returns true if the two reservations ar the same,else returns false.
	friend ostream& operator<<(ostream& out, Reservation & R1);//!< a function that does the overload of the operator <<.
};