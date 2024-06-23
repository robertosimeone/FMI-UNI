//
// Created by Robert Borisov on 7.05.21.
//

#include "Developer.hpp"
#include "TeamLead.hpp"


Developer::Developer(const string &name) : salary(0) , leader(nullptr){
this->name = name;
}

string Developer::getName() const {
    return this->name;
}

double Developer::getSalary() const {
    return salary;
}

void Developer::setInitialSalary(double amount) {
    if(salary == 0)
    salary = amount;
}

TeamLead *Developer::getTeamLead() const {
    return leader;
}

void Developer::sendLeavingRequest() {
    if(leader!= nullptr)
 leader->addLeavingRequest(LeavingRequest(this->name));
}

void Developer::sendPromotionRequest(double amount) {
    if(leader!= nullptr)
leader->addPromotionalRequest(PromotionRequest(this->name,amount));
}

void Developer::setSalary(double salary) {
    this->salary  = salary;

}

void Developer::setLeader(TeamLead * leader) {
this->leader = leader;
}

void Developer::increaseSalaryBy(double amount) {
 salary +=amount;
}

void Developer::decreaseSalaryBy(double amount) {
if(salary - amount >=0)
    salary-=amount;
}
