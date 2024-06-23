/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler clang */

#include "Card.hpp"
Card::Card(string name, string effect, size_t rarity) {
    this->name = name;
    this->effect = effect ;
    this->rarity = rarity;
}
void Card::setEffect(string effect) {
    this->effect = effect;
}
void Card::setName(string name) {
    this->name = name;
}
string Card::getEffect() const {
    return this->effect;
}
string Card::getName() const {
    return this->name;
}

size_t Card::getRarity() const {
    return this->rarity;
}

void Card::setRarity(size_t rarity) {
    this->rarity = rarity;
}
Card::~Card() {

}

bool Card::operator>(const Card &rhs) const {
    return rarity > rhs.rarity;
}

bool Card::operator<(const Card &rhs) const {
    return rarity<rhs.rarity;
}

Card::Card(const Card &rhs) {
this->rarity = rhs.rarity;
this->name = rhs.name;
this->effect =  rhs.effect;
}
