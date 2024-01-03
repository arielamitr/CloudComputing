#include "main.h"

//numbers for time are between 4-100, random num
//create random ip addresses (XXX.XXX.XXX.XXX), max is 255 for each
//ip range blocker: filter out certain IPs within a certain range

int main() {
	time_t current_time = time(NULL);
    srand(current_time); //provide random seed
    
	//create request
	Request r = Request();
	Request s = Request();
	r.printRequest();
	s.printRequest();
}


