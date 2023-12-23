#include <iostream>
#include <set>
#include <vector>
using namespace std;
int main(){
    set<vector<int> > visited;
    vector<int>a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    visited.insert(a);
    a[0] = 4;
    visited.insert(a);
    set<vector<int> >::iterator itr;
    cout << "\nThe set s1 is : \n";
    for (itr = visited.begin(); itr != visited.end(); itr++) {
        for(int i = 0; i < itr->size();i++){
            cout << (*itr)[i] << " ";

        }
        cout << endl;
    }
    cout << endl;
}