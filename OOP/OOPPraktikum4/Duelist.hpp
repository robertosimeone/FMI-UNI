/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler  clang */

#ifndef OOPPRAKTIKUM3_DUELIST_HPP
#define OOPPRAKTIKUM3_DUELIST_HPP
#include <string>
#include "Deck.hpp"
#include <iostream>
#include <fstream>
using namespace std;

class Duelist{
    string name;
    Deck deck;

public:
    Duelist(string name = "");
    Deck& getDeck();
    bool saveDeckToFile(string filename);
    bool loadDeckFromFile(string filename);
    string duel( Duelist & other);

};


#endif //OOPPRAKTIKUM3_DUELIST_HPP