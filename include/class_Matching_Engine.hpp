#pragma once
#ifndef _CLASS_MATCHING_ENGINE_HPP_
#define _CLASS_MATCHING_ENGINE_HPP_
#include <algorithm>
#include <fstream>

#include "class_Order_Book.hpp"
#include "class_Order_Queue.hpp"
#include "class_order.hpp"
using namespace std;
class MatchingEngine {
    OrderQueue& queue;
    OrderBook& book;
    ofstream ost;

   public:
    MatchingEngine(OrderQueue& queue, OrderBook& book);
    void Process(int limit);

   private:
    void MatchOrders();
};

#endif