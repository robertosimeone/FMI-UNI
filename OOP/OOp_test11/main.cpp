#include <iostream>
#include "NamedObject.hpp"
#include "NamedObjectArray.hpp"
int main() {
    NamedObject<int> object("lekesha",2,3);
    NamedObject<int> object1("tosho",1,1);
  // cout<<object.getName()<<endl;

  //  cout<<object1.getName()<<" "<<object1.getID()<<" "<<object1.getObject();
    NamedObjectArray<int> container;
    container.add(object);
    container.add(object1);
    cout<<container[0].getName() << " " <<container[0].getID() << " " << container[0].getObject()<<endl;
    cout<<container[1].getName() << " " <<container[1].getID() << " " << container[1].getObject();
    NamedObjectArray<int> container1 = container;
    cout<<endl;
    cout<<container1[0].getName() << " " <<container1[0].getID() << " " << container1[0].getObject()<<endl;
    cout<<container1[1].getName() << " " <<container1[1].getID() << " " << container1[1].getObject();

    return 0;
}
