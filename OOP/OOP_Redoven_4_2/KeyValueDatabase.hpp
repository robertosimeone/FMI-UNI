
#pragma once
#include <iostream>
#include <utility>
#include "Object.hpp"
#include <vector>
class KeyValueDatabase : public Object{
public:
    KeyValueDatabase(const std::string& name, const std::string& location, const std::string& extension);

    void add_entry(const std::pair<std::string, int>& entry);
    int get_value(const std::string& key) const;
    bool operator!=(const Comparable* comparable) const override;
    bool operator==(const Comparable* comparable) const override;
    void from_string(const std::string&) override;
    std::string to_string() const  override;
    std::string debug_print() const override;
    Object * clone() const  override;

private:
    std::vector<std::pair<std::string,int >> keys_values;
    std::string fromIndexToSymbol(std::string in, int &index,  char symbol, int& next_index) const;
    int toInt(std::string) const;
};
