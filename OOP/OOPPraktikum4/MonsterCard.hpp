/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler  clang */
#ifndef OOPPRAKTIKUM3_MONSTERCARD_HPP
#define OOPPRAKTIKUM3_MONSTERCARD_HPP
#include "Card.hpp"
#include <string>
#include <iostream>
using namespace std;
class MonsterCard: virtual public Card {
    size_t attack;
    size_t defense;
public:
    MonsterCard(string name = "", string effect = "",size_t rarity = 0, size_t attack = 0, size_t defense = 0 );
    MonsterCard& operator= (const MonsterCard& other);
    MonsterCard(const MonsterCard& rhs);
    void setAttack(size_t);
    void setDefense(size_t);
    size_t  getAttack() const;
    size_t  getDefense() const;
    friend istream & operator>>(istream & is, MonsterCard &);
    friend ostream & operator<<(ostream & out, const MonsterCard&);
    Card* clone() const override;
    string getCardType() const override;
    ~MonsterCard() override = default;
};


#endif //OOPPRAKTIKUM3_MONSTERCARD_HPP

