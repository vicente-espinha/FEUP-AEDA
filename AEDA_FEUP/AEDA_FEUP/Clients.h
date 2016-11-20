#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>



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
	
public:
	Users(string username, string password, long nif, int points);
	string getUsername();//!< a function that returns the username.
	string getPassword();//!< a function that returns the password.
	int getPoints();//!< a function that returns the points.
	long getNif();//!< a function that returns the nif.
	bool checkExistance(string username, string password);//!< a function that checks existance
};


