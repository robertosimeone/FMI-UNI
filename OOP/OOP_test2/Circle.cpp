//
// Created by Robert Borisov on 16.06.21.
//

#include "Circle.hpp"

double Circle::getRadius() const {
    return radius;
}

double Circle::Area() const {
   double result = 0;
   result = pi*radius*radius;
   return result;
}

Circle::Circle(double radius, string color): Form(color) {
this->radius=  radius;
}

Form *Circle::clone() const {
    return new Circle(*this);
}

string Circle::shapetype() const {
    return string("circle");
}

