//
// Created by Robert Borisov on 7.05.21.
//

#include "LeavingRequest.hpp"

LeavingRequest::LeavingRequest(const string &sender) : Request("I want to leave!",sender){
    setID(this->getCount());
}
