//
// Created by Robert Borisov on 3.06.21.
//

#ifndef OOP_REDOVEN_4_2_SERIALIZABLE_HPP
#define OOP_REDOVEN_4_2_SERIALIZABLE_HPP
#include <iostream>

class Serializable {
public:
virtual std::string to_string() const = 0;
virtual void from_string(const std::string  &) = 0;
virtual ~Serializable() = default;
};


#endif //OOP_REDOVEN_4_2_SERIALIZABLE_HPP
