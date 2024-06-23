//
// Created by Robert Borisov on 16.06.21.
//

#include "Shapes.hpp"

void Shapes::addCircle(Circle *circle) {
shapes.push_back(circle->clone());
}

void Shapes::addRectangle(Rectangle *rectangle) {
    shapes.push_back(rectangle->clone());
}

double Shapes::AreaOfRectanles() const {
    double result = 0;
    for(auto shape : shapes){
        if(shape->shapetype() == "rectangle" ){
            Rectangle * rectangle = dynamic_cast<Rectangle*>(shape);
            result+=rectangle->Area();
        }
    }
    return result;
}

double Shapes::AreaOfCircles() const {
    double result = 0;
    for(auto shape : shapes){
        if(shape->shapetype() == "circle" ){
            Circle * circle = dynamic_cast<Circle*>(shape);
            result+=circle->Area();
        }
    }
    return result;
}

Form& Shapes::shapeAtIndex(size_t index) const {
    if(index >=0 and index<shapes.size()){
        return *shapes[index];
    }

}

Shapes::~Shapes() {
    for(auto shape : shapes){
        delete shape;
    }

}

Shapes::Shapes(const Shapes &rhs) {
for(auto shape : rhs.shapes){
    this->shapes.push_back(shape->clone());
}
}

Shapes &Shapes::operator=(const Shapes &rhs) {
   if(this!=&rhs){
       for(auto shape : rhs.shapes){
           this->shapes.push_back(shape->clone());
       }
   }
   return *this;
}
