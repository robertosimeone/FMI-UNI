//
// Created by Robert Borisov on 3.06.21.
//

#ifndef OOP_REDOVEN_4_2_COMPARABLE_HPP
#define OOP_REDOVEN_4_2_COMPARABLE_HPP


class Comparable {
public:
   virtual  bool operator!=(const Comparable* comparable) const = 0;
   virtual bool operator==(const Comparable* comparable) const = 0;
   virtual ~Comparable() = default;

};




#endif //OOP_REDOVEN_4_2_COMPARABLE_HPP
