#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_set>
#include<cstdlib>

using namespace std;

class Request {
    public:
        string ipIn;
        int ipInAddy;
        string ipOut;
        int ipOutAddy;
        int cycles;

        Request();

        void printRequest();
};