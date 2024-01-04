#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_set>
#include <cstdlib>
#include "request.h"
#include "webserver.h"

/**
 * @brief The LoadBalancer class represents a simple load balancer.
 */
class LoadBalancer {
public:
    /**
     * @brief Constructor for the LoadBalancer class.
     */
    LoadBalancer();

    /**
     * @brief Run the load balancer simulation.
     * @param webserverCount Number of web servers.
     * @param totalClockCycles Total clock cycles for the simulation.
     * @param verbose Verbose mode flag.
     * @param firewall Firewall mode flag.
     * @param requestSpeed Speed of generating requests (slow, fast, or varied).
     */
    void run(int webserverCount, int totalClockCycles, bool verbose, bool firewall, int requestSpeed);

    /**
     * @brief Queue of requests.
     */
    std::queue<Request> q;

    /**
     * @brief Current time.
     */
    int time;

    /**
     * @brief Current clock cycle.
     */
    int cc = 0;

    /**
     * @brief Total number of requests processed.
     */
    int requestsCompleted = 0;

    /**
     * @brief Total number of requests blocked by firewall.
     */
    int requestsBlocked = 0;

    /**
     * @brief Vector of web servers.
     */
    std::vector<Webserver*> wServers;

    /**
     * @brief Vector of request-to-server ratios.
     */
    std::vector<float> ratios;

    /**
     * @brief Vector of server counts.
     */
    std::vector<int> servers;

    /**
     * @brief Size of the request queue.
     */
    int qSize;

    /**
     * @brief Generate a specified number of requests and add them to the queue.
     * @param numToAdd Number of requests to generate.
     * @param firewall Firewall mode flag.
     * @param verbose Verbose mode flag.
     * @param logFile Output log file stream.
     */
    void generateRequests(int numToAdd, bool firewall, bool verbose, std::ofstream& logFile);

    /**
     * @brief Print the current status of the load balancer.
     * @param verbose Verbose mode flag.
     * @param outputFile Output file stream.
     */
    void printStatus(bool verbose, std::ofstream& outputFile);

    /**
     * @brief Count the number of running web servers.
     * @return Number of running web servers.
     */
    int countRunningWebservers();

    /**
     * @brief Create a specified number of web servers.
     * @param serverCount Number of web servers to create.
     */
    void createServers(int serverCount);

    /**
     * @brief Remove an idle server.
     */
    void removeServer();
};

#endif // LOADBALANCER_H
