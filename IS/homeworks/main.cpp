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

bool binarySearch(int arr[],int element,int size) {
    int l, r,middle;
    r = size-1;
    l = 0;
    while(l<=r){
        middle = (l+r)/2;
        if(arr[middle] == element)
            return true;
        if(arr[middle]>element)
            r = middle-1;
        else
            l=middle+1;
    }
    return false;
}
int main() {

cout << "Helo";





}
