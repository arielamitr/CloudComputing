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
        string ipOut;
        int cycles;

        Request() {
            ipIn = to_string(rand() % 256)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256);
            ipOut = to_string(rand() % 256)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256);
            cycles = rand() % 96 + 4;
        }

        void printRequest() {
            cout << "IP in: " << ipIn << "\nIP out: " << ipOut << "\nTime: " << cycles << endl;
        }
};