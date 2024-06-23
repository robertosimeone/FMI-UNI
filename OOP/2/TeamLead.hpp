//
// Created by Robert Borisov on 7.05.21.
//

#ifndef INC_2_TEAMLEAD_HPP
#define INC_2_TEAMLEAD_HPP
#include "Developer.hpp"
#include <vector>
#include "LeavingRequest.hpp"
#include "PromotionRequest.hpp"
class TeamLead: public Developer {
vector<Developer*> developers;
vector<LeavingRequest> leaving_requests;
vector<PromotionRequest> promo_requests;
public:
    TeamLead(const string &name, double);
    vector<Developer*> getTeam() ;
    void addDeveloperToTeam(Developer * , double);
    void removeDeveloperFromTeam(const string&);
    void increaseTeamSalariesBy(double );
    void decreaseTeamSalariesBy(double);
    void addLeavingRequest(const LeavingRequest&);
    void addPromotionalRequest(const PromotionRequest&);
    void fulfillLeavingRequests();
    void fulfillPromotionRequests();


};


#endif //INC_2_TEAMLEAD_HPP
