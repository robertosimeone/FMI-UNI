//
// Created by Robert Borisov on 30.05.21.
//

#include "SimplePublisher.hpp"

void SimplePublisher::subscribe(Averager * averager)  {
    this->getSubscribers().push_back(averager);

}

void SimplePublisher::subscribe(MovingAverager * movingAverager) {
    this->getSubscribers().push_back(movingAverager);
}

void SimplePublisher::subscribe(PeriodicSampler * periodicSampler) {
    this->getSubscribers().push_back(periodicSampler);
}


