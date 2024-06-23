//
// Created by Robert Borisov on 3.06.21.
//

#ifndef OOP_REDOVEN_4_2_DEBUG_HPP
#define OOP_REDOVEN_4_2_DEBUG_HPP


class Debug {
public:
   virtual  std::string debug_print() const = 0;
   virtual ~Debug() = default;
};


#endif //OOP_REDOVEN_4_2_DEBUG_HPP
