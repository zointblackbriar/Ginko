/* 
 * File:   db_appdb.cpp
 * Author: manns
 *
 * This file manages all stuff regarding the appdb.
 * 
 * Created on March 11, 2013, 3:57 PM
 * 
 * General TODO: rewrite the code to make the database a define
 * Check every entry for consistency!
 */

/* standard c++ headers*/
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <sstream>
#include <ctype.h>
#include <math.h>

/* MySQL Connector headers */

#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

/* Own stuff*/

#include "ginko.h"

/*
 * Local defines
 */

#define DB "appdb"

// Table siteloc
#define SL "siteloc"
#define SLID "ID_sl" // ID - Auto Increment
#define SLIP "ipaddr" // Reference to corresponding ID from ipaddr
#define SLLO "longitude" 
#define SLLA "latitude"
#define SLAL "altitude"
#define SLSN "sitename"
#define SLST "street"
#define SLPO "postal"
#define SLCT "city"

// Table plugtypes 
#define PT "plugtypes"
#define PTID "ID_pl" // ID - Auto Increment
#define PTNA "name" // Name of the Plug

// Table ipaddr
#define IP "ipaddr"
#define IPID "ID_ip" // ID - Auto Increment
#define IPV4 "v4" 
#define IPV6 "v6"

// Table freeplugs
#define FP "freeplugs"
#define FPID "ID_frpl" // ID - Auto Increment
#define FPSL "siteloc" // Reference to corresponding ID from siteloc
#define FPFR "free"
#define FPPT "plugtype" // Reference to corresponding ID from plugtypes

/*
 * Show the full DATABASE from the given connection
 */

void appdb_showfulldb(sql::Connection *con, std::string database) {
	/*
	 * Show the full formatted database
	 */
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::stringstream query;

	try {
		/*
		 * Display only the entries where
		 * Siteloc-ID is present in Freeplugs-Siteloc AND
		 * Plugtype-ID is present in Freeplugs-Plugtype AND
		 * IP-ID is present in Siteloc-IP 
		 */
		query << "SELECT * FROM " << SL << ", " << IP << ", " << FP << ", " << PT 
					<< " WHERE "
					<< SL << "." << SLID << " = " << FP << "." << FPSL
					<< " AND "
					<< FP << "." << FPPT << " = " << PT << "." << PTID
					<< " AND "
					<< SL << "." << SLIP << " = " << IP << "." << IPID;
		con->setSchema(database);
		stmt = con->createStatement();
		std::cout << "showfulldb: " << query.str() << std::endl;
		res = stmt->executeQuery(query.str());
		query.str("");
		
		if (res->rowsCount()) {
			std::cout << SLID << "\t" <<
							//SLIP << "\t" <<
							SLLO << "\t" <<
							SLLA << "\t" <<
							SLAL << "\t" <<
							SLSN << "\t\t\t" <<
							//SLST << "\t" <<
							//SLPO << "\t" <<
							SLCT << "\t\t" <<
							//IPID << "\t" <<
							IPV4 << "\t" <<
							//IPV6 << "\t" <<
							//FPID << "\t" <<
							//FPSL << "\t" <<
							FPFR << "\t" <<
							//FPPT << "\t" <<
							PTID << "\t" <<
							PTNA << "\t" <<
							std::endl;
			while (res->next()) {
				std::cout << res->getString(SLID) << "\t" <<
								//res->getString(SLIP) << "\t" <<
								res->getString(SLLO) << "\t\t" <<
								res->getString(SLLA) << "\t\t" <<
								res->getString(SLAL) << "\t\t" <<
								res->getString(SLSN) << "    \t" <<
								//res->getString(SLST) << "\t\t" <<
								//res->getString(SLPO) << "\t\t" <<
								res->getString(SLCT) << "    \t" <<
								//res->getString(IPID) << "\t" <<
								res->getString(IPV4) << "\t" <<
								//res->getString(IPV6) << "\t\t" <<
								//res->getString(FPID) << "\t" <<
								//res->getString(FPSL) << "\t" <<
								res->getString(FPFR) << "\t" <<
								//res->getString(FPPT) << "\t" <<
								res->getString(PTID) << "\t" <<
								res->getString(PTNA) << "\t" <<
								std::endl;
			}
		}
		delete res;
		delete stmt;		
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}		

}

/*
 * Show content of specific tables
 */

void appdb_showsiteloc(sql::Connection *con, std::string database) {
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::stringstream query;

	try {
		query << "SELECT * FROM " << SL;
		con->setSchema(database);
		stmt = con->createStatement();
		std::cout << "showsiteloc: " << query.str() << std::endl;
		res = stmt->executeQuery(query.str());
		query.str("");
		
		if (res->rowsCount()) {
			std::cout << SLID << "\t" <<
							SLIP << "\t" <<
							SLLO << "\t" <<
							SLLA << "\t" <<
							SLAL << "\t" <<
							SLSN << "\t\t\t" <<
							SLST << "\t\t\t\t" <<
							SLPO << "\t" <<
							SLCT << "\t\t" <<
							std::endl;
			while (res->next()) {
				std::cout << res->getString(SLID) << "\t" <<
								res->getString(SLIP) << "\t" <<
								res->getString(SLLO) << "\t\t" <<
								res->getString(SLLA) << "\t\t" <<
								res->getString(SLAL) << "\t\t" <<
								res->getString(SLSN) << "    \t" <<
								res->getString(SLST) << "    \t" <<
								res->getString(SLPO) << "\t\t" <<
								res->getString(SLCT) <<
								std::endl;
			}
		}
		delete res;
		delete stmt;
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}		
}

void appdb_showip(sql::Connection *con, std::string database) {
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::stringstream query;

	try {
		query << "SELECT * FROM " << IP;
		con->setSchema(database);
		stmt = con->createStatement();
		std::cout << "showip: " << query.str() << std::endl;
		res = stmt->executeQuery(query.str());
		query.str("");
		
		if (res->rowsCount()) {
			std::cout << IPID << "\t" <<
							IPV6 << "\t\t\t\t\t\t" <<
							IPV4 <<
							std::endl;
			while (res->next()) {
				std::cout << res->getString(IPID) << "\t" <<
								res->getString(IPV6) << "\t\t" <<
								res->getString(IPV4) <<
								std::endl;
			}
		}
		delete res;
		delete stmt;
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}			
}

void appdb_showpt(sql::Connection *con, std::string database) {
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::stringstream query;

	try {
		query << "SELECT * FROM " << PT;
		con->setSchema(database);
		stmt = con->createStatement();
		std::cout << "showpt: " << query.str() << std::endl;
		res = stmt->executeQuery(query.str());
		query.str("");
		
		if (res->rowsCount()) {
			std::cout << PTID << "\t" <<
							PTNA <<
							std::endl;
			while (res->next()) {
				std::cout << res->getString(PTID) << "\t" <<
								res->getString(PTNA) <<
								std::endl;
			}
		}
		delete res;
		delete stmt;
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}			
}

void appdb_showfp(sql::Connection *con, std::string database) {
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::stringstream query;

	try {
		query << "SELECT * FROM " << FP;
		con->setSchema(database);
		stmt = con->createStatement();
		std::cout << "showfp: " << query.str() << std::endl;
		res = stmt->executeQuery(query.str());
		query.str("");
		
		if (res->rowsCount()) {
			std::cout << FPID << "\t" <<
							FPSL << "\t" <<
							FPFR << "\t" <<
							FPPT <<
							std::endl;
			while (res->next()) {
				std::cout << res->getString(FPID) << "\t" <<
								res->getString(FPSL) << "\t" <<
								res->getString(FPFR) << "\t" <<
								res->getString(FPPT) <<
								std::endl;
			}
		}	
		delete res;
		delete stmt;
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}			
}

