/**
 * @file webserver.cpp
 * @brief Implementation file for the Webserver class.
 */

#include "webserver.h"

/**
 * @brief Default constructor for the Webserver class.
 * 
 * Initializes the web server with no assigned request and waiting for a new one.
 */
Webserver::Webserver() {
    cyclesLeft = 0;
}

/**
 * @brief Assigns a new request to the web server.
 * 
 * @param newRequest The new request to be assigned to the web server.
 */
void Webserver::assignRequest(Request newRequest) {
    r = newRequest;
    cyclesLeft = r.cycles;
    waiting = false;
}

/**
 * @brief Checks if the web server has completed processing its current request.
 * 
 * @return True if the web server has completed processing; false otherwise.
 */
bool Webserver::isDone() {
    return cyclesLeft == 0;
}

/**
 * @brief Simulates one cycle of processing for the web server.
 * 
 * If the server is actively processing a request, decrements the remaining cycles.
 * If the request is completed, sets the waiting flag to true.
 */
void Webserver::cycle() {
    cyclesLeft--;
}
