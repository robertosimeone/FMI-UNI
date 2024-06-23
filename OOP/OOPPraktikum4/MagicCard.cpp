/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
        * Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler clang */
#include "MagicCard.hpp"
#include <iostream>
using namespace std;
MagicCard::MagicCard(string name, string effect,size_t rarity, Type type) :Card(name,effect , rarity){
    this->type = type;
}

MagicCard& MagicCard::operator=(const MagicCard& other) {
    if (this != &other) {
        setName(other.getName());
        setEffect(other.getEffect());
        setRarity(other.getRarity());
        this->type = other.type;
    }
    return *this;
}


Type MagicCard::fromstringtotype(string effect) const{
    if(effect == "TRAP")
        return Type::trap;
    if(effect == "BUFF")
        return Type::buff;
    return Type::spell;
}

void MagicCard::setType(Type type) {
    this->type = type;
}
ostream &operator<<(ostream &out, const MagicCard & card) {
    string between = "|";

    out<<card.getName()<<between<<card.getEffect()<<between<<card.getRarity()<<between<<card.fromtypetostring(card.type)<<endl;
    return out;
}

istream &operator>>(istream &is, MagicCard & card) {
    string name;
    string effect;
    Type type;
    char trash;
    size_t rarity;
    string typestring;
    getline(is, name, '|');
    getline(is, effect, '|');
    is>>rarity>>trash;
    getline(is, typestring, '\n');
    type = card.fromstringtotype(typestring);
    card.setEffect(effect);
    card.setName(name);
    card.setType(type);
    card.setRarity(rarity);
    return is;
}


string MagicCard::fromtypetostring(Type type) const {
    string outstring = "";
    if(type==Type::spell)
        outstring = "SPELL";
    if(type == Type::buff )
        outstring = "BUFF";
    if(type==Type::trap)
        outstring = "TRAP";
    return outstring;
}

Type MagicCard::getType() const {
    return this->type;
}

Card *MagicCard::clone() const {
    return new MagicCard(*this);
}

MagicCard::MagicCard(const MagicCard &rhs): Card(rhs)  {
    this->type = rhs.type;
}

string MagicCard::getCardType() const {
    return "magic";
}