/*
 * Add Data to the specific tables
 */

void appdb_addsiteloc(sql::Connection *con, std::string database) {
	/*
	 * Enter Data for new site location
	 * TODO: rewrite, so that errors can be removed
	 */
	std::cin.clear();
	
	std::string sitename, street, postal, city, longitude, latitude, altitude, ip;
	std::stringstream query;
	bool getipid = 0;
	char j;
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	sitename = "";
	street = "";
	postal = "";
	city = "";
	longitude = "";
	latitude = "";
	altitude = "";
	ip = "";
	
	std::cout << "Enter Sitename: ";
	while (sitename == "") {
		std::getline(std::cin, sitename);
	}
	std::cout << "Enter Street: ";
	while (street == "") {
		std::getline(std::cin, street);
	}
	std::cout << "Enter Postal: ";
	while (postal == "") {
		std::getline(std::cin, postal);
	}
	std::cout << "Enter City: ";
	while (city == "") {
		std::getline(std::cin, city);
	}
	std::cout << "Enter latitude: ";
	while (latitude == "") {
		std::getline(std::cin, latitude);
	}
	std::cout << "Enter longitude: ";
	while (longitude == "") {
		std::getline(std::cin, longitude);
	}
	std::cout << "Enter altitude: ";
	while (altitude == "") {
		std::getline(std::cin, altitude);
	}
	std::cout << "Select ID from available free IP-Adress: \n";

	/*
	 * select * from ipaddr where ipaddr.ID_ip between 1 and (select max(ID_ip) from ipaddr) and ipaddr.ID_ip not in (select ipaddr from siteloc)
	 * 
	 * Find unused IP addresses and present them for selection.
	 */
	try {
		
		query << "SELECT * FROM "  << IP 
					<< "WHERE " 
					<< IP << "." IPID	<< "BETWEEN 1"
					<< " AND " 
					<< "(SELECT MAX(" << IPID << "FROM " << IP << ")"
					<< " AND " 
					<< IP << "." << IPID << " NOT IN (SELECT " << SLIP << " FROM " << SL << ")";

		con->setSchema(database);
		stmt = con->createStatement();
		std::cout << "addsiteloc: " << query.str() << std::endl;
		res = stmt->executeQuery(query.str());
		query.str("");
		
		if (res->rowsCount()) {
			std::cout << IPID << "\t" 
								<< IPV4 << "\t" 
								<< IPV6 << std::endl;
			while (res->next()) {
				std::cout << res->getString(IPID) << "\t" 
									<< res->getString(IPV4) << "\t" 
									<< res->getString(IPV6) << std::endl;
			}
		} else {
			std::cout << "No free IP Adresses found! Please add some.\n";
			return;
		}
	
		/*
		 * Check, wether the supplied IP ID is really unused
		 */
		
		while(!getipid) {
			std::getline(std::cin, ip);
			query << "SELECT * FROM " << SL 
						<< " WHERE " 
						<< SLIP << " = " << ip;
			std::cout << "addsiteloc: " << query << std::endl;
			res = stmt->executeQuery(query.str());
			query.str("");

			if (res->rowsCount()) {
				std::cout << "You selected an already used IP address. Try again\t" <<	std::endl;
			}	else {
				getipid = 0;
			}
		}
	
		std::cout << "Please review your additions:" << std::endl
						<< "Sitename: " << sitename << std::endl
						<< "Street: " << street << std::endl
						<< "Postal: " << postal << std::endl
						<< "City: " << city << std::endl
						<< "longitude: " << longitude << std::endl
						<< "latitude: " << latitude << std::endl
						<< "altitude: " << altitude << std::endl
						<< "ID IP: " << ip << std::endl;
		
		query << "INSERT INTO `" << DB << "`.`" << SL << "` " 
					<< "(`" << SLID << "`, `" << SLIP << "`, `" << SLLO << "`, `" << SLLA << "`, `" << SLAL << "`, `" << SLSN << "`, `" << SLST << "`, `" << SLPO << "`, `" << SLCT << "`) "
					<< "VALUES "
					<< "(NULL, '" << ip << "', '" << longitude << " ', '" << latitude << "', '" << altitude << "', '" << sitename << "', '" << street << "', '" << postal << "', '" << city << "')";
		std::cout << "addsiteloc: " << query << std::endl;
		res = stmt->executeQuery(query.str());
		query.str("");
		
		delete res;
		delete stmt;
	
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}
}

void appdb_addipautomatic(sql::Connection *con, std::string database) {
	/*
	 * Generates n automatic random valid IPv4 and IPv6 addresses
	 * to quickly fill the database with stuff. If an address is already
	 * present, a new one is generated.
	 * TODO: What to do, when the full amount of IPv4 is reached?
	 * (Most likely to not happen, but...)
	 */
	
	std::cin.clear();
	
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::stringstream query;
	int number;
	bool v4existence, v6existence;
	
	std::string createdAddressv4, createdAddressv6;
	
	std::cout << "How much IP-Addresses do you need?\n";
	number = getIntinp();

	con->setSchema(database);
	stmt = con->createStatement();

	for (int i = 0; i < number; i++) {
		v4existence = 0;
		v6existence = 0;
		
		try {
			while(!v4existence) {
				createdAddressv4 = "";
				genipv4(createdAddressv4);
				
				query << "SELECT * FROM " << IP 
							<< " WHERE "
							<< IPV4 " = '" << createdAddressv4 << "'";

				res = stmt->executeQuery(query.str());
				query.str("");
			
				if (!res->rowsCount()) {
					if (VERBOSE)
						std::cout << "Generated IPv4 Address: " << createdAddressv4 << std::endl;
					v4existence = 1;
				} 
			}

			while(!v6existence) {
				createdAddressv6 = "";
				genipv6(createdAddressv6);
				
				query << "SELECT * FROM " << IP
							<< " WHERE "
							<< IPV6 " = '" << createdAddressv6 << "'";

				res = stmt->executeQuery(query.str());
				query.str("");
			
				if (!res->rowsCount()) {
					if (VERBOSE)
						std::cout << "Generated IPv6 Address: " << createdAddressv6 << std::endl;
					v6existence = 1;
				} 
			}
			
			query << "INSERT INTO `" << DB << "`.`" << IP "` "
						<< "(`" << IPID << "`, `" << IPV4 << "`, `" << IPV6 "`) " 	
						<< "VALUES (NULL, '" << createdAddressv4 << "', '" << createdAddressv6 << "')";
			std::cout << "addipautomatic: " << query.str() << std::endl;
			res = stmt->executeQuery(query.str());		
			query.str("");

			delete res;
			delete stmt;			
		} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
		}			
	}	
}

