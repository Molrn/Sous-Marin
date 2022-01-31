Project realised using a Windows OS

# Execution
A makefile is used, therefore :
	- make to compile
	- main to launch

# Project
## Sensors
The Sensor class is a template. It contains one attribute, data, which can be of any type, and a virtual method AleaGenValue() which has to be overridden by inherited classes. Temperature, Humidity, Light and Pressure classes are all inherited from Sensor, with as data type float, float, bool and int. In each case, the method AleaGenValue() is written in a way so the generated value is coherent with the measured value and with the previous value generated. 

## Data
In order to avoid repeting for each kind of attribute created one attribute per sensor type, there is in the Data.h file classes containing one attribute per sensor type. There is one class for log file names, one for raw values, one for sensors and one for frequency of sampling.

## Server
The Server class contains as attributes raw values and log file names. It contains three methods : fileWrite(), which write a log line in the chosen file; filesWrite(), which calls the fileWrite() method for each chosen sensor type; consoleWrite(), which displays values on the console.

## Scheduler
The scheduler's role is to send data to the server on a timer. The class contains as attributes Sensors, to which ones the value is updated every second using the AleaGenValue() method to simulate a system working in real time. The sendValue() method uploads the chosen value into the server if the sampling period is over, and if so it starts a new period for this value. sendData() is used to call sendValue() for each sensor type. It also calls the Server::consoleWrite() and Server::filesWrite() if console and log options are activated.

## Menu
The menu contains several options :
	- Display log files paths
	- Set up sampling periods
	- Set up log and console mode
	- Start the simulation

## Improvements
The main issue of the project is that the simulation can't be stopped on it has been launched without shutting the program. It could have been implemented using threads, but it is kind of tricky to do on a Windows OS.
