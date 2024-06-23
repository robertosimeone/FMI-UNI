using namespace std;
#include <iostream>
#include "Document.hpp"
#include "KeyValueDatabase.hpp"
int main() {

    std::string read1("Name\nLocation\nExtension\nkey1:1\nkey2:2\nkey3:3\n");
    std::string read2("Name\nLocation\nExtension\nkey1.1:1\nkey2.1:2\nkey:3.1:3\n");
    KeyValueDatabase keyValueDatabase("ss","ss","ss");
    keyValueDatabase.from_string(read1);
   Document document("ss","ss","ss");
   std::string string1("kur");
   document.write_line(string1);
   document.read_line();




   // std::string key = keyValueDatabase.to_string();
   // cout<<key;
   // std::pair<std::string,int> pair;
   // pair.first = "key1";
   // pair.second = 1;
    //keyValueDatabase.add_entry(pair);
  // keyValueDatabase.get_value("key10");

    //std::string to_string = keyValueDatabase.to_string();
    //cout<<to_string;
    //cout<<"yes";

 //   cout<<document.read_line();
  //  cout<<document.read_line();
   // cout<<document.read_line();
  //  cout<<document.read_line();
  //std::string out ("");
 // out = document.debug_print();
 // cout<<out;
   //r std::string out("");
  // out = document.to_string();
  //  std::cout<<out;
}