void appdb_addipmanually(sql::Connection *con, std::string database) {
	/*
	 * Enter a valid IPv4 and IPv6 address to quickly fill the database
	 * with stuff. If an address is already present, a new must be entered.
	 * TODO: What to do, when the full amount of IPv4 is reached?
	 * (Most likely to not happen, but...)
	 */	
	std::cin.clear();
	
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::stringstream query; 
	std::string ipv4, ipv6;

	bool valid = 0;
	bool v4existence, v6existence;
	
	v4existence = 0;
	v6existence = 0;
	ipv4 = ipv6 = "";

	try {
		con->setSchema(database);
		stmt = con->createStatement();		

		while(!v4existence) {
			std::cout << "Enter IPv4 Address (0, if none): " << std::endl;
			while (ipv4 == "") {
				std::cin >> ipv4;
			}
			if (ipv4 == "0") {
				ipv4 = "NULL";
				v4existence = 1; // ipv4 adresi artik yok.
			} else {
				query << "SELECT * FROM " << IP 
							<< " WHERE "
							<< IPV4 " = '" << ipv4 << "'";
				std::cout << "addipmanually: " << query.str() << std::endl;
				res = stmt->executeQuery(query.str());
				query.str("");

				if (res->rowsCount()) {
					std::cout << "IP-Address already in use, Enter new one" << std::endl;
				} else {
					v4existence = 1;
				}
			} 
		} 

		while(!v6existence) {
			std::cout << "Enter IPv6 Address (0, if none): " << std::endl;
			while (ipv6 == "") {
				std::cin >> ipv6;
			}
			
			if (ipv6 == "0") {
				ipv6 = "NULL";
				v6existence = 1;
			} else {
				query << "SELECT * FROM " << IP 
							<< " WHERE "
							<< IPV6 " = '" << ipv6 << "'";
				std::cout << "addipmanually: " << query.str() << std::endl;
				res = stmt->executeQuery(query.str());
				query.str("");

				if (res->rowsCount()) {
					std::cout << "IP-Address already in use, Enter new one\n";
				} else {
					v6existence = 1;
				}
			}
		}

		if(ipv4 == ipv6){
			std::cout << "Why are you here then?" << std::endl;
		} else {
			query << "INSERT INTO `" << DB << "`.`" << IP "` "
						<< "(`" << IPID << "`, `" << IPV4 << "`, `" << IPV6 "`) " 	
						<< "VALUES (NULL, '" << ipv4 << "', '" << ipv6 << "')";
			std::cout << "addipmanually: " << query.str() << std::endl;
			res = stmt->executeQuery(query.str());		
			query.str("");
		}
		delete res;
		delete stmt;	
	} catch(sql::SQLException& e) {
		if(e.getErrorCode() != 0) {
			sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
		}
	}			
}

void appdb_addnewpt(sql::Connection *con, std::string database) {
	/*
	 * Quickly add new Plugtypes.
	 * TODO: Improve handling of the Plugname input, because of an \n
	 */
	std::cin.clear();
	std::cin.sync();
	
	std::string plugname;
	std::stringstream query;
	bool plugexistence = 0;
	
	sql::Statement *stmt;
	sql::ResultSet *res;
	plugname = "";
	
	try {
		con->setSchema(database);
		stmt = con->createStatement();	
	
		while(!plugexistence) {
			std::cout << "Enter Plugname: ";
			while (plugname == "") {
				std::getline(std::cin, plugname);
			}
			
			query << "SELECT * FROM " << PT 
						<< " WHERE "
						<< PT << "." << PTNA << " = '" << plugname << "'";
			std::cout << "addnewpt: " << query.str() << std::endl;			
			res = stmt->executeQuery(query.str());
			query.str("");

			if (res->rowsCount()) {
				std::cout << "Plugname already in use, try again" << std::endl;
			} else {
				query << "INSERT INTO `" << DB << "`.`" << PT 
							<< "` (`" << PTID << "`, `" << PTNA << "`) " 
							<< "VALUES (NULL, '" << plugname << "')";
				std::cout << "addnewpt: " << query.str() << std::endl;			
				res = stmt->executeQuery(query.str());
				query.str("");
				plugexistence = 1;
			}			
		}
		delete res;
		delete stmt;		
		
	} catch(sql::SQLException& e) {
		if(e.getErrorCode() != 0) {
			sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
		}
	}
}

void appdb_addfp(sql::Connection *con, std::string database) {
	/*
	 * Choose site ID, Choose Plug ID, Enter amount of free Plugs
	 * TODO: repeat for chosen site, until no more plugtypes are available
	 */
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	std::string id, plugid, siteloc, free, plugtype;
	std::stringstream query;
	bool getsiteloc = 0;
	bool getplugid = 0;
	bool abort = 0;
	bool exiting = 0;
	bool leaving = 0;
	bool enterfree = 0;
	bool wrongplug = 0;

	try {
		while(!getsiteloc && !abort){
			id = "";
			std::cout << "Select ID of the site (0 to abort) \n";
			
			appdb_showsiteloc(con, database);
						
			std::cout << "Enter ID: ";
			
			while ((id == "")) {
				std::getline(std::cin, id);
				if (id == "0") {
					std::cout << "Exiting...\n";
					abort = 1;
				} 
				if (id == "") {

				}	else {
					//SELECT * FROM  `siteloc` WHERE ID_sl =1
					query << "SELECT * FROM `" << SL 
								<< "` WHERE " 
								<< SLID << "=" << id;
					
					con->setSchema(database);
					stmt = con->createStatement();
					std::cout << "addfreeplugs: " << query.str() << std::endl;
					res = stmt->executeQuery(query.str());
					query.str("");
					
					if (res->rowsCount()) {
						getsiteloc = 1;
					}	else {
						std::cout << "No such ID found!\n";
					}
				}
			}
		}

		if(!abort) {
			while(!wrongplug) {
				while(!getplugid && !exiting){
					plugtype = "";
					std::cout << "Select ID of the plug (0 to exit) \n";

					appdb_showpt(con, database);

					std::cout << "Enter ID: ";

					while ((plugtype == "")) {
						std::getline(std::cin, plugtype);
						if (plugtype == "0") {
							std::cout << "Exiting...\n";
							exiting = 1;
						} 
						if (plugtype == "") {

						}	else {
							//SELECT * FROM  `siteloc` WHERE ID_sl =1
							query << "SELECT * FROM  `" << PT 
										<< "` WHERE " 
										<< PTID << "=" << plugtype;
							std::cout << "addfreeplugs: " << query.str() << std::endl;
							res = stmt->executeQuery(query.str());
							query.str("");
							
							if (res->rowsCount()) {
								getplugid = 1;
							}	else {
								std::cout << "No such ID found!\n";
							}
						}
					}
				}
				query << "SELECT * FROM `" << FP 
							<< "` WHERE " 
							<< FPSL << " = " << id 
							<< " AND " 
							<< FPPT << " = " << plugtype;
				std::cout << "addfreeplugs" << query.str() << std::endl;
				res = stmt->executeQuery(query.str());
				query.str("");
				
				if (res->rowsCount()) {
					std::cout << "This Plug ist already present!\n";
				}	else {
					wrongplug = 1;
				}				
			}

			while(!enterfree && !leaving){
				free = "";
				std::cout << "Enter amount of free slots (0 to exit): ";

				while ((free == "")) {
					std::getline(std::cin, free);
					if (free == "0") {
						std::cout << "Exiting...\n";
						leaving = 1;
					} 
					if (free == "" && !leaving) {

					}	else {
			 // INSERT INTO  `appdb`.`freeplugs` (`ID_frpl` ,`siteloc` ,`free` ,`plugtype`) 	VALUES (NULL ,  '7',  '10',  '13');
						query << "INSERT INTO  `" << DB << "`.`" << FP 
									<< "` (`" << FPID << "` ,`" << FPSL << "` ,`" << FPFR << "` ,`" << FPPT << "`)"
									<< " VALUES (NULL ,  '"<< id << "',  '" << free << "',  '" << plugtype << "')";
						std::cout << "addfreeplugs: " << query.str() << std::endl;
						res = stmt->executeQuery(query.str());
						enterfree = 1;
						}
					}
				}
				delete res;
				delete stmt;						
			}			
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}		
}

