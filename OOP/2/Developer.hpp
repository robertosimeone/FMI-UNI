//
// Created by Robert Borisov on 7.05.21.
//

#ifndef INC_2_DEVELOPER_HPP
#define INC_2_DEVELOPER_HPP
#include <string>
#include "LeavingRequest.hpp"
#include "PromotionRequest.hpp"
using namespace  std;
class TeamLead;
class Developer {
string name;
double salary;
TeamLead * leader;
public:
    Developer(const string & name);
    string getName() const;
    double getSalary() const;
    TeamLead * getTeamLead() const;
    void setInitialSalary(double);
    void sendLeavingRequest();
    void sendPromotionRequest(double);
    void setSalary(double);
    void setLeader(TeamLead * leader);
    void increaseSalaryBy(double amount);
    void decreaseSalaryBy(double amount);






};


#endif //INC_2_DEVELOPER_HPP
