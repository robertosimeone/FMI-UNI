#pragma once
#include <iostream>
#include "Object.hpp"
#include <vector>
class Document : public Object {
public:
    Document(const std::string& name, const std::string& location, const std::string& extension);

    void write_line(const std::string& line);

    std::string read_line();
    std::string read_line(const unsigned line);
    bool operator!=( const Comparable * comparable) const override;
    bool operator==( const Comparable * comparable) const override;
    std::string to_string() const override;
    void from_string(const std::string & ) override;
    std::string debug_print() const override;
    Object * clone() const override;

private:
    std::vector<std::string> lines;
    int last_read;
    size_t get_lines_count() const;
    std::string fromIndexToSymbol(std::string in, int &index,  char symbol, int& next_index) const;
};