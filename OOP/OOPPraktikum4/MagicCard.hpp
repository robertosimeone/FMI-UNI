/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
    * @compiler  clang */

#pragma once

using namespace std;
#include "Card.hpp"
#include <string>
enum Type {
    spell = 0,
    buff = 1,
    trap = 2
};
class MagicCard : virtual public Card{
    Type type;
public:
    MagicCard(string name = "", string effect = "",size_t rarity = 0, Type type = buff);
    MagicCard& operator=(const MagicCard& other);
    MagicCard(const MagicCard& rhs);
    Type fromstringtotype(string) const ;
    string fromtypetostring(Type) const;
    friend  ostream& operator<<(ostream & out,const MagicCard &);
    friend istream& operator>>(istream& is,MagicCard&);
    void setType(Type type);
    Type getType()const;
    Card * clone() const override;
    string getCardType() const override;
    ~MagicCard() override = default;
};


