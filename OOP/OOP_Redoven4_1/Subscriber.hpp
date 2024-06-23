//
// Created by Robert Borisov on 30.05.21.
//
#include "Message.hpp"
#ifndef OOP_REDOVEN4_1_SUBSCRIBER_HPP
#define OOP_REDOVEN4_1_SUBSCRIBER_HPP
#include <string>
#include <vector>
#include <iostream>

class Subscriber {
public:
    Subscriber(std::string);
    std::string getID() const;
    virtual void signal(Message) = 0;
    virtual int read() const = 0;
    virtual Subscriber* clone() const = 0;
    virtual ~Subscriber() = default;



    const std::string id;
protected:
    std::vector<Message>messages;
};


#endif //OOP_REDOVEN4_1_SUBSCRIBER_HPP
