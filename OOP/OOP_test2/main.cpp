#include <iostream>
#include "Shapes.hpp"
int main() {
    Shapes shapes;
    Circle circle(2, "pink");
    shapes.addCircle(&circle);
    auto *circle1 = dynamic_cast<Circle *>(&shapes.shapeAtIndex(0));
    cout << circle1->getRadius();
   Rectangle rectangle(5,2,"white");
   shapes.addRectangle(&rectangle);
    auto * rectangle1 =  dynamic_cast<Rectangle*>(&shapes.shapeAtIndex(1));
    cout << endl << rectangle1->Area() << " " << rectangle1->getLenght() << "  " << rectangle1->getWidth() << " "
         << rectangle1->getColor();
    Rectangle rectangle2(3, 2, "white");
    shapes.addRectangle(&rectangle2);
    cout << endl << 2 * 2 * 3.14;
    cout << endl << shapes.AreaOfRectanles();
    return 0;
}

