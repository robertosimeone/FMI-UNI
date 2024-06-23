/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler clang */

#ifndef OOPPRAKTIKUM3_CARD_HPP
#define OOPPRAKTIKUM3_CARD_HPP

#include <string>
using namespace std;
class Card {
    string name;
    string effect;
    size_t rarity;
public:
    Card(string,string,size_t rarity);
    Card(const Card & rhs);
    void setRarity(size_t rarity);
    void setName(string name);
    void setEffect(string effect);
    string getName() const;
    string getEffect() const;
    size_t getRarity() const;
    bool operator>(const Card & rhs) const;
    bool operator<(const Card & rhs) const;
    virtual ~Card() = 0;
    virtual Card* clone() const  = 0;
    virtual string getCardType() const  = 0;
};



#endif //OOPPRAKTIKUM3_CARD_HPP
