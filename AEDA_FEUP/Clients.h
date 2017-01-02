#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Rent.h"



using namespace std;

/*! \brief Brief description.
*
* Class of clients
*/
class Clients
{
public:
	Clients();

};

/*! \brief Brief description.
*
*Class of the users.Users can make reservations
*/
class Users : public Clients {

protected:
	string username, password;/*!< "username" is the username of the User and "password" is the password of the account of the User*/
	int points, nif;/*!< "points" is a variable that has the number of points that the Client has and it increments as he makes reservations. "nif" is the numero de identificacao fiscal of the Client*/
	vector<Reservation> reserVec;
public:
	Users();
	Users(string username, string password, long nif, int points);
	string getUsername()const;//!< a function that returns the username.
	string getPassword();//!< a function that returns the password.
	int getPoints();//!< a function that returns the points.
	long getNif()const ;//!< a function that returns the nif.
	friend bool operator==(const Users &u1, const Users &s2);//!< a function that returns true if the users are the same,else returns false
	bool operator<(const Users &u1) const;//!< a function that returns true if the users username is alphabetic bigger
	bool checkExistance(string username, string password);//!< a function that checks existance
	void orderReservations();//!< a function that puts the reservation vector in order
	vector<Reservation> getReservation() { return reserVec; }//!< a function that returns a vector that contains the user's reservation
	void addReservation(Reservation &r1) { reserVec.push_back(r1); }//!< a function that adds a reservation to the vector of reservations
};


