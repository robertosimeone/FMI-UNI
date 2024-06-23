//
// Created by Robert Borisov on 7.05.21.
//

#ifndef INC_2_PROMOTIONREQUEST_HPP
#define INC_2_PROMOTIONREQUEST_HPP
#include "Request.hpp"

class PromotionRequest : public Request {
    double amount;
public:
    PromotionRequest(const string & sender, double amount);
    double getAmount() const;


};


#endif //INC_2_PROMOTIONREQUEST_HPP
