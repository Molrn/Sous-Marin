/*
 * @author youriaubry
 * @file Sensors.h
 * @date 04/10/2021
 * @brief All sensors type declaration
 */

// Define guards
#ifndef HEADER_Sensors_H_
#define HEADER_Sensors_H_

//includes
#include <cstdlib>
#include <iostream>
#include <cmath>

using std::min;
using std::max;

/**
 * @class Sensor
 * @brief declaration of a sensor, template so any type of data can be used
 */
template <class T> class Sensor{
	protected : // Protected so it can be accessed in inherited classes
		T data; // Value of the data represented by the sensor
	public :
	// Canonical form

		// Constructors
		Sensor(): data(){};  // Default
		Sensor(const Sensor& s){ *this = s;}; // copy
		Sensor(const T& d):data(d){};
		// Copy assignment operator
		Sensor& operator=(const Sensor& s){
			data = s.data;
			return *this;
		};
		virtual ~Sensor(){}; // Destructor

	// Methods

		// Getter
		T& getData(){ return data; };

		/**
		* @brief Generate random float between two boundaries
		* @param min : lower boundary
		* @param max : upper boundary
		* @return generated float
		*/
		float floatInRange(const float& min, const float& max){
			return (max-min)*(static_cast <float> (rand()) / static_cast <float> (RAND_MAX))+min;
		}

		/**
		* @brief Update data to a random value, can be overridden in inherited classes
		* @return
		*/
		virtual void aleaGenVal(){ data = rand()%2; };
};

/**
 * @class Humidity
 * @brief Declaration of a humidity sensor
 */
class Humidity : public Sensor<float>{
	public :


		Humidity(): Sensor(50){};
		/**
		* @brief Update data to a random value which a humidity sensor could sense
		* @return
		*/
		void aleaGenVal() override{
			float delta = 1;
			data = floatInRange(fmax(0,data-delta),fmin(100, data+delta));
		}
};

/**
 * @class Temperature
 * @brief Declaration of a temperature sensor
 */
class Temperature : public Sensor<float>{
	public :

		Temperature():Sensor(20){};
		/**
		* @brief Update data to a random value which a temperature sensor could sense
		* @return
		*/
		void aleaGenVal() override{
			float delta = 1;
			data = floatInRange(fmax(-20,data-delta),fmin(60, data+delta));
		}
};

/**
 * @class Light
 * @brief Declaration of a light sensor
 */
class Light : public Sensor<bool>{
	public :
		/**
		 * Default constructor
		 * Sets light to the average pressure on earth
		 */
		Light(): Sensor(true){};
		/**
		* @brief Update data to a random value which a light sensor could sense
		* @return
		*/
		void aleaGenVal() override{
			int delta = 90;
			if(data){
				data = (rand()%100 < delta);
			}else{
				data = (rand()%100 > delta);
			}
		}
};

/**
 * @class Pressure
 * @brief Declaration of a pressure sensor
 */
class Pressure : public Sensor<int>{
	public :
		/**
		 * Default constructor
		 * Sets pressure to the average pressure on earth
		 */
		Pressure():Sensor(985){};
		/**
		* @brief Update data to a random value which a pressure sensor could sense
		* @return
		*/
		void aleaGenVal() override{
			int delta = 5;
			data = (data + rand()%(delta*2)-delta)%3000;
			if(data < 80){ data = 80; }
		}
};

/**
 * @class Sensors
 * @brief Contain one type of every specific sensor
 */
class Sensors{
	private:
		Temperature t;
		Humidity h;
		Light l;
		Pressure p;
	public :
		Sensors():t(),h(),l(),p(){};
	friend class Scheduler;
};

#endif /* HEADER_Sensors_H_ */
