/**
 * @file webserver.h
 * @brief Header file for the Webserver class.
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
#include "request.h"

using namespace std;

/**
 * @class Webserver
 * @brief Represents a web server in a load balancing system.
 */
class Webserver {
public:
    Request r;        /**< The request currently being processed by the web server. */
    int cyclesLeft;    /**< The remaining cycles for the current request to complete. */
    bool waiting;      /**< Flag indicating whether the web server is waiting for a new request. */

    /**
     * @brief Default constructor for the Webserver class.
     * 
     * Initializes the web server with no assigned request and waiting for a new one.
     */
    Webserver();

    /**
     * @brief Assigns a new request to the web server.
     * 
     * @param newRequest The new request to be assigned to the web server.
     */
    void assignRequest(Request newRequest);

    /**
     * @brief Checks if the web server has completed processing its current request.
     * 
     * @return True if the web server has completed processing; false otherwise.
     */
    bool isDone();

    /**
     * @brief Simulates one cycle of processing for the web server.
     * 
     * If the server is actively processing a request, decrements the remaining cycles.
     * If the request is completed, sets the waiting flag to true.
     */
    void cycle();
};
