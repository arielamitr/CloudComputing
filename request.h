/**
 * @file request.h
 * @brief Header file for the Request class.
 */

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_set>
#include <cstdlib>

using namespace std;

/**
 * @class Request
 * @brief Represents a request in a load balancing system.
 */
class Request {
public:
    string ipIn;         /**< Source IP address of the request. */
    int ipInAddy;        /**< Numeric representation of the source IP address. */
    string ipOut;        /**< Destination IP address of the request. */
    int ipOutAddy;       /**< Numeric representation of the destination IP address. */
    int cycles;          /**< Time required for the request to complete. */

    /**
     * @brief Default constructor for the Request class.
     * 
     * Initializes the IP addresses and cycles randomly.
     */
    Request();

    /**
     * @brief Prints the details of the request to the given output file stream.
     * 
     * @param logFile The output file stream where the request details will be printed.
     */
    void printRequest(ofstream& logFile);
};
