/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler clang */

#include "PendulumCard.hpp"
PendulumCard::PendulumCard(string name, string effect,size_t rarity, size_t attack, size_t defense, size_t scale, Type type) :
        MagicCard(name,effect,rarity,type) , MonsterCard(name,effect,rarity,attack,defense) , Card(name,effect,rarity){
    this->scale = scale;
}

istream &operator>>(istream &is, PendulumCard & card) {
    string name;
    string effect;
    Type type;
    size_t rarity;
    size_t scale;
    string typestring;
    char trash;
    size_t attack;
    size_t defense;
    getline(is,name,'|');
    getline(is,effect,'|');
    is>>rarity>>trash>>attack>>trash>>defense>>trash>>scale>>trash>>typestring>>trash;
    type = card.fromstringtotype(typestring);
    card.setEffect(effect);
    card.setName(name);
    card.setType(type);
    card.setAttack(attack);
    card.setDefense(defense);
    card.setRarity(rarity);
    card.scale = scale;
    return is;
}

ostream &operator<<(ostream &out, const PendulumCard & card) {
    string between = "|";
    string typestring = card.fromtypetostring(card.getType());
    out<<card.getName()<<between<<card.getEffect()<<between<<card.getRarity()<<between<<card.getAttack()<<between<<card.getDefense()<<between<<card.scale<<between<<typestring;
    out<<endl;
    return out;
}

Card *PendulumCard::clone() const {
    return new PendulumCard(*this);

}

PendulumCard::PendulumCard(const PendulumCard &rhs) : MonsterCard(rhs) , MagicCard(rhs) , Card(rhs) {
this->scale = rhs.scale;
}

string PendulumCard::getCardType() const {
    return "pendulum";
}
