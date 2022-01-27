/*
 * @author youriaubry
 * @file Server.cpp
 * @date 28/09/2021
 * @brief Definition of methods of Server.h
 */


#include "Server.h"

using std::string;

// Constructors

Server::Server(const Server& s){ (*this) = s; }
Server::Server(const Data& d):f(){ this->d = d; }

// Operators

// Copy
Server& Server::operator=(const Server& s){
	d = s.d;
	return *this;
}

// Writing
std::ostream& operator<<(std::ostream& os, const Server& s){
	os << s.d;
	os << "\nPress any key to exit (not available yet)";
	os << "\nCTRL+C to kill process";
	return os;
}

void Server::consoleWrite(){ std::cout << (*this); }


template <class T> void Server::fileWrite(const string& file_name,const T& value){

	time_t now = time(0); // Get current time
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now); // Splits into time structure current time
    // Store date/time into buffer
    strftime(buf, sizeof(buf), "  --  %Y-%m-%d %X", &tstruct);
    std::ofstream file;
    // Open file in append mode
	file.open (file_name,std::ios_base::app);
	// Check if file was correctly opened
	if (file){
		// Write value and time buffer into file
		file << value << buf << '\n';
		file.close(); // Close file
	}else{
		// Send error message to cerr stream
		std::cerr << "Error while opening file " << file_name;
	}
	/**time_t now = system_clock::to_time_t(system_clock::now());
	std::ofstream file;
	file.open (file_name,std::ios_base::app);
	file << value << "  --  " << std::ctime(&now) << '\n';
	file.close();**/

}

void Server::filesWrite(const bool& t, const bool& h, const bool& l, const bool& p){

	// For each sensor type, check boolean and writes log if activated
	if(t){ fileWrite(f.getT(), d.temperature); };
	if(h){ fileWrite(f.getH(), d.humidity); };
	if(l){ fileWrite(f.getL(), d.light); };
	if(p){ fileWrite(f.getP(), d.pressure); };

}

