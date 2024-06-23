#pragma once
#include <iostream>
#include "Comparable.hpp"
#include "Debug.hpp"
#include "Serializable.hpp"
class Object :  public Comparable, public Serializable ,  public Debug {
public:
    Object(const std::string& name, const std::string& location, const std::string& extension);
    virtual Object * clone() const = 0;


    std::string get_name() const;
    std::string get_location() const;
    std::string get_extension() const;
    std::string get_fullpath() const;
    void setName(std::string name);
    void setLocation(std::string location);
    void setExtension(std::string extension);
    virtual  ~Object() =default;

    std::string name;
private:
    std::string extension;
    std::string location;
};