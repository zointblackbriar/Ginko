/* 
 * File:   main.cpp
 * Author: user
 *
 * Created on March 11, 2013, 3:57 PM
 */

/* standard c++ headers*/
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <sstream>

/* MySQL Connector headers */

#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "ginko.h"

int main() {
	
	sql::Driver *driver;
	sql::Connection *con;
	std::cout << "Hello\n";
	bool connected, endit;
	int i;
	std::string host, user, password, database, createdAddressv4, createdAddressv6;
	
	std::cout << "Pleaser enter the credentials for the database connection\n"
					<< "[Enter] selects default-values in [].\n";
	std::cout << "Host [" << DBHOST << "] : ";

	std::getline(std::cin, host);
	if(!host.empty()) {
		std::cout << "      ok \n";
	} else {
		std::cout << "      default \n";
		host = DBHOST;
	}
	
	std::cout << "user [" << USER << "] : ";

	std::getline(std::cin, user);
	if(!user.empty()) {
		std::cout << "      ok \n";
	} else {
		std::cout << "      default \n";
		user = USER;
	}

	std::cout << "Password [ ***** ] : ";

	password = getpass();
	if(!password.empty()) {
		std::cout << "      ok \n";
	} else {
		std::cout << "      default \n";
		password = PASSWORD;
	}

try {
		driver = get_driver_instance();
		con = driver->connect(host, user, password);
		std::cout << "Connected to " << host << " with user: " << user << "\n" ;
		connected = 1;
	} catch(sql::SQLException &e) {
		std::cout << "Connect error!\n";
		sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
		connected = 0;
	}		

	if(connected) {	
		endit = 0;
		while(!endit) {
			i = 0;	

			std::cout << "Connect to database: \n"
						<< "1: test\n"
						<< "2: appdb\n"
						<< "3: generate random ipv4 address\n"
						<< "4: generate random ipv6 adress\n" 
						<< "9: Exit" << std::endl;
						
			i = getIntinp();
			
			switch(i) {
				case 1: database = "test"; endit = 1; break;
				case 2: database = "appdb"; endit = 1; break;
				case 3: genipv4(createdAddressv4); std::cout << "Generated IPv4 Address: " << createdAddressv4 << std::endl ;break;
				case 4: genipv6(createdAddressv6); std::cout << "Generated IPv6 Address: " << createdAddressv6 << std::endl ;break;
				case 9: std::cout << "Goodbye\n"; exit(0);
				default: ;
			}	
		}
		choice(con, database);
		delete con;			
		
	} else {
		std::cout << "Error while connecting\n";
	}
}

