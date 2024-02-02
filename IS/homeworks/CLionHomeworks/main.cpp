#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <set>
#include <fstream>
#include <limits.h>
#include <cmath>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
class A{
public:

    string a;
};
int main() {

 uint32_t arr [2][3] = {};
 uint32_t arr1[3] = {3,4,5};
 for(int i = 0 ; i < sizeof(arr1)/sizeof(arr1[0]);i++){
     arr[0][i] = arr1[i];

 }


 for(int i =0 ; i < 3;i++){
     cout << arr[0][i]  << " ";

 }



   }
