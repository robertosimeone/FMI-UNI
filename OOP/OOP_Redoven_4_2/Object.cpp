//
// Created by Robert Borisov on 3.06.21.
//

#include "Object.hpp"

void Object::setName(std::string name) {
this->name = name;
}

void Object::setLocation(std::string location) {
this->location = location;
}

void Object::setExtension(std::string extension) {
this->extension = extension;
}

std::string Object::get_name() const {
    return this->name;
}

std::string Object::get_location() const {
    return this->location;
}

std::string Object::get_extension() const {
    return this->extension;
}

std::string Object::get_fullpath() const {

    return std::string(location+'/'+name+'.'+extension);
}

Object::Object(const std::string &name, const std::string &location, const std::string &extension) {
this->name = name;
this->location = location;
this->extension = extension;
}




