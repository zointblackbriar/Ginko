/*
 * file: mysql_helper_routines
 * author: manns
 * 
 * This File contains frequently used mysql routines.
 *  
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

/*
 * Errornotifier is used to catch SQLException Errors and to trace them back.
 */

void sqlerrornotifier(std::string File, std::string Function, int Line, std::string what, int ec, std::string state) {
	std::cout << "# ERR: SQLException in " << File;
	std::cout << "(" << Function << ") on line " << Line << std::endl;
	std::cout << "# ERR: " << what;
	std::cout << " (MySQL error code: " << ec;
	std::cout << ", SQLState: " << state << " )" << std::endl;	
}

void choice(sql::Connection *con, std::string database) {

	if (database == "test") {
	//	testdb_choice(con, database);
	} else if (database == "appdb") {
		appdb_choice(con, database);
	}
}