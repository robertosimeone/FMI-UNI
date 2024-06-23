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

int arr[] = {1,2,10,12,15,17};
int size = sizeof (arr)/sizeof(arr[0]) ;
if(binarySearch(arr,17,size))
    cout << "Found it";
else
    cout << "not found";





}
