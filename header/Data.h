/*
 * @author youriaubry
 * @file Data.h
 * @date 05/10/2021
 * @brief Classes containing one attribute of each sensor type
 */

// Define guards
#ifndef HEADER_DATA_H_
#define HEADER_DATA_H_

// includes
#include <string>
#include <iostream>


using std::string;
using std::ostream;


/**
 * @class Data
 * @brief raw values of each type
 */
class Data{
	private:
		// attributes
		float temperature;
		float humidity;
		bool light;
		int pressure;
	public :
	// Canonical form
		// Default constructor
		Data():
			temperature(),
			humidity(),
			light(),
			pressure(){};
		Data(const Data& d){ *this = d; } // copy constructor

		~Data(){}; // Destructor

		// Copy assignment operator
		Data& operator=(const Data& d){
			temperature = d.temperature;
			humidity = d.humidity;
			light = d.light;
			pressure = d.pressure;
			return *this;
		}
	// End canonical form
		// Writing operator
		friend ostream& operator<<(ostream& os, const Data& d){
			os << "Temperature : " << d.temperature << " C\n";
			os << "Humidity : " << d.humidity << " %\n";
			os << "Light : " << d.light <<'\n';
			os << "Pressure : " << d.pressure << " hPa\n";
			return os;
		}

	// Declare Server and Scheduler as friends
	friend class Server;
	friend class Scheduler;
};

/**
 * @class Files
 * @brief Log files names for each sensor type
 */
class Files{
	private:
		// attributes
		string t;
		string h;
		string l;
		string p;

	public:
	// Canonical form
		// Default constructor
		Files():
		t("log_files\\temperature.log"),
		h("log_files\\humidity.log"),
		l("log_files\\light.log"),
		p("log_files\\pressure.log"){};

		~Files(){};

		// no need for copy constructor or operator
		// Because values never are modified

	// End canonical form

		// Writing operator
		friend ostream& operator<<(ostream& os, const Files& f){
			os << "Temperature : " << f.t <<'\n';
			os << "Humidity : " << f.h << '\n';
			os << "Light : " << f.l <<'\n';
			os << "Pressure : " << f.p << '\n';
			return os;
		}

		// Getters
		string getT(){ return t; }
		string getH(){ return h; }
		string getL(){ return l; }
		string getP(){ return p; }

	// Declare Server and Scheduler as friends
	friend class Server;
	friend class Scheduler;
};


/**
 * @class Frequencies
 * @brief One attribute for each sensor type representing its sampling frequency
 */
class Frequencies{
	private:
		// Attributes
		float t;
		float h;
		float l;
		float p;

	public:
	// Canonical form

		// Constructors
		Frequencies(): t(0),h(0),l(0),p(0){}; // Default
		// Copy
		Frequencies
			(const float& t2, const float& h2,
			const float& l2, const float& p2){
			if(t2 > 0 && h2 > 0 && l2 > 0 && p2 > 0){
				t = t2;
				h = h2;
				l = l2;
				p = p2;
			}
		};
		~Frequencies(){}; // Destructor
	// End canonical form

	// Getters
		float getT(){ return t; }
		float getH(){ return h; }
		float getL(){ return l; }
		float getP(){ return p; }

	// Setters
		void setT(const float& f){ if(f>0){ t = f; } }
		void setH(const float& f){ if(f>0){ h = f; } }
		void setL(const float& f){ if(f>0){ l = f; } }
		void setP(const float& f){ if(f>0){ p = f; } }

		// Writing operator
		friend ostream& operator<<(ostream& os, const Frequencies& f){
			os << "Temperature : 1 per " << f.t <<" seconds\n";
			os << "Humidity : 1 per " << f.h << " seconds\n";
			os << "Light : 1 per " << f.l <<" seconds\n";
			os << "Pressure : 1 per " << f.p << " seconds\n";
			return os;
		}

	// Declare Scheduler as friend
	friend class Scheduler;
};

/**
 * @class Logs
 * @brief Count logs for each sensor attribute
 */
class Logs{
	private:
		// Attributes
		int t;
		int h;
		int l;
		int p;
	public:
		// Default constructor
		Logs(): t(0),h(0),l(0),p(0){};

	// Declare Scheduler as friend
	friend class Scheduler;
};


#endif /* HEADER_DATA_H_ */
