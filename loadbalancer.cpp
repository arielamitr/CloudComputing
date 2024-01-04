#include "loadbalancer.h"

LoadBalancer::LoadBalancer() {
    time = 0;
    qSize = 0;
}

void LoadBalancer::generateRequests(int numToAdd) {
    time = 0;
    for(int i = 0; i < numToAdd; i++) {
        Request r = Request();
        q.push(r);
        qSize++;
    }
}