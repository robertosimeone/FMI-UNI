//
// Created by Robert Borisov on 16.06.21.
//

#include "Rectangle.hpp"

double Rectangle::getLenght() const {
    return lenght;
}

double Rectangle::getWidth() const {
    return width;
}

double Rectangle::Area() const {
 double result = 1;
 result = width*lenght;
 return result;
}

Rectangle::Rectangle(double width, double lenght, string color): Form(color) {
this->width = width;
this->lenght = lenght;
}

string Rectangle::shapetype() const {
    return std::string("rectangle");
}

Form *Rectangle::clone() const  {
    return new Rectangle(*this);
}
