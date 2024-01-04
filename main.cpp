#include "main.h"
#include "loadbalancer.h"

//numbers for time are between 4-100, random num
//create random ip addresses (XXX.XXX.XXX.XXX), max is 255 for each
//ip range blocker: filter out certain IPs within a certain range
//randomly generate requests, and if it's too big add more web servers
//every 10 clock cycles check if we need to add or remove web servers (see how many items are in queue vs how many webservers there are)
int webserverCount;
int totalClockCycles;
int cc = 0;
bool verbose = true;
LoadBalancer lb = LoadBalancer();

int main() {
	time_t current_time = time(NULL);
    srand(current_time); //provide random seed

    cout << "Welcome to the load balancer. Please enter how many web servers you would like to begin with." << endl;
    webserverCount = getUserInput();

    cout << "Please enter how many clock cycles you would like to run." << endl;
    totalClockCycles = getUserInput();

    lb.generateRequests(rand() % 100);

    //need queue of webservers here

    for(cc = 0; cc <= totalClockCycles; cc++){
    	//generate some random new attacks
    	if(rand() % 3 == 1) {
    		lb.generateRequests(rand() % 15);
    	}
    	//for each webserver, increment the clock
    	//if empty and load balancer has stuff in the queue, give it a process
    	//if not empty, decrement clock cycles remaining by 1
    	//if remaining is 0, print the request and assign a new one
    	if(verbose) { //show output when requests are completed

    	}

    	if(cc%10 == 0) {
    		printStatus();
    	}
    }


}

int getUserInput(){
	int userInput;
	std::cout << "Enter an integer: ";
	while (true) {
        // Check if the input is an integer
        if (std::cin >> userInput && userInput > 0) {
            // Input is valid, break out of the loop
            break;
        } else {
            // Clear the input buffer to handle the error
            cin.clear();
            // Discard the invalid input
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer: ";
        }
    }
    return userInput;
}

void printStatus() {
	cout << "STATUS:" << endl;
	cout << "Clock cycle: " << cc << endl;
	cout << "Webservers running: " << min(webserverCount, lb.qSize) << endl;
	cout << "Webservers provisioned: " << webserverCount << endl;
	cout << "Processes in the queue: " << max(lb.qSize-webserverCount, 0) << endl << endl;

}

