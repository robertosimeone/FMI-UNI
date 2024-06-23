/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler clang */

#include "MonsterCard.hpp"
MonsterCard::MonsterCard(string name, string effect,size_t rarity, size_t attack, size_t defense) : Card(name,effect,rarity){
    this->attack = attack;
    this->defense = defense;
}

MonsterCard& MonsterCard::operator= (const MonsterCard& other) {
    if (this != &other) {
        setName(other.getName());
        setEffect(other.getEffect());
        setRarity(other.getRarity());
        this->attack = other.attack;
        this->defense = other.defense;
    }
    return *this;
}

istream &operator>>(istream &is, MonsterCard & card) {
    string name;
    string effect;
    size_t rarity;
    char trash;
    getline(is,name,'|');
    getline(is,effect,'|');
    is>>rarity;
    is>>trash;
    is>>card.attack;
    is>>trash;
    is>>card.defense;
    card.setName(name);
    card.setEffect(effect);
    getline(is,effect , '\n');
    card.setRarity(rarity);
    return is;


}

ostream &operator<<(ostream &out, const MonsterCard & card) {
    string between  = "|";
    string outstring = card.getName() + between +card.getEffect()+between;
    out<<outstring<<card.getRarity()<<between<<card.attack<<between<<card.defense<<endl;
    return out;
}

void MonsterCard::setAttack(size_t attack) {
    this->attack = attack;
}

void MonsterCard::setDefense(size_t defense) {
    this->defense = defense;
}

size_t MonsterCard::getAttack() const {
    return this->attack;
}

size_t MonsterCard::getDefense() const {
    return this->defense;
}

Card *MonsterCard::clone() const {
    return new MonsterCard(*this);
}

MonsterCard::MonsterCard(const MonsterCard &rhs)  : Card(rhs){
this->defense = rhs.defense;
this->attack = rhs.attack;
}

string MonsterCard::getCardType() const {
    return "monster";
}
