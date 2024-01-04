#include "webserver.h"

Webserver::Webserver() {
    cyclesLeft = 0;
}

void Webserver::assignRequest(Request newRequest) {
    r = newRequest;
    cyclesLeft = r.cycles;
    waiting = false;
}

bool Webserver::isDone() {
    return cyclesLeft == 0;
}

void Webserver::cycle() {
    cyclesLeft--;
}