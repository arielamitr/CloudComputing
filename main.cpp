#include "main.h"
#include "loadbalancer.h"
#include "webserver.h"

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
vector<Webserver*> wServers;
vector<float> ratios;
vector<int> servers;

int main() {
	time_t current_time = time(NULL);
    srand(current_time); //provide random seed

    cout << "Welcome to the load balancer. Please enter how many web servers you would like to begin with." << endl;
    webserverCount = getUserInput();

    cout << "Please enter how many clock cycles you would like to run." << endl;
    totalClockCycles = getUserInput();

    lb.generateRequests(20*webserverCount);

    createServers(webserverCount);

    for(cc = 0; cc <= totalClockCycles; cc++){
    	//generate some random new requests
    	if(cc/1000 % 50 != 0) {
	    	if(rand() % 3 == 1) { //toggle gen on and off
	    		lb.generateRequests(rand() % 15);
	    		//25 both adds and removes
	    	}
	    } else {
	    	if(rand() % 3 == 1) { //toggle gen on and off
	    		lb.generateRequests(rand() % 250);
	    		//25 both adds and removes
	    	}
	    }

    	bool toRemoveServer = false;
    	for(Webserver* w:wServers) {
    		bool skipAssignment = false; //used if balancing needed
	    	if(w -> isDone()) {
	    		if(w -> waiting == false) {
	    			//cout << "Webserver finished task at time " << cc << endl;
	    			//w -> r.printRequest();
	    			w -> waiting = true;

	    			if(lb.qSize < int(15*wServers.size()) && !toRemoveServer) { //too many servers, none sent to delete yet
						cout << "BALANCING: Too many idle servers, toggling decrease\n" << endl;
						skipAssignment = true;
						toRemoveServer = true;
					}
	    		}
	    		if(lb.qSize != 0 && !skipAssignment) {
	    			w -> assignRequest(lb.q.front());
	    			lb.q.pop();
	    			lb.qSize--;
	    			w -> waiting = false;
	    		} else {
	    			//cout << "WEBSERVER BORED" << endl;
	    		}
	    	} else {
	    		w -> cycle();
	    	}
	    }

	    if(toRemoveServer) {
	    	removeServer();
	    }

    	if(cc%10 == 0) {
    		printStatus();
    	}
    }

    /*for(auto x: ratios) {
    	cout << x << endl;
    }
    cout << endl;

    for(auto x: servers) {
    	cout << x << endl;
    }
    cout << endl;*/
     std::ofstream outputFile("output.txt");

    if (outputFile.is_open()) {
        // Export data to the file
        for (auto x : servers) {
            outputFile << x << '\n';
        }

        outputFile.close();
        std::cout << "Data exported to 'output.txt'." << std::endl;
    } else {
        std::cerr << "Unable to open the file." << std::endl;
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
	//cout << "STATUS:" << endl;
	//cout << "Clock cycle: " << cc << endl;
	//cout << "Webservers running: " << countRunningWebservers() << endl;
	//cout << "Webservers provisioned: " << wServers.size() << endl;
	//cout << "Processes in the queue: " << lb.qSize << endl;
	//cout << "Ratio: " << lb.qSize/wServers.size() << endl << endl;

	while(lb.qSize > int(20*wServers.size())) { //too many requests for the servers we have
		cout << "BALANCING: Requests exceed server by too much, creating new webserver\n" << endl;
		createServers(1);
	}

	ratios.push_back(static_cast<float>(lb.qSize) / wServers.size());
	servers.push_back(wServers.size());

}

int countRunningWebservers(){
	int count = 0;
	for(Webserver* w:wServers) {
	    if(w -> waiting == false) {
	    	count++;
	    }
	}
	return count;
}

void createServers(int serverCount) {
	for(int i = 0; i < serverCount; i++) {
	    Webserver* w = new Webserver();
	    if(lb.qSize != 0) {
	    	w -> assignRequest(lb.q.front());
	   		lb.q.pop();
	    	lb.qSize--;
	    } else {
	    	w -> waiting = true;
	    }
	    wServers.push_back(w);
    }
}


void removeServer() {
    for (auto w = wServers.begin(); w != wServers.end(); w++) {
        if ((*w)->waiting == true) {
            delete *w; 
            wServers.erase(w);
            break;
        }
    }
}

