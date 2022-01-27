/*
 * @author youriaubry
 * @file Scheduler.cpp
 * @date 04/10/2021
 * @brief Definition of methods of Scheduler.h
 */

// Includes
#include "Scheduler.h"

using std::string;
using std::time_t;
using std::chrono::system_clock;

// Constructors

Scheduler::Scheduler(): d(), f(), l(), s(){};

Scheduler::Scheduler
	(const float& t, const float& h,
	const float& l, const float& p):
	d(),f(t,h,l,p),l(),s(){};

void Scheduler::getData(){
	d.temperature = s.t.getData();
	d.humidity = s.h.getData();
	d.light = s.l.getData();
	d.pressure = s.p.getData();
}

void Scheduler::updateData(){
	// Call aleaGenVal() of each sensor value
	s.t.aleaGenVal();
	s.h.aleaGenVal();
	s.l.aleaGenVal();
	s.p.aleaGenVal();
}


template <class T> bool Scheduler::sendValue
			( T& value, T& server_value,const float& freq,
					int& log_nb, const clock_t& start){

	// Check if frequency is correctly initialized
	if(freq > 0){
		// Check if value has to be updated
		if(time(start)/freq > (float) log_nb){

			++log_nb; // increase the number of logs
			server_value = value; // Send local value to server

			return true; // Return true if value was updated
		}
	}
	return false; // Return false if value wasn't updated
}


void Scheduler::setFreq
			(const float& t, const float& h,
			const float& l, const float& p){
	f.t = t;
	f.h = h;
	f.l = l;
	f.p = p;
}


void Scheduler::sendData
	(Server& server,const clock_t& start,
	const bool console, const bool log){

	updateData(); // Update all data in sensors
	getData(); // Save sensors values into raw data object
	// Set up booleans to check which values are updated
	bool t_change, h_change, l_change, p_change;
	// Call sendValue() method for each sensor type
	// Store the number of modifications into nb_change
	t_change = sendValue(d.temperature, server.d.temperature, f.t, l.t, start);
	h_change = sendValue(d.humidity, server.d.humidity,f.h, l.h,start);
	l_change = sendValue(d.light, server.d.light, f.l, l.l,start);
	p_change = sendValue(d.pressure, server.d.pressure, f.p, l.p,start);

	// Display values on console if one modification was made
	// And if the mode is activated
	if(console){
		system("cls");
		server.consoleWrite();
	}
	if(log){ server.filesWrite(t_change, h_change, l_change, p_change); }
}

