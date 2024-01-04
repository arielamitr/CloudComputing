#include "main.h"
#include "loadbalancer.h"

//ip range blocker: filter out certain IPs within a certain range

int main(int argc, char* argv[]) {
    int webserverCount = 0;
    int totalClockCycles = 0;
    bool verbose = false;
    int requestSpeed = 0; 
    bool firewall = false;

    LoadBalancer lb = LoadBalancer();

    // Loop through command-line arguments
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-s") {
            if (i + 1 < argc) {
                webserverCount = stoi(argv[i + 1]);
            }
        } else if (arg == "-c") {
            if (i + 1 < argc) {
                totalClockCycles = stoi(argv[i + 1]);
            }
        } else if (arg == "-v") {
            verbose = true;
        } else if (arg == "-f") {
            firewall = true;
        } else if (arg == "-q") {
            if (i + 1 < argc) {
                string speed = argv[i + 1];
                if (speed == "slow") {
                    requestSpeed = 1;
                } else if (speed == "fast") {
                    requestSpeed = 2;
                } else if (speed == "varied") {
                    requestSpeed = 3;
                }
            }
        }
    }

    // If a flag is not set, ask the user for input
    if (webserverCount == 0) {
        cout << "Enter the number of web servers\n";
        webserverCount = getUserInput();
    }

    if (totalClockCycles == 0) {
        cout << "Enter the total clock cycles\n";
        totalClockCycles = getUserInput();
    }

    if (requestSpeed == 0) {
        string speed;
        cout << "Enter request speed (slow/fast/varied): ";
        cin >> speed;

        if (speed == "slow") {
            requestSpeed = 1;
        } else if (speed == "fast") {
            requestSpeed = 2;
        } else if (speed == "varied") {
            requestSpeed = 3;
        } else {
            cerr << "Invalid request speed. Using default (varied)." << endl;
            requestSpeed = 3;
        }
    }

    lb.run(webserverCount, totalClockCycles, verbose, firewall, requestSpeed);
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

