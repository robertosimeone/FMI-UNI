//
// Created by Robert Borisov on 16.06.21.
//

#ifndef OOP_TEST11_NAMEDOBJECT_HPP
#define OOP_TEST11_NAMEDOBJECT_HPP
#include <iostream>
using namespace std;
template <class T>
class NamedObject {
private:
    char *  name;
     size_t id;
     T object;
public:
    NamedObject(char * name  = "", size_t id = 0, T object = T())  : id(id),object(object){
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);

    }
    const char * getName() const {
        return name;
    }
    size_t getID() const{
        return id;
    }
    const T getObject() const{
        return object;
    }
    NamedObject<T>* clone() const{
        return new NamedObject<T>(*this);
    }
    NamedObject(const NamedObject<T> &rhs): id(rhs.id) , object(rhs.object){
        this->name = new char[strlen(rhs.name)];
        strcpy(this->name,rhs.name);
    }
    NamedObject& operator=(const NamedObject<T> &rhs){
        if(this!=&rhs){
            delete[]name;
            this->name = new char[strlen(rhs.name)];
            strcpy(this->name,rhs.name);
            this->id = rhs.id;
            this->object = rhs.object;
        }
        return *this;
    }
    ~NamedObject(){
        delete[] name;
    }

};


#endif //OOP_TEST11_NAMEDOBJECT_HPP
