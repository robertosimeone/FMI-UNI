//
// Created by Robert Borisov on 16.06.21.
//

#ifndef OOP_TEST2_RECTANGLE_HPP
#define OOP_TEST2_RECTANGLE_HPP
using namespace std;
#include "Form.hpp"
#include <iostream>

class Rectangle : public Form {
private:
double lenght;
double width;
public:
    Rectangle(double width, double lenght, string color);
  double getLenght() const;
  double getWidth() const;
  double Area() const override;
  string shapetype() const override;
  Form* clone() const override;





};


#endif //OOP_TEST2_RECTANGLE_HPP
