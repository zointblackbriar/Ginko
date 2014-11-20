/* 
 * File:   ginko.h
 * Author: user
 *
 * Created on March 27, 2013, 1:14 PM
 */

#ifndef GINKO_H
#define	GINKO_H

/* standard c++ headers*/
#include <cstdlib>
#include <string>

/* MySQL Connector headers */

#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/resultset.h>

/* Own headers*/

#include "defines.h"

#endif	/* GINKO_H */

/* Helper Routines */

std::string convertfromInt(int number); // Convert an int to a string
std::string FloatToString(float number); // Convert a float to a string
float stringtofloat(std::string tofloat); // Convert a string to a float
float calc_gps_distance(float lat1, float lon1, float lat2, float lon2); // Calculate distance bw 2 gps coord. in km
int getch();	// gets one character without showing it
std::string getpass();  // shows *** in password entry
std::string getstringinput(); // get string input, handles backspace
int getIntinp();	// Makes sure, that input is an Integer
void genipv4(std::string& createdAddress); // create one random IPv4 Address
void genipv6(std::string& createdAddress); // create one random IPv6 Address

/* Generic SQL Helper routines */

void sqlerrornotifier(std::string File, std::string Function, int Line, std::string what, int ec, std::string state);
void choice(sql::Connection *con, std::string database);

/* Specific Routines for Database TEST*/

void testdb_choice(sql::Connection *con, std::string database);

/* Specific Routines for Database appdb*/

void appdb_choice(sql::Connection *con, std::string database);
