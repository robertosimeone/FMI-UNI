//
// Created by Robert Borisov on 30.05.21.
//

#include "Subscriber.hpp"

Subscriber::Subscriber(std::string id) : id(id) {

}

 std::string Subscriber::getID() const {
    return this->id;
}