/*
 * Alter Data in the specific tables
 */

void appdb_altersiteloc(sql::Connection *con, std::string database) {
	std::cin.clear();
	
	std::string id,sitename, street, postal, city, dummy, longitude, latitude, altitude, ip, choice;
	std::string oldsitename, oldstreet, oldpostal, oldcity, oldlongitude, oldlatitude, oldaltitude, oldip;
	std::stringstream  query, idselect;
	bool getipid = 1;
	bool getid = 0;
	bool changesok = 0;
	bool exiting = 0;
	sql::Statement *stmt;
	sql::ResultSet *res;
	id = "";
	int i;

	/*UPDATE  `appdb`.`siteloc` SET  `ipaddr` =  '1',`longitude` =  '12.93833',
	`sitename` =  'Parkhaus Sachsen-Allee 3' WHERE  `siteloc`.`ID_sl` =1
	 * select * from ipaddr where ipaddr.ID_ip between 1 and (select max(ID_ip) from ipaddr) and ipaddr.ID_ip not in (select ipaddr from siteloc)
	 * 
	 * Find unused IP addresses and present them for selection.
	 */
	try {
		
		// Get the ID to change
		
		while(!getid && !exiting){
			std::cout << "Select ID of entry to change (0 to exit) \n";
			
			appdb_showsiteloc(con, database);
						
			std::cout << "Enter ID: ";
			
			while ((id == "")) {
				std::getline(std::cin, id);
				if (id == "0") {
					std::cout << "Exiting...\n";
					exiting = 1;
				} 
				if (id == "") {

				}	else {
					//SELECT * FROM  `siteloc` WHERE ID_sl =1
					query << "SELECT * FROM  `" << SL 
								<< "` WHERE " 
								<< SLID << "=" << id;
					con->setSchema(database);
					stmt = con->createStatement();
					res = stmt->executeQuery(query.str());
					query.str("");
					
					if (!(res->rowsCount())) {
						std::cout << "No such ID found!\n";
					}	else {
						res->next();
						oldsitename = res->getString(SLSN);// << ;
						oldstreet = res->getString(SLST);
						oldpostal = res->getString(SLPO);
						oldcity = res->getString(SLCT);
						oldlatitude = res->getString(SLLA);
						oldlongitude = res->getString(SLLO);
						oldaltitude = res->getString(SLAL);
						oldip = res->getString(SLIP);					
						
						idselect << "WHERE `" << SL << "`.`" << SLID << "` = " << id;
						getid = 1;

					}
				}
			}
		}

		if(!(exiting)) {			
			while(!changesok) {	
				std::cout << "Enter the values to change, ENTER skips the change:\n";

				std::cout << "Enter Sitename (old one: " << oldsitename<<  "): ";
				std::getline(std::cin, sitename);
				if (sitename == "")
					sitename = oldsitename;

				std::cout << "Enter Street: (old one: " << oldstreet <<  "): ";
				std::getline(std::cin, street);
				if (street == "")
					street = oldstreet;			

				std::cout << "Enter Postal: (old one: " << oldpostal <<  "): ";
				std::getline(std::cin, postal);
				if (postal == "")
					postal = oldpostal;

				std::cout << "Enter City: (old one: " << oldcity <<  "): ";
				std::getline(std::cin, city);
				if (city == "")
					city = oldcity;

				std::cout << "Enter latitude: (old one: " << oldlatitude <<  "): ";
				std::getline(std::cin, latitude);
				if (latitude == "")
					latitude = oldlatitude;

				std::cout << "Enter longitude: (old one: " << oldlongitude <<  "): ";
				std::getline(std::cin, longitude);
				if (longitude == "")
					longitude = oldlongitude;

				std::cout << "Enter altitude: (old one: " << oldip <<  "): ";
				std::getline(std::cin, altitude);
				if (altitude == "")
					altitude = oldaltitude;

				std::cout << "Select ID from available free IP-Adress: " << std::endl;

				query << "SELECT * FROM " << IP 
							<< "WHERE " 
							<< IP << "." IPID	<< "BETWEEN 1"
							<< " AND " 
							<< "(SELECT MAX(" << IPID << "FROM " << IP << ")"
							<< " AND " 
							<< IP << "." << IPID << " NOT IN (SELECT " << SLIP << " FROM " << SL << ")";				
				
				res = stmt->executeQuery(query.str());
				query.str("");
				
				if (res->rowsCount()) { // Alter the Data in the specific table 
					std::cout << IPID << "\t" <<
									IPV4 << "\t" <<
									IPV6 <<	std::endl;
					while (res->next()) {
						std::cout << res->getString(IPID) << "\t" <<
										res->getString(IPV4) << "\t" <<
										res->getString(IPV6) <<	std::endl;
					}
				} else {
					std::cout << "No free IP Adresses found! Please add some." << std::endl;
					return;
				} 

				/*
				 * Check, whether the supplied IP ID is really unused
				 */

				while(getipid) {
					query.str("");
					std::cout << "Enter ID: ";
					std::getline(std::cin, ip);
					if (ip == "") {
						ip = oldip;
						i = 0;
					} else {
						query << "select * from siteloc where ipaddr = " << ip;
						std::cout << "altersiteloc: " << query << std::endl;
						res = stmt->executeQuery(query.str());
						query.str("");

						if (res->rowsCount()) {
							std::cout << "You selected an already used IP address. Try again" << std::endl;
						}	else {
							getipid = 0;
						}					
					}
				} 

		/*
		 * Alter the Data in the specific table 
		 * UPDATE  `appdb`.`siteloc` SET  `ipaddr` =  '2' WHERE  `siteloc`.`ID_sl` =1;
		 * UPDATE  `appdb`.`siteloc` SET  `ipaddr` =  '1',`longitude` =  '12.93833',
		`sitename` =  'Parkhaus Sachsen-Allee 3' WHERE  `siteloc`.`ID_sl` =1;
		 */		
				std::cout << "Please review your changes:\n"
								<< "Sitename: " << sitename << "\n"
								<< "Street: " << street << "\n"
								<< "Postal: " << postal << "\n"
								<< "City: " << city << "\n"
								<< "longitude: " << longitude << "\n"
								<< "latitude: " << latitude << "\n"
								<< "altitude: " << altitude << "\n"
								<< "ID IP: " << ip << std::endl;
				std::cout << "Changes ok? Y/N ";
				std::getline(std::cin, choice);
				if ((choice == "y") || (choice == "Y")) {
					changesok = 1;
				}	
			}
			stmt = con->createStatement();
			query << "UPDATE  `" << DB << "`.`" << SL << "` SET  `" 
						<< SLIP <<"` = '" << ip << "',`"
						<< SLLO << "` = '" << longitude << "',`"
						<< SLLA << "` = '" << latitude << "',`"
						<< SLAL << "` = '" << altitude << "',`"
						<< SLSN << "` = '" << sitename << "',`"
						<< SLST << "` = '" << street << "',`"
						<< SLPO << "` = '" << postal << "',`"
						<< SLCT << "` = '" << city << "' " << idselect.str();
			std::cout << "altersiteloc: " << query.str() << std::endl;
			res = stmt->executeQuery(query.str());
			query.str("");
	
			delete res;
			delete stmt;	
		}			
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}	
}

