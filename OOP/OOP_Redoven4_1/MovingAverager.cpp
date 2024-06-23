//
// Created by Robert Borisov on 30.05.21.
//

#include "MovingAverager.hpp"

MovingAverager::MovingAverager(std::string id, size_t windowSize) : Subscriber(id), windowSize(windowSize) {
}

Subscriber *MovingAverager::clone() const {
    return new MovingAverager(*this);
}

void MovingAverager::signal(Message message) {
messages.push_back(message);
}

int MovingAverager::read() const {
if(messages.size() == 0){
    return 0;
}
    int result  = 0;
    int count = 0;
    if(messages.size()<windowSize){
        for(auto message : messages){
            result+=message.data;
            count++;
        }
        return result/count;
    }
    else{
        for (size_t last_element = messages.size()-1, times = windowSize; times > 0; times--, --last_element) {
            result += messages[last_element].data;
        }
        result = result/(int)windowSize;
        return result;
    }

}
