#include "Date.h"

using namespace std;


/*! \brief Brief description.
*
*  Class dedicated to the reservations that the users do.
*/
class Reservation {
private:
	Date d1, d2;/*!< date of the check-in and date of the check-out */
	long nif;/*!< nif of the user */
	double price;/*!< total price of the reservation */
public:
	Reservation(long nif,double price, Date d1, Date d2);
	Date getDate1() const {return d1;}//!< a function that returns the date of the check-in.
	Date getDate2() const { return d2;}//!< a function that returns the date of the check-out.
	double getPrice() const { return price; }//!< a function that returns the price.
	long getnif() const { return nif; }//!< a function that returns the city where they will stay.
};