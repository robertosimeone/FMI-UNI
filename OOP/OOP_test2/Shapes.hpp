//
// Created by Robert Borisov on 16.06.21.
//

#ifndef OOP_TEST2_SHAPES_HPP
#define OOP_TEST2_SHAPES_HPP
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Form.hpp"
#include <vector>

class Shapes {
private:
vector<Form*> shapes;
public:
    Shapes() = default;
    Shapes(const Shapes& rhs);
    Shapes & operator=(const Shapes& rhs);
    void addCircle(Circle * circle);
    void addRectangle(Rectangle * rectangle);
    double AreaOfRectanles() const;
    double AreaOfCircles() const;
    Form &  shapeAtIndex(size_t index) const;
    ~Shapes();

};


#endif //OOP_TEST2_SHAPES_HPP
