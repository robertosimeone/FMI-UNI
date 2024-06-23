//
// Created by Robert Borisov on 7.05.21.
//


#include "PromotionRequest.hpp"

PromotionRequest::PromotionRequest(const string &sender, double amount) : Request("I want a raise!",sender) {
this->amount = amount;
setID(this->getCount());
}

double PromotionRequest::getAmount() const {
    return this->amount;
}