void appdb_alterip(sql::Connection *con, std::string database) {

	std::cin.clear();
	
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::stringstream query, idselect; 
	std::string oldipv4, oldipv6, ipv4, ipv6, id;
	
	bool getid = 0;
	bool exiting = 0;
	bool v4existence = 0;
	bool v6existence = 0;

	try {
		while(!getid && !exiting){
			std::cout << "Select ID of entry to change (0 to exit) \n";

			appdb_showip(con, database);
		 			
			std::cout << "Enter ID: ";
			
			while ((id == "")) {
				std::getline(std::cin, id);
				if (id == "0") {
					std::cout << "Exiting...\n";
					exiting = 1;
				} 
				if (id == "") {

				}	else {
					//SELECT * FROM  `siteloc` WHERE ID_sl =1
					query << "SELECT * FROM  `" << IP 
								<< "` WHERE " 
								<< IPID << "=" << id;
					con->setSchema(database);
					stmt = con->createStatement();
					res = stmt->executeQuery(query.str());
		  		query.str("");
					if (!(res->rowsCount())) {
						std::cout << "No such ID found!\n";
					}	else {
						res->next();
						oldipv4 = res->getString(IPV4);
						oldipv6 = res->getString(IPV6);
						
						idselect << "WHERE `" << IP << "`.`" << IPID << "` = " << id;
						getid = 1;
					}
				}
			}
		}
		
		if (!exiting) {
			while(!v4existence) {
				std::cout << "Enter new IPv4 Address (0 to keep " << oldipv4 << "): \n";
				std::cin >> ipv4;

				if (ipv4 == "0") {
					ipv4 = oldipv4;
					v4existence = 1;
				} else {
					query.str("");
					query << "SELECT * FROM " << IP 
								<< " WHERE v4 = '" << ipv4 << "'";
					res = stmt->executeQuery(query.str());
	
					if (!res->rowsCount()) {
						if (VERBOSE)
							std::cout << "IPv4 Address: " << ipv4 << std::endl;
						v4existence = 1;
						query.str("");
					} else {
						std::cout << "IP-Address already in use, Enter new one\n";
					}
				} 
			} 			
			while(!v6existence) {
				std::cout << "Enter new IPv6 Address (0 to keep " << oldipv6 << "):\n";
				std::cin >> ipv6;

				if (ipv6 == "0") {
					ipv6 = oldipv6;
					v6existence = 1;
				} else {
					query.str("");
					query << "SELECT * FROM " << IP 
								<< " WHERE v6 = '" << ipv6 << "'";

					res = stmt->executeQuery(query.str());

					if (!res->rowsCount()) {
						if (VERBOSE)
							std::cout << "IPv6 Address: " << ipv6 << std::endl;
						v6existence = 1;
						query.str("");
					} else {
						std::cout << "IP-Address already in use, Enter new one\n";
					}
				}
			}		
			query.str("");
			query << "UPDATE `" << DB << "`.`" << IP << "` SET `"
						<< IPV4 << "` = `" << ipv4 << "',`"
						<< IPV6 << "` = `" << ipv6 << "' " << idselect.str(); 
			if (VERBOSE)
				std::cout << query.str() << std::endl;
			res = stmt->executeQuery(query.str());		

			delete res;
			delete stmt;			
		}
	} catch(sql::SQLException& e) {
		if(e.getErrorCode() != 0) {
			sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
		}
	}
}

void appdb_alterfp(sql::Connection *con, std::string database) {
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	std::string fpid, id, plugid, siteloc, free, plugtype;
	std::string oldsiteloc, oldfree, oldplugtype;
	std::stringstream query, idselect;
	bool getid = 0;
	bool getsiteloc = 0;
	bool getplugid = 0;
	bool enterfree = 0;
	bool wrongplug = 0;

	try {
		while(!getid) {
			fpid = "";
			std::cout << "Select ID to change: \n";
			appdb_showfp(con, database);
			std::cout << "Enter ID: ";
			
			while ((fpid == "")) {
				std::getline(std::cin, fpid);
				if (!(fpid == "")) {
					//SELECT * FROM  `siteloc` WHERE ID_sl =1
					query << "SELECT * FROM  `" << FP 
								<< "` WHERE " 
								<< FPID << "=" << fpid;
					con->setSchema(database);
					stmt = con->createStatement();
					std::cout << query.str() << std::endl;
					res = stmt->executeQuery(query.str());
					query.str("");
					if (!(res->rowsCount())) {
						std::cout << "No such ID found!\n";
					}	else {
						res->next();
						oldsiteloc = res->getString(FPSL);
						oldfree = res->getString(FPFR);
						oldplugtype = res->getString(FPPT);
						
						idselect << "WHERE `" << FP << "`.`" << FPID << "` = " << fpid;												
						getid = 1;
					}					
				}
			}
		}
		
		while(!getsiteloc){
			id = "";
			std::cout << "Enter new ID of the site (0 to keep) \n";
			
			appdb_showsiteloc(con, database);
						
			std::cout << "Enter ID: ";
			
			while ((id == "")) {
				std::getline(std::cin, id);
				if (id == "0") {
					id = oldsiteloc;
					getsiteloc = 1;
				} 
				if (id == "") {

				}	else {
					//SELECT * FROM  `siteloc` WHERE ID_sl =1
					query << "SELECT * FROM  `" << SL 
								<< "` WHERE " 
								<< SLID << "=" << id;
					std::cout << query.str() << std::endl;
					res = stmt->executeQuery(query.str());
					query.str("");
					if (!(res->rowsCount())) {
						std::cout << "No such ID found!\n";
					}	else {
						getsiteloc = 1;
					}
				}
			}
		}

		while(!wrongplug && !getplugid) {
			while(!getplugid){
				plugtype = "";
				std::cout << "Select ID of the plug (0 to keep) \n";

				appdb_showpt(con, database);

				std::cout << "Enter new ID: ";

				while ((plugtype == "")) {
					std::getline(std::cin, plugtype);
					if (plugtype == "0") {
						plugtype = oldplugtype;
						getplugid = 1;
					} 
					if (plugtype == "") {

					}	else {
						//SELECT * FROM  `siteloc` WHERE ID_sl =1
						query << "SELECT * FROM  `" << PT 
									<< "` WHERE " 
									<< PTID << "=" << plugtype;
						std::cout << query.str() << std::endl;
						res = stmt->executeQuery(query.str());
						query.str("");
						if (!(res->rowsCount())) {
							std::cout << "No such ID found!\n";
						}	else {
							getplugid = 1;
						}
					}
				}
			}
			if (!getplugid) {
				query << "SELECT * FROM `" << FP 
							<< "` WHERE " 
							<< FPSL << " = " << id 
							<< " AND " 
							<< FPPT << " = " << plugtype;
				std::cout << query.str() << std::endl;
				res = stmt->executeQuery(query.str());
				query.str("");
				if (res->rowsCount()) {
					std::cout << "This Plug ist already present!\n";
				}	else {
					wrongplug = 1;
				}					
			}		
		}

		while(!enterfree){
			free = "";
			std::cout << "Enter amount of free slots (0 to exit): ";

			while ((free == "")) {
				std::getline(std::cin, free);
				if (free == "0") {
					free = oldfree;
					enterfree = 1;
				} 
				if (free == "") {

				}	else {
		 // INSERT INTO  `appdb`.`freeplugs` (`ID_frpl` ,`siteloc` ,`free` ,`plugtype`) 	VALUES (NULL ,  '7',  '10',  '13');
					query << "UPDATE `" << DB << "`.`" << FP 
								<< "` SET `"
								<< FPFR << "` = '" << free << "',`"
								<< FPSL << "` = '" << id << "',`"
								<< FPPT << "` = '" << plugtype << "' " << idselect.str();					

					std::cout << query.str() << std::endl;
					res = stmt->executeQuery(query.str());
					enterfree = 1;
					}
				}
			}
			delete res;
			delete stmt;						
			
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}			
}

