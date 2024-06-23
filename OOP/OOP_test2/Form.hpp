//
// Created by Robert Borisov on 16.06.21.
//

#ifndef OOP_TEST2_FORM_HPP
#define OOP_TEST2_FORM_HPP
#include <iostream>
using namespace std;


class Form {
private:
    string color;
public:
    Form(string color = "");

   virtual  double Area() const  = 0;
   virtual string shapetype() const = 0;
   string getColor() const;
   virtual Form* clone() const = 0;
   virtual ~Form() = default;
};


#endif //OOP_TEST2_FORM_HPP
