/* 9
 * F2i65le: helper_routines
 * Author: manns
 * 
 * This file collects all the little helper routines,
 * which might become handy when used plenty.
 *  
 */

/* standard c++ headers*/
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <math.h>

#include <cstdlib>
#include <string>
#include <sstream>
#include <ctime>
#include <fstream>
#include <time.h>

#include "ginko.h"

/*
 * Little helper routine to convert any given integer to a string.
 * This is needed for certain arguments to be put into SQL-Statemnts.
 * www.cplusplus.com/forum/articles/9645
 */

std::string convertfromInt(int number) {
	std::stringstream ss; // create stringstream
	ss << number; //add number to the stream
	return ss.str(); // return string with conent of stream
}

std::string FloatToString(float number) {
	std::stringstream ss; // create stringstream
	ss << number; //add number to the stream
	return ss.str(); // return string with conent of stream
}

float stringtofloat(std::string tofloat) {
	char* stop = 0;
	float returnfloat;
	
	returnfloat = strtod(tofloat.c_str(), &stop);
	return returnfloat;
}

float calc_gps_distance(float lat1, float lon1, float lat2, float lon2) {
	float dlong = (lon2 - lon1)*PI/180;
	float dlat = (lat2 - lat1)*PI/180;
	float R = 6371;
	float step1, step2, distance;
	
	// Haversine Formula
	// http://stackoverflow.com/questions/15890081/calculate-distance-in-x-y-between-two-gps-points
	
	step1 = sin(dlat/2)*sin(dlat/2) + cos(lat1)*cos(lat2) * sin(dlong/2)*sin(dlong/2);
	step2 = 2 * atan2( sqrt(step1), sqrt(1-step1));
	distance = R * step2;
	
	return distance;
}

/*
 * Makes sure, that only Integer-Values are returned.
 */

int getIntinp() {
	char i;
	bool j = 0;
	int k;
	
	while(!j) {
		std::cout << "Your Input (int): ";
		std::cin >> i;
		std::cout << std::endl;

		if(isdigit(i)){
			k = i - '0';
			std::cin.sync();
			return k;
		} else {
			std::cout << "Wrong Input, try again!\n";
		}
	}
	
	
}

/*
 * Borrowed from a cplusplus.com article
 * www.cplusplus.com/articles/E6vU7k9E/
 */

int getch() {
	int ch;
	struct termios t_old, t_new;
	
	tcgetattr(STDIN_FILENO, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
	
	ch = getchar();
	
	tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
	return ch;
}

/*
 * Borrowed from a cplusplus.com article
 * www.cplusplus.com/articles/E6vU7k9E/
 */

std::string getpass() {
	
	std::string password;
	unsigned char ch=0;
	
	while ((ch=getch()) != RETURN )
	{
		if (ch == BACKSPACE) 
		{
			if(password.length() >= 0)
			{
				std::cout << "\b \b";
				password.resize(password.length()-1);
			}
		}
		else
		{
			password+=ch;
			std::cout << '*';
		}
	}
	std::cout << std::endl;
	return password;
}

std::string getstringinput() {
	std::cin.clear();
	
	std::string stringinput;
	unsigned char ch=0;
	
	while ((ch=getch()) != RETURN )
	{
		if (ch == BACKSPACE) 
		{
			if(stringinput.length() >= 0)
			{
				std::cout << "\b \b";
				stringinput.resize(stringinput.length()-1);
			}
		}
		else
		{
			stringinput+=ch;
			std::cout << ch;
		}
	}
	std::cout << std::endl;
	std::cin.sync();
	return stringinput;
}	


void genipv4(std::string& createdAddress) {
	
	sleep(0.1); // wait 0.1 s to get a new time, so that the random
						// number generator gets guaranteed a new seed
	
	time_t t;
  time(&t);
  srand(t);
  std::stringstream myOutput;

	createdAddress = "";
	
	for(int i = 0; i < 3; i++)
		{
		myOutput <<  rand() % 256;
		myOutput <<  ".";
		};
	myOutput <<  rand() % 256;
	//myOutput << std::endl;

  createdAddress += myOutput.str();
}

void genipv6(std::string& createdAddress) {
  time_t t;
  time(&t);
  srand(t);
  std::stringstream myOutput;
	char adressspace[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	
	createdAddress = "";

	for(int i = 0; i <7; i++) {
		for(int j = 0; j < 4; j++)
			{
			myOutput <<  adressspace[rand() % 16];
			};
		myOutput <<  ":";
	}
	for(int j = 0; j < 4; j++)
		{
		myOutput <<  adressspace[rand() % 16];
		};
	//myOutput << std::endl;

  createdAddress += myOutput.str();	
}