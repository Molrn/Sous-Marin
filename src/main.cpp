/*
 * @author youriaubry
 * @file main.cpp
 * @date 28/09/2021
 * @brief Menu describing the UI
 */
#include "Server.h"
#include "Sensors.h"
#include "Scheduler.h"
#include <thread>
#include "conio.h"

using std::cout;
using std::cin;
//using std::thread;

void getFreq(const string& data, float& freq);
void defaultMenu(const bool& log, const bool& console);

int main(){

// Variables declaration
	// set default value to console and log mode
	bool log = true, console = true;
	Server serv; // Initialize server
	// Frequencies to be set by the user
	float t_freq = 1, h_freq = 1, l_freq = 1, p_freq = 1;
	Scheduler sch; // Initialize scheduler
	clock_t start; // Clock when the program starts
	int nb_sec; // Number of seconds since program launch
	char menu = 'd'; // Menu variables

// Menu description
	// Value 'q' : quit the menu
	while(menu != 'q'){
		system("cls");
		switch(menu){

		// Value 'f' : Show the log files paths
			case 'f' :
				cout << serv.getF();
				cout << "\nPress any key to continue";
				getch();
				// Get back to the default menu
				menu = 'd';
			break;
		// value 'p' : Set up the sampling periods
			case 'p' :
				// Control User input
				while(menu != 'q'){
					system("cls");
					// Display frequency menu
					cout << "t : Set temperature sampling frequency (current : " << t_freq << ")\n";
					cout << "h : Set humidity sampling frequency (current : " << h_freq << ")\n";
					cout << "l : Set light sampling frequency (current : " << l_freq << ")\n";
					cout << "p : Set pressure sampling frequency (current : " << p_freq << ")\n";
					cout << "q : Exit frequency menu\n";
					cin >> menu;
					switch(menu){
						case 't': getFreq("temperature",t_freq);
							break;
						case 'h': getFreq("humidity",h_freq);
							break;
						case 'l': getFreq("light",l_freq);
							break;
						case 'p': getFreq("pressure",p_freq);
							break;
						default:
							break;
					}
				}
				menu = 'd';
			break;
		// value 'l' : set up log mode
			case 'l' :
				//Control user input
				while(menu != 'y' && menu != 'n'){
					system("cls");
					cout << "Save samples into log files ?\n\n";
					cout << "y : Yes\nn : No\n";
					cin >> menu;
				}
				log = (menu == 'y');
				// reset menu value to allow multiple log and console sets
				menu = 'd';
			break;
		 // value 'c' : Set up console mode
			case 'c' :
				while(menu != 'y' && menu != 'n'){
					system("cls");
					cout << "Display samples on console ?\n\n";
					cout << "y : Yes\nn : No\n";
					cin >> menu;
				}
				console = (menu == 'y');
				menu = 'd';
			break;
		// Value 's' : Start the program
			case 's' :
				// Set scheduler frequencies to user values (default : 1)
				sch.setFreq(t_freq,h_freq,l_freq,p_freq);
				// Get current time to compute time spent since program launch
				start = clock();
				// Initializes number of second since program launch
				nb_sec = 0;
				// Infinite loop (So far, impossible to exit it)
				while(1){
					// limits sampling to one per second
					if(((float) clock() - start)/CLOCKS_PER_SEC > (float)nb_sec){
						++nb_sec;
						// Send data from sensors to the server if necessary
						sch.sendData(serv,start,console,log);
					}
				}
				menu = 'd';
			break;
			// Default menu (option choice)
			default : defaultMenu(log, console);
				cin >> menu;
			break;
		}
	}
	return 0;
}

/**
* @brief Get frequency value from user
* @return
* @param data : data name to display on the console
* @param freq : frequency value to set
*/

void getFreq(const string& data, float& freq){
	system("cls");
	cout << "Enter period of " << data << " sampling (seconds) : ";
	cin >> freq;
}

/**
* @brief Display menu options
* @param log : log mode
* @param console : console mode
* @return
*/

void defaultMenu(const bool& log, const bool& console){
	system("cls");
	cout << "Pick your option\n\n";
	cout << "f : Consult log files path\n";
	cout << "p : Enter sampling periods (integer, default 1)\n";
	cout << "s : start simulation\n";
	cout << "l : select log mode (current : " << log << ")\n";
	cout << "c : select console mode (current : " << console << ")\n";
	cout << "q : Quit\n";
}
