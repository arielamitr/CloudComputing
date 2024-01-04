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

class Webserver {
    public:
        Request r;
        int cyclesLeft;
        bool waiting;

        Webserver();

        void assignRequest(Request newRequest);

        bool isDone();

        void cycle();
};