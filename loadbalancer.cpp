#include "loadbalancer.h"

#define ANSI_COLOR_RED "\033[1;31m"
#define ANSI_COLOR_RESET "\033[0m"

LoadBalancer::LoadBalancer() {
    time = 0;
    qSize = 0;
}

void LoadBalancer::run(int webserverCount, int totalClockCycles, bool verbose, bool firewall, int requestSpeed) {
    std::ofstream logFile("logs.txt");
    if (logFile.is_open()) {

        // Display the values of each flag
        logFile << "\nWeb server count: " << webserverCount << endl;
        logFile << "Total clock cycles: " << totalClockCycles << endl;
        logFile << "Verbose: " << boolalpha << verbose << endl;
        logFile << "Firewall: " << boolalpha << firewall << endl;
        logFile << "Request times range from 4-100 seconds to complete" << endl;
       
        logFile << "Request speed: ";
        switch (requestSpeed) {
            case 1:
                logFile << "slow";
                break;
            case 2:
                logFile << "fast";
                break;
            case 3:
                logFile << "varied";
                break;
            default:
                logFile << "unknown";
                break;
        }
        logFile << std::endl << endl;

        generateRequests(20*webserverCount, firewall, verbose, logFile);

        createServers(webserverCount);

        for(cc = 0; cc <= totalClockCycles; cc++){
            //generate some random new requests
            if(requestSpeed == 1) { //slow gen
                if(rand() % 3 == 1) { 
                    generateRequests(rand() % 15, firewall, verbose, logFile);
                }
            } else if (requestSpeed == 2) {
                if(rand() % 3 == 1) { //toggle gen on and off
                    generateRequests(rand() % 250, firewall, verbose, logFile);
                }
            } else {
                 if(cc/1000 % 2 == 0) { //generate slow for first 1k
                    if(rand() % 3 == 1) { 
                        generateRequests(rand() % 15, firewall, verbose, logFile);
                    }
                } else {
                    if(rand() % 3 == 1) { //generate fast for next 1k
                        generateRequests(rand() % 250, firewall, verbose, logFile);
                    }
                }
            }

            bool toRemoveServer = false;
            for(Webserver* w:wServers) {
                bool skipAssignment = false; //used if balancing needed
                if(w -> isDone()) {
                    if(w -> waiting == false) {
                        if(verbose) {
                            logFile << "Webserver finished task at time " << cc << endl;
                            w -> r.printRequest(logFile);
                        }
                        w -> waiting = true;

                        if(qSize < int(15*wServers.size()) && !toRemoveServer) { //too many servers, none sent to delete yet
                            logFile << "[BALANCING] Too many idle servers, toggling decrease" << std::endl;
                            skipAssignment = true;
                            toRemoveServer = true;
                        }
                    }
                    if(qSize != 0 && !skipAssignment) {
                        w -> assignRequest(q.front());
                        q.pop();
                        qSize--;
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
                printStatus(verbose, logFile);
            }
        }
        logFile.close();
        std::cout << "Logs exported to 'logs.txt'." << std::endl;
    } else {
        std::cerr << "Unable to create log file." << std::endl;
    }
    
    std::ofstream serverCountFile("servercount.txt");

    if (serverCountFile.is_open()) {
        // Export data to the file
        for (auto x : servers) {
            serverCountFile << x << '\n';
        }

        serverCountFile.close();
        std::cout << "Data exported to 'servercount.txt'." << std::endl;
    } else {
        std::cerr << "Unable to open the file." << std::endl;
    }

}

void LoadBalancer::generateRequests(int numToAdd, bool firewall, bool verbose, ofstream& logFile) {
    time = 0;
    for(int i = 0; i < numToAdd; i++) {
        Request r = Request();
        if(firewall){
             while((r.ipInAddy > 100 && r.ipInAddy < 110) || (r.ipOutAddy > 100 && r.ipOutAddy < 110)) {
                if(verbose) {
                    logFile << "Request blocked by firewall: \n";
                    r.printRequest(logFile);
                }
                r = Request();
             }
        }
        q.push(r);
        qSize++;
    }
}

void LoadBalancer::printStatus(bool verbose, ofstream& logFile) {
    if(verbose) {
        logFile << "STATUS:" << endl;
        logFile << "Clock cycle: " << cc << endl;
        logFile << "Webservers running: " << countRunningWebservers() << endl;
        logFile << "Webservers provisioned: " << wServers.size() << endl;
        logFile << "Processes in the queue: " << qSize << endl;
        logFile << "Ratio: " << qSize/wServers.size() << endl << endl;
    } else {
        logFile << "[" << cc << "] server count: " << wServers.size() << ", requests per server: " << qSize/wServers.size() << endl;
    }

    while(qSize > int(20*wServers.size())) { //too many requests for the servers we have
        logFile << "[BALANCING] Requests exceed server by too much, creating new web server" << std::endl;
        createServers(1);
    }

    ratios.push_back(static_cast<float>(qSize) / wServers.size());
    servers.push_back(wServers.size());

}

int LoadBalancer::countRunningWebservers(){
    int count = 0;
    for(Webserver* w:wServers) {
        if(w -> waiting == false) {
            count++;
        }
    }
    return count;
}

void LoadBalancer::createServers(int serverCount) {
    for(int i = 0; i < serverCount; i++) {
        Webserver* w = new Webserver();
        if(qSize != 0) {
            w -> assignRequest(q.front());
            q.pop();
            qSize--;
        } else {
            w -> waiting = true;
        }
        wServers.push_back(w);
    }
}


void LoadBalancer::removeServer() {
    for (auto w = wServers.begin(); w != wServers.end(); w++) {
        if ((*w)->waiting == true) {
            delete *w; 
            wServers.erase(w);
            break;
        }
    }
}