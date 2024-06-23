//
// Created by Robert Borisov on 7.05.21.
//

#include "TeamLead.hpp"

TeamLead::TeamLead(const string &name, double salary) : Developer(name) {
    setInitialSalary(salary);
    setLeader(this);

}

vector<Developer*> TeamLead::getTeam() {
    return developers;
}

void TeamLead::addDeveloperToTeam(Developer * developer, double salary) {
    developer->setLeader(this);
    developer->setSalary(salary);
    developers.push_back(developer);
}

void TeamLead::increaseTeamSalariesBy(double amount) {
        for(size_t i  = 0;i<developers.size();++i){
                developers[i]->increaseSalaryBy(amount);
        }
}

void TeamLead::removeDeveloperFromTeam(const string & name) {
    size_t index  = -1;
for(size_t i = 0 ; i < developers.size();++i){
    if(developers[i]->getName() == name){
        index = i;
    }
    if(index!=-1){
        developers[index]->setLeader(nullptr);
        developers.erase(developers.begin() + index);

    }
}
}

void TeamLead::decreaseTeamSalariesBy(double amount) {
    for(size_t i  = 0;i<developers.size();++i){
        developers[i]->decreaseSalaryBy(amount);
    }
}

void TeamLead::addLeavingRequest(const LeavingRequest & leavingRequest) {
    leaving_requests.push_back(leavingRequest);


}

void TeamLead::addPromotionalRequest(const PromotionRequest & promotionRequest) {
 promo_requests.push_back(promotionRequest);
}

void TeamLead::fulfillLeavingRequests() {
for(size_t i = 0 ; i<leaving_requests.size();++i){
    string fired = leaving_requests[i].getSender();
    this->removeDeveloperFromTeam(fired);
    }
}

void TeamLead::fulfillPromotionRequests() {
    for(size_t i = 0;i<promo_requests.size();++i){
            string promoted = promo_requests[i].getSender();
            double increase = promo_requests[i].getAmount();
            for(size_t j = 0 ;j<developers.size();++j) {
                if(developers[i]->getName() == promoted) {
                    developers[i]->increaseSalaryBy(increase);
                    break;
                }
            }
    }

}
