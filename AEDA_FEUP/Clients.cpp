#include "Clients.h"

Clients::Clients(){}

Users::Users(string username, string password, long nif,  int points){

	this->username = username;
	this->password = password;
	this->nif = nif;
	this->points = points;

}

Users::Users()
{
	username = ""; password = "";/*!< "username" is the username of the User and "password" is the password of the account of the User*/
	points = 0; nif = 0;/*!< "points" is a variable that has the number of points that the Client has and it increments as he makes reservations. "nif" is the numero de identificacao fiscal of the Client*/
}

void Users::orderReservations()
{
	for (int j = 0; j < reserVec.size() - 1; j++)
	{
		for (int i = 0; i < reserVec.size() - 1; i++)
		{
			Reservation r1 = reserVec[i];
			Reservation r2 = reserVec[i + 1];

			if (r1.getDate1() < r2.getDate1())
				continue;
			else
			{
				reserVec[i] = r2;
				reserVec[i + 1] = r1;
			}
		}
	}
}


bool Users::operator<(const Users &u1) const
{
	return (getUsername() < u1.getUsername());
}

string Users::getUsername()const { return username; }

string Users::getPassword() { return password; }

int Users::getPoints() { return points; }

long Users::getNif() const{ return nif; }

bool operator==(const Users &u1,const Users &s2) {

	if (u1.nif == s2.nif && u1.password == s2.password && u1.points == s2.points && u1.username == s2.username)
		return true;
	else
		return false;
}


