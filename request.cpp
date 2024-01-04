#include "request.h"

Request::Request() {
    ipInAddy = rand() % 256;
    ipIn = to_string(ipInAddy)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256);
    ipOutAddy = rand() % 256;
    ipOut = to_string(ipOutAddy)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256);
    cycles = rand() % 96 + 4;
}

void Request::printRequest(ofstream& logFile) {
    logFile << "IP in: " << ipIn << "\nIP out: " << ipOut << "\nTime: " << cycles << endl << endl;
}