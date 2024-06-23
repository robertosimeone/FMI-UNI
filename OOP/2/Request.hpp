//
// Created by Robert Borisov on 7.05.21.
//

#ifndef INC_2_REQUEST_HPP
#define INC_2_REQUEST_HPP
#include <string>
using namespace std;

class Request {
string message;
string sender;
static int counter;
int ID;
public:
    Request(const string& message , const string & sender);
    string  getMessage() const;
    string getSender() const;
    int getCount() const;
    int getID() const;
    void setID(int id);

};


#endif //INC_2_REQUEST_HPP
