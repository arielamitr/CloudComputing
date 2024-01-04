#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_set>
#include<cstdlib>
#include "request.h"
#include "webserver.h"

using namespace std;

class LoadBalancer {
    public:
        queue <Request> q;
        int time;
        int cc = 0;

        vector<Webserver*> wServers;  
        vector<float> ratios;
        vector<int> servers;

        LoadBalancer();

        void run(int webserverCount, int totalClockCycles, bool verbose, bool firewall, int requestSpeed);

        int qSize;

        void generateRequests(int numToAdd, bool firewall, bool verbose, ofstream& logFile);

        void printStatus(bool verbose, ofstream& outputFile);

        int countRunningWebservers();

        void createServers(int serverCount);

        void removeServer();

};