void appdb_alterpt(sql::Connection *con, std::string database) {
	std::cin.clear();
	std::cin.sync();
	
	std::string plugname, oldplugname, plugid;
	std::stringstream query, idselect;
	bool plugexistence = 0;
	bool bplugid = 0;
	
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	try {
		while(!bplugid) {
			plugid = "";
			std::cout << "Select ID to change: \n";
			appdb_showpt(con, database);
			std::cout << "Enter ID: ";
			
			while ((plugid == "")) {
				std::getline(std::cin, plugid);
				if (!(plugid == "")) {
					//SELECT * FROM  `siteloc` WHERE ID_sl =1
					query << "SELECT * FROM  `" << PT 
								<< "` WHERE " 
								<< PTID << "=" << plugid;
					con->setSchema(database);
					stmt = con->createStatement();
					std::cout << query.str() << std::endl;
					res = stmt->executeQuery(query.str());
					query.str("");
					if (!(res->rowsCount())) {
						std::cout << "No such ID found!\n";
					}	else {
						res->next();
						oldplugname = res->getString(PTNA);
						
						idselect << "WHERE `" << PT << "`.`" << PTID << "` = " << plugid;												
						bplugid = 1;
					}					
				}
			}
		}
		
		while(!plugexistence) {
			query.str("");
			plugname = "";
			std::cout << "Enter new Plugname (0 to keep, old one: " << oldplugname << "): ";
			
			while ((plugname == "")) {
				plugname = getstringinput();

				if (plugname == "0") {
					plugname = oldplugname;
					plugexistence = 1;
				}
				
				if (!(plugname == "" && !(plugname == "0"))) {
					//SELECT * FROM  `siteloc` WHERE ID_sl =1
					query << "SELECT * FROM  `" << PT 
								<< "` WHERE " 
								<< PTNA << "= '" << plugname << "'";

					std::cout << query.str() << std::endl;
					res = stmt->executeQuery(query.str());
					query.str("");
					if ((!res->rowsCount()) && !(plugname == "")) {
						if (VERBOSE)
							std::cout << "Plugname: " << plugname << std::endl;
						plugexistence = 1;
						query.str("");
					} else {
						if (plugname == "") {

						} else {
							std::cout << "Plugname already in use, try again\n";
						}
					}							
				}
			}			
		}
		query << "UPDATE `" << DB << "`.`" << PT 
					<< "` SET `"
					<< PTNA << "` = '" << plugname << "' " << idselect.str();

		if (VERBOSE)
			std::cout << query.str() << std::endl;
		res = stmt->executeQuery(query.str());
		
		delete res;
		delete stmt;		
		
	} catch(sql::SQLException& e) {
		if(e.getErrorCode() != 0) {
			sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
		}
	}	
}

/*
 * Delete specific Data in the table 
 */

void appdb_delfp(sql::Connection *con, std::string database, int callingfrom, std::string idtodel) {
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	std::string fpid, sure;
	std::stringstream query;
	bool getid = 0;

	try {
		con->setSchema(database);
		stmt = con->createStatement();
		switch(callingfrom) {
			case 1: // from deleting site
				query.str("");
				query << "DELETE FROM " << FP 
							<< "WHERE " 
							<< FPSL << " = " << idtodel;
				std::cout << query.str() << std::endl;
				res = stmt->executeQuery(query.str());
				query.str("");
				break;
			case 2: // from deleting site
				query.str("");
				query << "DELETE FROM " << FP 
							<< "WHERE " 
							<< FPPT << " = " << idtodel;
				std::cout << query.str() << std::endl;
				res = stmt->executeQuery(query.str());
				query.str("");
				break;
			default: 
				while(!getid) {
					fpid = "";
					sure = "";
					std::cout << "Select ID to delete: \n";
					appdb_showfp(con, database);
					std::cout << "Enter ID: ";

					while ((fpid == "")) {
						std::getline(std::cin, fpid);
						if (!(fpid == "")) {
							//SELECT * FROM  `siteloc` WHERE ID_sl =1
							query << "SELECT * FROM  `" << FP 
										<< "` WHERE " 
										<< FPID << "=" << fpid;
							con->setSchema(database);
							stmt = con->createStatement();
							std::cout << query.str() << std::endl;
							res = stmt->executeQuery(query.str());
							query.str("");
							if (!(res->rowsCount())) {
								std::cout << "No such ID found!\n";
							}	else {
								std::cout << "Are you really sure to delete this entry? (Y/N) :";
								while (sure == "") {
									std::getline(std::cin, sure);
									if ((sure == "Y") || (sure == "y") ) {
										query << "DELETE FROM " << FP 
													<< "WHERE " 
													<< FPID << " = " << fpid;
										res = stmt->executeQuery(query.str());
										query.str("");
										getid = 1;
									} 
								}
							}					
						}
					}
				}
		}
		delete res;
		delete stmt;								
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}			
}

void appdb_delsiteloc(sql::Connection *con, std::string database) {
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	std::string slid, sure;
	std::stringstream query;
	bool getid = 0;

	try {
		con->setSchema(database);
		stmt = con->createStatement();
		while(!getid) {
			slid = "";
			sure = "";
			std::cout << "Select ID to delete: \n";
			appdb_showsiteloc(con, database);
			std::cout << "Enter ID: ";

			while ((slid == "")) {
				std::getline(std::cin, slid);
				if (!(slid == "")) {
					//SELECT * FROM  `siteloc` WHERE ID_sl =1
					query << "SELECT * FROM  `" << SL 
								<< "` WHERE " 
								<< SLID << "=" << slid;
					std::cout << query.str() << std::endl;
					res = stmt->executeQuery(query.str());
					query.str("");
					if (!(res->rowsCount())) {
						std::cout << "No such ID found!\n";
					}	else {
						std::cout << "Are you really sure to delete this entry? (Y/N) :";
						while (sure == "") {
							std::getline(std::cin, sure);
							if ((sure == "Y") || (sure == "y") ) {
								std::cout << "Deleting associated Free Plugs as well\n";
								appdb_delfp(con, database, 1, slid);
								query << "DELETE from " << FP 
											<< "WHERE " 
											<< FPID << " = " << slid;
								res = stmt->executeQuery(query.str());
								query.str("");
								getid = 1;
							} 
						}
					}					
				}
			}
		}

		delete res;
		delete stmt;								
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}	
}


