/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler  clang */
#include <iostream>
#include "Duelist.hpp"
#include <fstream>

using namespace  std;
int main() {
    Duelist fist ("Robi");
    //ifstream file("Text.txt");
    //ofstream file2("Output.txt");
    cout<<fist.loadDeckFromFile("Text.txt")<<endl;
   // cout<<fist.getDeck().getTotalCount() <<" "<<fist.getDeck().getMonstersCount()<<" "<<fist.getDeck().getSpellsCount()<<" "<<fist.getDeck().getPendulumsCount();
    //fist.saveDeckToFile("Output.txt");
    Duelist sec("Bobi");
    cout<<sec.loadDeckFromFile("Text.txt")<<endl;

    MonsterCard tosho("Big Tosho.","Kill glavniq",2,2,2);

    MagicCard glaven("glaven","kill tosho",1,Type::spell);
    cout<<fist.duel(sec)<<endl;
    PendulumCard pend ("pend","kill" , 1,1,1,1,Type::trap);
    cout<<"Number of monster cards : "<<fist.getDeck().getMonstersCount()<<endl;
    cout<<"Number of magic cards : "<<fist.getDeck().getSpellsCount()<<endl;
    cout<<"Number of pendulum cards : "<<fist.getDeck().getPendulumsCount()<<endl;
    fist.saveDeckToFile("Output.txt");
    cout<<"Number of cards  after adding : "<<fist.getDeck().getTotalCount() << endl;
    fist.getDeck().clearDeck();
    cout<<"Number of cards after clearing the deck : "<<fist.getDeck().getTotalCount()<< endl;
    fist.getDeck().addCard(&pend);
    fist.getDeck().addCard(&pend);
    fist.getDeck().addCard(&glaven);
    fist.getDeck().addCard(&tosho);
    PendulumCard pends("Sineok magiosnik","Kill all.",1,1,1,1,Type::trap);
    fist.getDeck().changeCard(1,&pends);
    fist.getDeck().changeCard(3,&pends);
    cout<<"Number of cards after adding  cards : " << fist.getDeck().getTotalCount()<<endl;
    cout<<"Expected number of monstercards : 1 Actual number of monstercards : "<<fist.getDeck().getMonstersCount()<<endl;
    cout<<"Expected number of magiccards : 1 Actual number of magiccards : "<<fist.getDeck().getSpellsCount()<<endl;
    cout<<"Expected number of pendulumcards : 2 Actual number of pendulumcards : "<<fist.getDeck().getPendulumsCount()<<endl;
    cout<<fist.duel(sec);
    fist.saveDeckToFile("Output.txt");
    MagicCard magic = glaven;
    cout<<endl<<magic;
    MonsterCard monster = tosho;
    cout<<monster;
    PendulumCard pendulum = pend;
    cout<<pendulum;
}
