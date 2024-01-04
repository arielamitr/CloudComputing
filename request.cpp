/**
 * @file request.h
 * @brief Implementation file for the Request class.
 */

#include "request.h"

/**
 * @brief Default constructor for the Request class.
 * 
 * Initializes the IP addresses and cycles randomly.
 */
Request::Request() {
    ipInAddy = rand() % 256;
    ipIn = to_string(ipInAddy)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256);
    ipOutAddy = rand() % 256;
    ipOut = to_string(ipOutAddy)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256)+"."+to_string(rand() % 256);
    cycles = rand() % 96 + 4;
}

/**
 * @brief Prints the details of the request to the given output file stream.
 * 
 * @param logFile The output file stream where the request details will be printed.
 */
void Request::printRequest(ofstream& logFile) {
    logFile << "IP in: " << ipIn << "\nIP out: " << ipOut << "\nTime: " << cycles << endl << endl;
}
