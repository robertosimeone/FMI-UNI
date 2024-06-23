//
// Created by Robert Borisov on 30.05.21.
//

#include "PeriodicSampler.hpp"

PeriodicSampler::PeriodicSampler(std::string id, size_t period) : Subscriber(id){
this->period = period;
}

Subscriber *PeriodicSampler::clone() const {
    return new PeriodicSampler(*this);
}

void PeriodicSampler::signal(Message message) {
messages.push_back(message);
}

int PeriodicSampler::read() const  {
    if(messages.size() == 0){
        return 0;
    }
int size = (int)messages.size() - 1 ;
if(messages.size() <= period){
    return messages[0].data;
}
int result = this->IndexToReturn(size);
return messages[result].data;

}

int PeriodicSampler::IndexToReturn(int size) const {
    int result  = 0;
    for(int i = 1;i<=size; ++i){
        if(i%period ==0)
            result = i;
    }
    return result;
}
