//
// Created by Robert Borisov on 3.06.21.
//

#ifndef OOP_REDOVEN4_1_PUBLISHER_HPP
#define OOP_REDOVEN4_1_PUBLISHER_HPP
#include "Averager.hpp"
#include "MovingAverager.hpp"
#include "PeriodicSampler.hpp"
#include <vector>


class Publisher {
public:
    void unsubscribe(Averager *);
    void unsubscribe(MovingAverager *);
    void unsubscribe(PeriodicSampler *);

   virtual void subscribe(Averager *) = 0;
   virtual void subscribe(MovingAverager *) = 0;
   virtual void subscribe(PeriodicSampler *) = 0;
   virtual void signal(Message message);
   std::vector<Subscriber*> &  getSubscribers();
   virtual ~Publisher() = default;

private:
    std::vector<Subscriber*> subscribers;


};


#endif //OOP_REDOVEN4_1_PUBLISHER_HPP
