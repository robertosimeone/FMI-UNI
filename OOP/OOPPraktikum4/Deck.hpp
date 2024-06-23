/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler  clang */

#ifndef OOPPRAKTIKUM3_DECK_HPP
#define OOPPRAKTIKUM3_DECK_HPP
#include <string>
#include <vector>
#include "MonsterCard.hpp"
#include "MagicCard.hpp"
#include "PendulumCard.hpp"
using namespace std;

class Deck {

    string name;
    vector<Card*> cards;

public:
    Deck(string name = "");
    Deck(const Deck& rhs);
    Deck& operator=(const Deck& rhs);
    ~Deck();
    void setName(string name);
    string getName() const;
    size_t getMonstersCount() const;
    size_t getSpellsCount() const;
    size_t getPendulumsCount() const;
    size_t getTotalCount() const;
    vector<Card*> getCards() ;
    void addCard( Card * card);
    void changeCard(size_t index,Card * card);
    void clearDeck();
    void shuffleDeck();
    //display deck

};


#endif //OOPPRAKTIKUM3_DECK_HPP
