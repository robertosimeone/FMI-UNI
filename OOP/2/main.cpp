#include <iostream>
#include "Developer.hpp"
#include "TeamLead.hpp"
using namespace  std;
int main() {
Developer d1("gosho");
d1.setSalary(2000);
//d1.increaseSalaryBy(1000);
cout<<d1.getSalary();

}