void appdb_delip(sql::Connection *con, std::string database) {
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	std::string ipid, newipid, sure;
	std::stringstream query;
	bool getid = 0;
	bool updateip = 0;

	try {
		con->setSchema(database);
		stmt = con->createStatement();
		while(!getid) {
			ipid = "";
			sure = "";
			std::cout << "Select ID to delete: \n";
			appdb_showip(con, database);
			std::cout << "Enter ID: ";

			while ((ipid == "")) {
				std::getline(std::cin, ipid);
				if (!(ipid == "")) {
					//SELECT * FROM  `siteloc` WHERE ID_sl =1
					query << "SELECT * FROM  `" << IP 
								<< "` WHERE " 
								<< IPID << "=" << ipid;
					std::cout << query.str() << std::endl;
					res = stmt->executeQuery(query.str());
					query.str("");
					if (!(res->rowsCount())) {
						std::cout << "No such ID found!\n";
					}	else {
						std::cout << "Are you really sure to delete this entry? (Y/N) :";
						while (sure == "") {
							std::getline(std::cin, sure);
							/*
							 * Now Check, if the ID to delete is used by a site. If so, ask for a new IP
							 * ID, so this field doesn't stay empty. Only when a new IP is chosen
							 * the selected IP ID will deleted.
							 */
							if ((sure == "Y") || (sure == "y") ) {
								std::cout << "Checking if this IP is used from a site... ";
								query << "SELECT * FROM " << SL 
											<< "WHERE " 
											<< SLIP << " = " << ipid;
								res = stmt->executeQuery(query.str());
								query.str("");
								if (res->rowsCount()) {
									std::cout << "done. Site found, renewing IP-Address" << std::endl;
									std::cout << "Please choose a new IP-Address for this site: \n";
									// Select all unused IP-Addresse
									query << "SELECT * FROM "  << IP 
												<< "WHERE " 
												<< IP << "." IPID	<< "BETWEEN 1 AND (SELECT MAX(" << IPID << "FROM " << IP << ")"
												<< " AND " 
												<< IP << "." << IPID << " NOT IN (SELECT " << SLIP << " FROM " << SL << ")";
									std::cout << query.str() << std::endl;
									res = stmt->executeQuery(query.str());
									query.str("");
									
									// Show, what we got
									if (res->rowsCount()) {
										std::cout << IPID << "\t" 
															<< IPV4 << "\t" 
															<< IPV6 << std::endl;
										while (res->next()) {
											std::cout << res->getString(IPID) << "\t" 
																<< res->getString(IPV4) << "\t" 
																<< res->getString(IPV6) << std::endl;
										}
										
										// Select ID (input), make sure it isn't used already (just in case)
										while(!(updateip)) {
											std::getline(std::cin, newipid);
											query << "SELECT * FROM " << SL 
														<< " WHERE " 
														<< SLIP << " = " << newipid;

											std::cout << query << std::endl;
											res = stmt->executeQuery(query.str());
											query.str("");

											if (res->rowsCount()) {
												std::cout << "You selected an already used IP address. Try again." <<	std::endl;
											}	else {
												updateip = 1;
												query << "UPDATE  `" << DB << "`.`" << SL 
															<< "` SET  `" 
															<< SLIP <<"` =  '" << newipid 
															<< "' WHERE " 
															<< SLIP << " = " << ipid;
												std::cout << query.str() << std::endl;
												res = stmt->executeQuery(query.str());
												query.str("");												
											}
										} // end while for updating sitelocation
									} else {
										std::cout << "No free IP Adresses found! Please add some.\n";
									}	// end if, checking for available IP-Addresses
								} else {
									std::cout << "done, none found, proceeding" << std::endl;
								} // end if, checking if the IP-Addres to delete is used by a site
	
								query << "DELETE from " << IP << "WHERE " << IPID << " = " << ipid;
								res = stmt->executeQuery(query.str());
								query.str("");
								getid = 1;
							}  
						} // end confirmation Y/N
					}					
				}
			}
		}

		delete res;
		delete stmt;								
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}	
}

void appdb_delpt(sql::Connection *con, std::string database) {
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	std::string ptid, sure;
	std::stringstream query;
	bool getid = 0;

	try {
		con->setSchema(database);
		stmt = con->createStatement();
		while(!getid) {
			ptid = "";
			sure = "";
			std::cout << "Select ID to delete: \n";
			appdb_showsiteloc(con, database);
			std::cout << "Enter ID: ";

			while ((ptid == "")) {
				std::getline(std::cin, ptid);
				if (!(ptid == "")) {
					//SELECT * FROM  `siteloc` WHERE ID_sl =1
					query << "SELECT * FROM  `" << PT 
								<< "` WHERE " 
								<< PTID << "=" << ptid;
					std::cout << query.str() << std::endl;
					res = stmt->executeQuery(query.str());
					query.str("");
					
					if (!(res->rowsCount())) {
						std::cout << "No such ID found!\n";
					}	else {
						std::cout << "Are you really sure to delete this entry? (Y/N) :";
						while (sure == "") {
							std::getline(std::cin, sure);
							if ((sure == "Y") || (sure == "y") ) {
								std::cout << "Deleting associated Free Plugs as well\n";
								appdb_delfp(con, database, 1, ptid);
								query << "DELETE FROM " << PT 
											<< "WHERE " 
											<< PTID << " = " << ptid;
								res = stmt->executeQuery(query.str());
								query.str("");
								getid = 1;
							} 
						}
					}					
				}
			}
		}
		delete res;
		delete stmt;								
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}	
} 

/*
 * Get the neares GPS coordinates out of the db, based on latitude and longitude
 */

void appdb_getsitebygps(sql::Connection *con, std::string database) {
	std::cin.clear();
	sql::Statement *stmt;
	sql::ResultSet *res;

	std::string str_longitude, str_latitude;
	float fl_longitude, fl_latitude, fl_lo_min, fl_lo_max, fl_la_min, fl_la_max, fl_dif_lat, fl_dif_lon, fl_dist;
	float Radius = 6378; // Sphere of Earth in m
	float distance = 300; // Radius, to limit search, 100 ~ 3.5km
	float min_dist = 6400;
	bool long_ok = 0;
	bool lat_ok = 0;		
	std::string res_siteid, res_minsiteid, res_sitename, res_ipv4, res_tmp, res_street, res_city, res_lo, res_la;
	std::stringstream query;
	
	str_longitude = "";
	str_latitude = "";

	fl_dif_lat = distance / Radius;
		
	while (!lat_ok) {
		std::cout << "Enter latitude: ";
		while (str_latitude == "") {
			std::getline(std::cin, str_latitude);
		}
		fl_latitude = stringtofloat(str_latitude);
		if ((fl_latitude <= 90) && (fl_latitude >= -90)) {
			lat_ok = 1;
			fl_la_min = fl_latitude - fl_dif_lat;
			fl_la_max = fl_latitude + fl_dif_lat;
		} else {
			std::cout << "Error, wrong value for latitude, try again." << std::endl;
			str_latitude = "";
		}
	}
	
	fl_dif_lon = distance / (Radius * cos (PI * fl_latitude / 180));
	
	while (!long_ok) {
		std::cout << "Enter longitude: ";
		while (str_longitude == "") {
			std::getline(std::cin, str_longitude);
		}
		fl_longitude = stringtofloat(str_longitude);
		if ((fl_longitude <= 180) && (fl_longitude >= -180)) {
			long_ok = 1;
			fl_lo_min = fl_longitude - fl_dif_lon;
			fl_lo_max = fl_longitude + fl_dif_lon;			
		} else {
			std::cout << "Error, wrong value for latitude, try again." << std::endl;
			str_longitude = "";
		}		
	}

	std::cout << "latitude min / max: " << fl_la_min << " / " << fl_la_max << std::endl;
	std::cout << "longitude min / max: " << fl_lo_min << " / " << fl_lo_max << std::endl;
	
	try {
		con->setSchema(database);
		stmt = con->createStatement();
	
		/*<
		 * select * from siteloc, ipaddr, freeplugs, plugtypes 
		 * where 
		 * siteloc.ipaddr = ipaddr.ID 
		 * and 
		 * siteloc.ID = freeplugs.siteloc 
		 * and 
		 * freeplugs.plugtype = plugtypes.ID 
		 * and 
		 * freeplugs.free >= 2 
		 * and 
		 * (siteloc.longitude >= 12.9142 and siteloc.longitude <= 12.9392) 
		 * and 
		 * (siteloc.latitude >= 50.8208 and siteloc.latitude <= 50.8458) 
		 */
		
		query << "SELECT * FROM " << SL << ", " << IP << ", " << FP << ", " << PT
					<< " WHERE "
					<< SL << "." << SLIP << " = " << IP << "." << IPID
					<< " AND "
					<< SL << "." << SLID << " = " << FP << "." << FPSL
					<< " AND " 
					<< FP << "." << FPPT << " = " << PT << "." << PTID
					<< " AND "
					<< FP << "." << FPFR << " >= " << "2"
					<< " AND "
					<< "("
						<< SL << "." << SLLO << " >= " << FloatToString(fl_lo_min)
						<< " AND "
						<< SL << "." << SLLO << " <= " << FloatToString(fl_lo_max)
					<< ")"
					<< " AND "
					<< "("
						<< SL << "." << SLLA << " >= " << FloatToString(fl_la_min)
						<< " AND "
						<< SL << "." << SLLA << " <= " << FloatToString(fl_la_max)
					<< ")";
	//		std::cout << query.str() << std::endl;
			res = stmt->executeQuery(query.str());
			query.str("");
		
		if (res->rowsCount()) {
	/*		std::cout << SLID << "\t" 
								<< SLLO << "\t" 
								<< SLLA << "\t" 
								<< SLSN << "\t\t\t" 
								<< SLCT << "\t\t" 
								<< IPV4 << "\t" 
								<< FPFR << "\t" 
								<< PTNA << "\t" 
								<< "Distance to " << str_longitude << " / " << str_latitude << std::endl;*/
			while (res->next()) {
				res_lo = "";
				res_la = "";
				res_tmp = "";
				res_lo = res->getString(SLLO);
				res_la = res->getString(SLLA);
				res_tmp = res->getString(IPV4);
				fl_dist = calc_gps_distance(fl_latitude,fl_longitude,stringtofloat(res_la),stringtofloat(res_lo));
				
	/*			std::cout << res->getString(SLID) << "\t" 
									<< res->getString(SLLO) << "\t\t"
									<< res->getString(SLLA) << "\t\t" 
									<< res->getString(SLSN)	<< "    \t" 
									<< res->getString(SLCT) << "    \t" 
									<< res->getString(IPV4) << "\t" 
									<< res->getString(FPFR) << "\t" 
									<< res->getString(PTNA) << "\t" 
									<< fl_dist << std::endl; */
				if (fl_dist < min_dist) {
					res_ipv4 = "";
					res_ipv4 = res_tmp;
					min_dist = fl_dist;
					
				}
			}
		}
		std::cout << "IP of nearest Site: " << res_ipv4 << std::endl;
		delete res;
		delete stmt;
		
	} catch(sql::SQLException& e) {
			if(e.getErrorCode() != 0) {
				sqlerrornotifier(__FILE__,__FUNCTION__,__LINE__,e.what(), e.getErrorCode(),e.getSQLState());
			}
	}	
}

