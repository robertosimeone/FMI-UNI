//
// Created by Robert Borisov on 3.06.21.
//

#include "Document.hpp"

std::string Document::read_line() {
    if(lines.size() == 0)
       throw std::out_of_range("You are out of bounds");
    if(last_read+1<=lines.size()-1) {
        last_read++;
        return lines[last_read];
    }
    else{
        throw std::out_of_range("You are out of bounds");
    }
}

std::string Document::read_line(const unsigned int line) {
    if(line <= 0 || line>lines.size() ){
        throw std::out_of_range("You are out of bounds");
    }
    else{
        last_read  = (int)line - 1;
        return lines[line-1];
    }
}

void Document::write_line(const std::string &line) {
lines.push_back(line);
}

Document::Document(const std::string &name, const std::string &location, const std::string &extension) : Object(name,
                                                                                                                location,
                                                                                                                extension) {
last_read = -1;
}
bool Document ::operator!=(const Comparable *comparable ) const {
    int count = 0;
    Comparable * comparable1 = const_cast<Comparable*>(comparable);
    Document * document = dynamic_cast<Document*>(comparable1);
    if(document) {
        if (this->get_lines_count() == document->get_lines_count()) {
            for (auto line : lines) {

                if (line != document->lines[count]) {
                    return true;
                }
                count++;
            }
            return false;
        }else {
            return true;
        }
        }
    return true;
}
bool Document ::operator==( const Comparable *comparable) const {
    return !this->operator!=((Document*) comparable);
}

size_t Document::get_lines_count() const {
    return lines.size();
}

std::string Document::to_string() const {
std::string to_return;
to_return = get_name()  + '\n' + get_location() + '\n' + get_extension()+'\n';
    for(auto line : lines){
        to_return +=line;
        to_return +='\n';
    }
return to_return;
}

void Document::from_string(const std::string &document) {
    if(document.empty() || document == "\n")
        return;
    lines.clear();
    int from_index = 0;
    int next_index = 0;
    std::string name = this->fromIndexToSymbol(document, from_index ,'\n' , next_index);
    std::string location = this->fromIndexToSymbol(document , from_index,'\n',next_index );
    std::string extension = this->fromIndexToSymbol(document, from_index, '\n' , next_index);
    this->setName(name);
    this->setLocation(location);
    this->setExtension(extension);
    while(from_index!=document.size()){
        std::string add = this->fromIndexToSymbol(document , from_index , '\n',next_index);
        lines.push_back(add);
    }
}

std::string Document::fromIndexToSymbol(std::string in,int &index , char symbol, int &next_index) const {
    std::string result;
    for(int i = index; in[i]!=symbol;i++){
            result+=in[i];
            next_index = i;
    }
    next_index +=2;
    index = next_index;
    return result;
}

std::string Document::debug_print() const {
    int counter = 1;
    std::string result;
    for(auto line : lines ){
        result+="Line ";
        result += std::to_string(counter);
        result+=':';
        result +=line;
        result+='\n';
        counter++;
    }
    return result;
}

Object *Document::clone() const {
    return new Document(*this);
}


