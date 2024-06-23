//
// Created by Robert Borisov on 3.06.21.
//

#include "Publisher.hpp"

void Publisher::unsubscribe(Averager * averager) {
    int counter = 0;
    for(auto x : subscribers){
        if(x->getID() == averager->getID()){
            subscribers.erase(subscribers.begin()+counter);
        }
        counter++;
    }
}

void Publisher::unsubscribe(MovingAverager * movingAverager) {
    int counter = 0;
    for(auto x : subscribers){
        if(x->getID() == movingAverager->getID()){
            subscribers.erase(subscribers.begin()+counter);
        }
        counter++;
    }
}

void Publisher::unsubscribe(PeriodicSampler * periodicSampler) {
    for(size_t i = 0 ; i < subscribers.size() ; i++){
        if(subscribers[i]->getID() == periodicSampler->getID()){
            subscribers.erase(subscribers.begin()+(int)i);
        }
    }
}

std::vector<Subscriber *> &Publisher::getSubscribers() {
    return subscribers;
}

void Publisher::signal(Message message) {
    for(auto subscriber : subscribers){
        subscriber->signal(message);
    }
}

