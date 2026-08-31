#pragma once
#ifndef _CLASS_ORDER_QUEUE_HPP_
#define _CLASS_ORDER_QUEUE_HPP_
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

#include "class_order.hpp"
using namespace std;
class OrderQueue {
   private:
    queue<Order> orders;
    condition_variable cv;
    mutex mx;

   public:
    void Push(const Order& order);
    Order Pop();
    bool TryPop(Order& order);
    bool IsEmpty();
};

#endif