/* 
 * File: db_test
 * user: manns
 * 
 * This file contains some tiny functions related to the mysql test table.
 * It's merely proof of concept stuff.
 * 
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
 * Local Defines
 */

#define SELECTALL "SELECT * from testvalues"
#define SELECTTSTVAL "SELECT by Testvalues"

#define ID "id"
#define ADDR "address"
#define LAT "latitude"
#define LON "longitude"
#define ALT "altitude"
#define TSTA "testvalue_a"
#define TSTB "testvalue_b"
#define TSTC "testvalue_c"
#define TSTD "testvalue_d"

/*
 * Routine to show all results with the same formatting.
 */

void showresults(sql::ResultSet *res) {
	if (res->rowsCount()) {
		std::cout << ID << "\t" <<
						ADDR << "\t\t" <<
						LAT << "\t" <<
						LON << "\t" <<
						ALT << "\t" <<
						TSTA << "\t" <<
						TSTB << "\t" <<
						TSTC << "\t" <<
						TSTD << std::endl;
		while (res->next()) {
			std::cout << res->getString(ID) << "\t" <<
							res->getString(ADDR) << "\t\t" <<
							res->getString(LAT) << "\t\t" <<
							res->getString(LON) << "\t" <<
							res->getString(ALT) << "\t\t" <<
							res->getString(TSTA) << "\t\t" <<
							res->getString(TSTB) << "\t\t" <<
							res->getString(TSTC) << "\t\t" <<
							res->getString(TSTD) << "\t\t" <<
							std::endl;
		}
	}	else {
		std::cout << "No result found\n" ;
	}
}

/*
 * Show the full DATABASE from the given connection
 */

void showfulldb(sql::Connection *con, std::string database) {
	sql::Statement *stmt;
	sql::ResultSet *res;

	try {
		std::cout << SELECTALL << "\n";
		con->setSchema(database);
		stmt = con->createStatement();
		res = stmt->executeQuery(SELECTALL);
		showresults(res);
	} catch(sql::SQLException& e) {
		std::cout << "Select error!\n";
		sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
	}		
	delete res;
	delete stmt;
}

/*
 * Routine to selective assemble a SQL-select statement in dependency of given
 * parameters. It's a bit ugly for building the statement, but it can't be helped...
 * 
 */


void selectbytstvalues(sql::Connection *con, int tsta, int tstb, int tstc, int tstd, std::string database) {
	sql::Statement *stmt;
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	
	std::string ststa, ststb, ststc, ststd, selst, sand, sgle, restr;
	bool btsta, btstb, btstc, btstd = 0;
	
	selst = "select * from testvalues where ";
	restr = "";
	sgle = " = ";
	sand = " and ";
	
	if (tsta > 0) {
		ststa = convertfromInt(tsta);
		ststa = TSTA + sgle + ststa;
		btsta = 1;
	} else {btsta = 0;}
	if (tstb > 0) {
		ststb = convertfromInt(tstb);
		ststb = TSTB + sgle + ststb;
		btstb = 1;
	} else {btstb = 0;}
	if (tstc > 0) {
		ststc = convertfromInt(tstc);
		ststc = TSTC + sgle + ststc;
		btstc = 1;
	} else {btstc = 0;}
	if (tstd > 0) {
		ststd = convertfromInt(tstd);
		ststd = TSTD + sgle + ststd;
		btstd = 1;
	} else {btstd = 0;}	
	
	if (btsta && (!btstb && !btstc && !btstd)) { // A
		restr = selst + ststa;
	} else	if (btsta && btstb && btstc && btstd) { //ABCD
		restr = selst + ststa + sand + ststb + sand + ststc + sand + ststd;
	} else	if (btsta && btstb && btstc && !btstd) { // ABC
		restr = selst + ststa + sand + ststb + sand + ststc;
	} else 	if (btsta && btstb && !btstc && btstd) { //ABD
		restr = selst + ststa + sand + ststb + sand + ststd;
	} else 	if (btsta && btstb && !btstc && !btstd) { // AB
		restr = selst + ststa + sand + ststb;
	} else 	if (btsta && !btstb && btstc && btstd) { //ACD
		restr = selst + ststa + sand + ststc + sand + ststd;
	} else 	if (btsta && !btstb && btstc && !btstd) { // AC
		restr = selst + ststa + sand + ststc;
	} else 	if (btsta && !btstb && !btstc && btstd) { //AD
		restr = selst + ststa + sand + ststd;
	} else 	 	if (!btsta && btstb && btstc && btstd) { // BCD
		restr = selst + ststb + sand + ststc + sand + ststd;
	} else 	if (!btsta && btstb && btstc && !btstd) { // BC
		restr = selst + ststb + sand + ststc;
	}	else  if (!btsta && btstb && !btstc && btstd) { //BD
		restr = selst + ststb + sand + ststd;
	} else if (!btsta && btstb && !btstc && !btstd) { //B
		restr = selst + ststb;
	} else 	if (!btsta && !btstb && btstc && btstd) { //CD
		restr = selst + ststc + sand + ststd;
	} else 	if (!btsta && !btstb && btstc && !btstd) { //C
		restr = selst + ststc;
	} else 	if (!btsta && !btstb && !btstc && btstd) { //D
		restr = selst + ststd;
	}	else if (!btsta && !btstb && !btstc && !btstd) {
		std::cout << "Nothing to find\n";
		restr = "";
	}
	
	if (restr.size()) {
		try {
			std::cout << "Abfrage: " << restr << std::endl;
			con->setSchema(database);
			stmt = con->createStatement();		
			res = stmt->executeQuery(restr);
			showresults(res);
		} catch(sql::SQLException& e) {
			std::cout << "Select error!\n";
			sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
		}
	
	delete res;
	delete stmt;
	}
}

void iteratetstvalues(sql::Connection *con, std::string database) {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 4; l++) {
					std::cout << "\n===================\n";
					std::cout << "a: " << i;
					std::cout << " b: " << j;
					std::cout << " c: " << k;
					std::cout << " d: " << l << std::endl;
					selectbytstvalues(con, i,j,k,l, database);
				}
			}			
		}
	}
}

void testdb_choice(sql::Connection *con, std::string database) {

	bool endit = 0;
	
	while(!endit) {
		int i = 0;

		std::cout << "======================== \n"
						<< "What do you want do ? \n"
						<< "1: Show the full database?\n"
						<< "2: iterate through the testvalues?\n"
						<< "3: do both!\n"
						<< "anything else: Goodbye\n";
						
			i = getIntinp();

		switch(i) {
			case 1: showfulldb(con, database); break;
			case 2: iteratetstvalues(con, database); break;
			case 3: showfulldb(con, database);
							iteratetstvalues(con, database); break;
			default: std::cout << "Goodbye\n"; endit = 1;
		}	
	}
}