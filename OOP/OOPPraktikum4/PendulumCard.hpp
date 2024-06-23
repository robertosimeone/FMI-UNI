
/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler  clang */

#ifndef OOPPRAKTIKUM3_PENDULUMCARD_HPP
#define OOPPRAKTIKUM3_PENDULUMCARD_HPP

#include "MonsterCard.hpp"
#include "MagicCard.hpp"
using namespace std;
#include <iostream>
class PendulumCard : public MonsterCard,public MagicCard{
    size_t scale;
public:
    PendulumCard(string name = "", string effect = "",size_t rarity  = 0,size_t attack = 0,size_t defense = 0, size_t scale = 0,Type type = buff);
    PendulumCard(const PendulumCard& rhs);
    friend istream & operator>>(istream & is , PendulumCard& );
    friend ostream & operator<<(ostream & out, const PendulumCard&);
    Card * clone() const override;
    string getCardType() const override;
    ~PendulumCard() override = default;
};


#endif //OOPPRAKTIKUM3_PENDULUMCARD_HPP
