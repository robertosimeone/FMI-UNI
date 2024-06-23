/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021 *
* @author Robert Borisov
* @idnumber 62529
* @task 1
* @compiler clang  */
using namespace std;
#include <iostream>

#include "Duelist.hpp"
Deck& Duelist::getDeck() {
    return deck;
}
Duelist::Duelist(string name){
    this->name = name;
}

bool Duelist::saveDeckToFile(string filename) {//check for new lines when u print in the file
    ofstream file(filename);
    char separator = '|';
    if(file){
        file<<this->getDeck().getName()<<separator<<this->getDeck().getTotalCount()<<separator<<this->getDeck().getMonstersCount()<<separator<<this->getDeck().getSpellsCount()<<separator<<this->getDeck().getPendulumsCount()<<endl;
        for(auto monster : this->getDeck().getCards()){
            if(monster->getCardType() == "monster"){
                file<< *dynamic_cast<MonsterCard*>(monster);
            }
        }
        for(auto magic : this->getDeck().getCards()) {
            if (magic->getCardType() == "magic") {
                file << *dynamic_cast<MagicCard*>(magic);
            }
        }
            for(auto pendulum : this->getDeck().getCards()) {
                if (pendulum->getCardType() == "pendulum") {
                    file << *dynamic_cast<PendulumCard*>(pendulum);
                }
            }
        file.close();
        return true;
    }
    else{
        file.close();
        return false;
    }
}

bool Duelist::loadDeckFromFile(string filename) {
    ifstream file(filename);
    if(file){
        char trash;
        size_t monstercount = 0 ;
        size_t spellscount  = 0;
        size_t pendulumscount = 0;
        size_t cards_count = 0;
        string deckname;
        getline(file,deckname,'|');
        file>>cards_count>>trash>>monstercount>>trash>>spellscount>>trash>>pendulumscount;
        this->getDeck().setName(deckname);
        getline(file,deckname,'\n');
        MonsterCard monster;
        MagicCard magic;
        PendulumCard pendulum;
        for(size_t i = 0 ;i<monstercount;++i){
            file>>monster;
            this->getDeck().addCard(&monster);
        }
        for(size_t i = 0 ;i<spellscount;++i){
            file>>magic;
            this->getDeck().addCard(&magic);
        }
        for(size_t i = 0 ;i<pendulumscount;++i){
            file>>pendulum;
            this->getDeck().addCard(&pendulum);
        }
        file.close();
        return true;
    }else {

        file.close();
        return false;
    }
}

string Duelist::duel( Duelist &other) {
    if(this->getDeck().getTotalCount() == other.getDeck().getTotalCount()){
        this->getDeck().shuffleDeck();
        other.getDeck().shuffleDeck();
        size_t count_player1 = 0;
        size_t count_player2 = 0;
            for(size_t i  = 0 ;i<this->getDeck().getTotalCount();++i) {
                    if ((*this->getDeck().getCards()[i]) > (*other.getDeck().getCards()[i])) {
                        count_player1++;
                    }
                    if ((*this->getDeck().getCards()[i]) < (*other.getDeck().getCards()[i])) {
                        count_player2++;
                    }
            }


            if(count_player1==count_player2){
                return "Draw!";
            }
            else if(count_player1>count_player2){
                return "Player:"+this->name+" has won the duel.Congratulaions!";
            }
            else {
                return "Player: " + other.name +" has won the duel.Congratulations!";
            }
    }
    else{
        return "The decksizes do not match!";
    }
}
