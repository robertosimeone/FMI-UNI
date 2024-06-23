//
// Created by Robert Borisov on 16.06.21.
//

#ifndef OOP_TEST11_NAMEDOBJECTARRAY_HPP
#define OOP_TEST11_NAMEDOBJECTARRAY_HPP
#include "NamedObject.hpp"
template <class T >
class NamedObjectArray {
private:
NamedObject<T> * array = nullptr;
size_t size = 0;
size_t ToAdd = 0;
public:
    NamedObjectArray() = default;
    NamedObjectArray(const NamedObjectArray<T>& rhs){
        this->size = rhs.size;
        array = new NamedObject<T>[rhs.size];
       for(int i = 0 ; i<rhs.size;i++){
           array[i] = rhs.array[i];
       }
    }
    NamedObjectArray& operator=(const NamedObjectArray<T>& rhs){
        if(this!=&rhs){
            delete[] array;
            array = new NamedObject<T>[rhs.size];
            this->size = rhs.size;
            for(int i = 0 ; i<rhs.size;i++){
                array[i] = rhs.array[i];
            }
        }
        return * this;
    }
    ~NamedObjectArray(){
        delete[] array;
    }
    void add(const NamedObject<T> &object){
        if(ToAdd + 1 > size) {
            NamedObject<T> *  copy = new NamedObject<T>[size+1];
            for(int i =0 ; i<size; i++){
                copy[i] = array[i];
            }
            delete[]array;
            ToAdd = size;
            array = copy;
        }
        array[ToAdd] = object;
        ToAdd++;
        size++;
    }
    size_t getSize() const{
        return size;
    }
    NamedObject<T> operator[](size_t index) const{
        if(index >=0 and index< size){
            return array[index];
        }
        else{
            throw  std::out_of_range("Out of range");
        }
    };

};




#endif //OOP_TEST11_NAMEDOBJECTARRAY_HPP
