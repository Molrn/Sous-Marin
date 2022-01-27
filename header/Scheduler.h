/*
 * @author youriaubry
 * @file Scheduler.h
 * @date 04/10/2021
 * @brief Scheduler gathers sensor values and send it to server according to a timer
 */

// Define guards
#ifndef HEADER_SCHEDULER_H_
#define HEADER_SCHEDULER_H_

// includes
#include <chrono>
#include <ctime>
#include "Server.h"
#include <Sensors.h>
#include <Data.h>

using std::string;

class Server;

/**
 * @class Scheduler
 * @brief gathers sensor values and send it to server according to a timer
 */
class Scheduler{
	private :
		// Each attribute possesses an attribute per humidity, temperature, light, pressure
		Data d;
		Frequencies f;
		Logs l;
		Sensors s;

	public:
	//Canonical form
		// Constructors
		Scheduler(); // default
		Scheduler(const Scheduler& s); // Copy

		~Scheduler(){}; // Destructor

		// Copy assignment operator
		Scheduler& operator=(const Scheduler& s);
	// End canonical form

		// Frequencies contructor
		Scheduler
			(const float& t, const float& h,
			const float& l, const float& p);

		/**
		* @brief Compute seconds spent since a date
		* @param start : starting date
		* @return seconds spent
		*/
		float time(const clock_t& start){
			return ((float) clock() - start)/CLOCKS_PER_SEC;
		};

		/**
		* @brief Call the aleaGenVal() method of each sensor
		* @return
		*/
		void updateData();

		/**
		* @brief Move data from sensors to scheduler save
		* @return
		*/
		void getData();

		/**
		* @brief Update frequency values
		* @param t : temperature frequency
		* @param h : humidity frequency
		* @param l : light frequency
		* @param p : pressure frequency
		* @return
		*/
		void setFreq
			(const float& t, const float& h,
			const float& l, const float& p);

		/**
		* @brief Send data to server if the clock matches the frequency condition
		* @param s : server
		* @param start : clock indicating the beginning of the program
		* @param console : indicate console mode (true = display, false = don't)
		* @param log : log mode (true = write into log files, false = don't)
		* @return
		*/
		void sendData
			(Server& s, const clock_t& start,
			const bool console, const bool log);

		/**
		* @brief send one value to the server
		* @param value : value to send to the server
		* @param server_value : Server value to update
		* @param freq : frequency of log write
		* @param log_nb : number of logs since the beginning of the program
		* @param start : clock indicating the beginning of the program
		* @return true if value was sent, false otherwise
		* Needed operators : =
		*/
		template <class T> bool sendValue
			(T& value, T& server_value,
			const float& freq, int& log_nb,
			const clock_t& start);
};


#endif /* HEADER_SCHEDULER_H_ */