/*
 * Menu structure
 */

void appdb_sitelocmenu(sql::Connection *con, std::string database) {
	std::cin.clear();
	int choice;
	bool endit = 0;

	while(!endit) {	
		std::cout << "What do you want to do?\n"
						<< "1: Show table\n"
						<< "2: Add new site location\n"
						<< "3: Alter a site location\n"
						<< "4: Delete one Entry\n"
						<< "9: Previous menu\n";

		choice = getIntinp();
	
		switch(choice) {
			case 1: appdb_showsiteloc(con, database);  break;
			case 2: appdb_addsiteloc(con, database); break;
			case 3: appdb_altersiteloc(con, database);  break;
			case 4: appdb_delsiteloc(con, database);  break;
			case 9: endit = 1; break;
			default: ;
		}	
	}	
}

void appdb_ipmenu(sql::Connection *con, std::string database) {
	std::cin.clear();
	int choice;
	bool endit = 0;

	while(!endit) {	
		std::cout << "What do you want to do?\n"
						<< "1: Show table\n"
						<< "2: Generate n new IPv4 and IPv6 addresses\n"
						<< "3: Add one IPv4 and IPv6 address manually\n"
						<< "4: Alter one IPv4 and IPv6 address\n"
						<< "5: Delete one entry\n"
						<< "9: Previous menu\n";

		choice = getIntinp();
	
		switch(choice) {
			case 1: appdb_showip(con, database);  break;
			case 2: appdb_addipautomatic(con, database); break;
			case 3: appdb_addipmanually(con, database);  break;
			case 4: appdb_alterip(con, database);  break;
			case 5: appdb_delip(con, database);  break;
			case 9: endit = 1; break;
			default: ;
		}	
	}		
}

void appdb_ptmenu(sql::Connection *con, std::string database) {
	std::cin.clear();
	
	bool endit = 0;

	while(!endit) {
		int i = 0;

	std::cout << "What do you want to do?\n" <<
					"1: Show table\n" <<
					"2: Add new Plugtgypes\n" <<
					"3: Alter one entry\n" <<
					"4: Delete one entry\n" <<
					"9: previous menu" << std::endl;		
		
		i = getIntinp();

		switch(i) {
			case 1: appdb_showpt(con, database); break;
			case 2: appdb_addnewpt(con, database); break;
			case 3: appdb_alterpt(con, database);  break;
			case 4: appdb_delpt(con, database);  break; 
			case 9: endit = 1; break;
			default: ;
	
		}
	}	
}

void appdb_fpmenu(sql::Connection *con, std::string database) {
	std::cin.clear();
	
	bool endit = 0;

	while(!endit) {
		int i = 0;

	std::cout << "What do you want to do?\n" <<
					"1: Show table\n" <<
					"2: Add free plugs to site location\n" <<
					"3: Alter one entry\n" <<
					"4: Delete one entry\n" <<
					"9: previous menu" << std::endl;		
		
		i = getIntinp();

		switch(i) {
			case 1: appdb_showfp(con, database); break;
			case 2: appdb_addfp(con, database); break;
			case 3: appdb_alterfp(con, database);  break;
			case 4: appdb_delfp(con, database, 0, 0);  break; 
			case 9: endit = 1; break;
			default: ;
		}
	}		
}

void appdb_table_select(sql::Connection *con, std::string database) {
	
	int i;
	bool endit = 0;
	
	while(!endit) {
		std::cout << "Select table: \n"
				<< "1: Site Location\n"
				<< "2: IP Adresses\n"
				<< "3: Plugtypes\n"
				<< "4: Free Plugs\n"
				<< "9: Previous menu\n";
						
		i = getIntinp();
		
		switch(i) {
			case 1: appdb_sitelocmenu(con, database); break;
			case 2: appdb_ipmenu(con, database); break;
			case 3: appdb_ptmenu(con, database); break;
			case 4: appdb_fpmenu(con, database); break;
			case 9: endit = 1; break;
			default: ;
		}	
	}		
}

void appdb_choice(sql::Connection *con, std::string database) {
	std::cin.clear();
	bool endit = 0;
	
	while(!endit) {
		int i = 0;

		std::cout << "======= appdb ======== \n"
						<< "What do you want do ? \n"
						<< "1: Show the full database with all tables in one\n"
						<< "2: Select tables for manipulating\n"
						<< "3: Get IP of nearest Position by GPS-coordinates\n"
						<< "9: Exit\n";
						
			i = getIntinp();

		switch(i) {
			case 1: appdb_showfulldb(con, database); break;
			case 2: appdb_table_select(con, database); break;
			case 3: appdb_getsitebygps(con, database); break;
			case 9: endit = 1; break;
			default: ;
		}	
	}
}