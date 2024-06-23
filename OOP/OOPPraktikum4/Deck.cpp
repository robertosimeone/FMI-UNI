/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler  clang */
#include <algorithm>
#include <random>
#include "Deck.hpp"
using namespace std;
#include <iostream>
size_t Deck::getMonstersCount() const {
    size_t count = 0 ;
    for(auto card : cards){
        if(card->getCardType() == "monster") {
            count++;
        }
    }
    return count;
}
size_t Deck::getSpellsCount() const {
    size_t count = 0 ;
    for(auto card : cards){
        if(card->getCardType() == "magic") {
            count++;
        }
    }
    return count;
}
size_t Deck::getPendulumsCount() const {
    size_t count = 0 ;
    for(auto card : cards){
        if(card->getCardType() == "pendulum")
            count++;
    }
    return count;
}
string Deck::getName() const {
    return this->name;
}
void Deck::clearDeck() {
    for(auto card : cards){
        delete card;
    }
    cards.clear();
}

void Deck::setName(string name) {
    this->name = name;

}

void Deck::addCard(Card *card) {
    cards.push_back(card->clone());
}

void Deck::changeCard(size_t index, Card *card) {
    if(cards[index]->getCardType() == card->getCardType()) {
        delete cards[index];
        cards[index] = card->clone();
    }

}

void Deck::shuffleDeck() {
std::random_device rd;
std::shuffle(cards.begin(),cards.end(),rd);
}

size_t Deck::getTotalCount() const {
    size_t all_count = 0;
    all_count = this->getMonstersCount()+this->getSpellsCount()+this->getPendulumsCount();
    return all_count;
}

vector<Card *> Deck::getCards() {
    return cards;
}

Deck::Deck(string name) {
this->name = name;
}

Deck::Deck(const Deck &rhs) {
this->name = rhs.name;
for(auto card:rhs.cards){
    this->cards.push_back(card->clone());
}
}

Deck &Deck::operator=(const Deck &rhs) {
    if(this!=&rhs){
        for(auto card:cards){
            delete card;
        }
        this->cards.clear();
        for(auto card:rhs.cards){
            this->cards.push_back(card->clone());
        }
    }
    return *this;
}
Deck::~Deck() {
for(auto card:cards){
    delete card;
}
}
