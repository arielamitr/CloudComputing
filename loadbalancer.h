#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_set>
#include<cstdlib>
#include "request.h"

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

        int qSize;

        void generateRequests(int numToAdd);

};