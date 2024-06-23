//
// Created by Robert Borisov on 16.06.21.
//

#ifndef OOP_TEST2_CIRCLE_HPP
#define OOP_TEST2_CIRCLE_HPP
#include "Form.hpp"

class Circle: public Form {
private:
    const double pi = 3.14;
    double radius;


public:
    Circle(double radius, string color);
    double getRadius() const;
    double Area() const override;
    Form* clone() const override;
    string shapetype() const override;


};


#endif //OOP_TEST2_CIRCLE_HPP
