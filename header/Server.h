/*
 * @author youriaubry
 * @file Server.h
 * @date 28/09/2021
 * @brief Server gathering data and manipulating log files and console
 */

// Define guards
#ifndef SERVER_H_
#define SERVER_H_

// includes
#include <Data.h>
#include <iostream>
#include <fstream>
#include "Scheduler.h"
#include <string>


using std::string;

/**
 * @class Server
 * @brief deals with console and log files
 */
class Server{
	private :
		Data d; // Contain one value per data type
		Files f; // Contain log files names

	public :
	// Canonical form
		//Constructors
		Server(): d(),f(){}; // Default
		Server(const Server& s); // Copy

		~Server(){}; // Destructor

		//Operators
		Server& operator=(const Server& s);
	// End Canonical form
		friend std::ostream& operator<<(std::ostream& os, const Server& s);

		Server(const Data& d); // Data copy constructor

		Files getF(){ return f; };// Getter

	//Methods

		/**
		* @brief Display data values on the console
		* @return
		*/
		void consoleWrite();

		/**
		* @brief Write in a file a data value, template so any kind of data can be displayed
		* @return
		* @param file_name : name of the file
		* @param value : value to display in the file
		* Needed operators : <<
		*/
		template <class T> void fileWrite(const string& file_name,const T& value);

		/**
		* @brief Write in log files if values were updated
		* @return
		* @param t : true if temperature log has to be written
		* @param h : true if humidity log has to be written
		* @param l : true if light log has to be written
		* @param p : true if pressure log has to be written
		*/
		void filesWrite(const bool& t, const bool& h, const bool& l, const bool& p);

	// Scheduler needs to easily access Server methods and attributes to call them when needed
	friend class Scheduler;
};


#endif /* SERVER_H_ */
