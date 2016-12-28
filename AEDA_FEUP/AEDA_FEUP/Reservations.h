#include "Date.h"

using namespace std;


/*! \brief Brief description.
*
*  Class dedicated to the reservations that the users do.
*/
class Reservation {
private:
	string name;/*!< User's name for further storage in the BST */
	Date d1, d2, reservationDate;/*!< date of the check-in, check-out and the day the reservation was made*/
	long nif;/*!< nif of the user */
	double price;/*!< total price of the reservation */

public:
	Reservation(long nif,double price, Date d1, Date d2);
	//Reservation(string name, long nif, double price, Date d1, Date d2, Date reservationDate);
	Date getDate1() const {return d1;}//!< a function that returns the date of the check-in.
	Date getDate2() const { return d2;}//!< a function that returns the date of the check-out.
	double getPrice() const { return price; }//!< a function that returns the price.
	long getnif() const { return nif; }//!< a function that returns the city where they will stay.
	//Date getReservationDate() const { return reservationDate;}//!< a function that returns the date the reservation was made.
	//string getName() const { return name;}//!< a function that returns the name of the user that made the reservation.

	//bool operator<(const Reservation & r) const;
};