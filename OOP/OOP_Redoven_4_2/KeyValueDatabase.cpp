//
// Created by Robert Borisov on 3.06.21.
//

#include "KeyValueDatabase.hpp"


KeyValueDatabase::KeyValueDatabase(const std::string &name, const std::string &location, const std::string &extension)
        : Object(name, location, extension) {

}

void KeyValueDatabase::add_entry(const std::pair<std::string, int> &entry) {
    for(auto key_value : keys_values){
        if(key_value.first == entry.first) {
           throw std::invalid_argument("Invalid argument");

        }
    }
    keys_values.push_back(entry);
}

int KeyValueDatabase::get_value(const std::string &key) const {
    for(auto key_value : keys_values){
        if(key_value.first == key){
            return key_value.second;
        }
    }
    throw std::invalid_argument("Invalid argument");


}

bool KeyValueDatabase::operator!=(const Comparable *comparable) const {
    Comparable * comparable1 = const_cast<Comparable*>(comparable);
    KeyValueDatabase* key_value = dynamic_cast<KeyValueDatabase*>(comparable1);
    if(key_value){
        KeyValueDatabase * keys_values_other = (KeyValueDatabase*)comparable;
        if(keys_values_other->keys_values.size()!=this->keys_values.size()){
            return true;
        }
        for(size_t i = 0 ; i<keys_values.size();++i){
            if(keys_values_other->keys_values[i].first != keys_values[i].first || keys_values_other->keys_values[i].second != keys_values[i].second)
                return true;
        }
        return false;
    }
    else {
        return false;
    }
}

bool KeyValueDatabase::operator==(const Comparable *comparable) const {
    return !(this->operator!=((KeyValueDatabase*) comparable));
}

void KeyValueDatabase::from_string(const std::string &kv_database) {
    if(kv_database.empty() || kv_database == "\n")
        return;
    int from = 0;
    int next_from = 0;
    this->keys_values.clear();
std::string name = this->fromIndexToSymbol(kv_database,from, '\n',next_from);
std::string location = this->fromIndexToSymbol(kv_database,from, '\n',next_from);
std::string extension = this->fromIndexToSymbol(kv_database,from, '\n',next_from);
    setName(name);
    setExtension(extension);
    setLocation(location);
    while(from!=(int)(kv_database.size())){
        std::string key = this->fromIndexToSymbol(kv_database,from,':',next_from);
        std::string value = this->fromIndexToSymbol(kv_database,from,'\n',next_from);
        std::pair<std::string, int > key_value;
        key_value.first = key;
        key_value.second = this->toInt(value);
        keys_values.push_back(key_value);
    }

}

std::string KeyValueDatabase::to_string() const {
    std::string to_return;
    to_return = get_name()  + '\n' + get_location() + '\n' + get_extension()+'\n';
    for(auto key_value : keys_values){
        std::string toString = std::to_string(key_value.second);
        to_return += key_value.first;
        to_return += ':';
        to_return += toString;
        to_return += '\n';
    }
    return to_return;
}

std::string KeyValueDatabase::fromIndexToSymbol(std::string in, int &index, char symbol, int &next_index) const {
    std::string result;
    for(int i = index; in[i]!=symbol;i++){
        result+=in[i];
        next_index = i;
    }
    next_index +=2;
    index = next_index;
    return result;
}

int KeyValueDatabase::toInt(std::string convert) const {
    int result = 0;
    for(int i = 0 ;convert[i]!='\0';i++){
        result*=10;
        result += convert[i]-48;
    }
    return result;
}

std::string KeyValueDatabase::debug_print() const {
    std::string result;
    for(auto key_value : keys_values){
        result+='{';
        result+=key_value.first;
        result+=':';
        result+=std::to_string(key_value.second);
        result+='}';
        result+='\n';
    }

    return result;
}

Object *KeyValueDatabase::clone() const {
    return new KeyValueDatabase(*this);
}


