#pragma once
#ifndef _CLASS_ORDER_BOOK_HPP
#define _CLASS_ORDER_BOOK_HPP
#include <algorithm>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <vector>

#include "class_order.hpp"
class MatchingEngine;
class OrderBook {
   private:
    map<float, vector<Order>, greater<float>> buy;
    map<float, vector<Order>, less<float>> sell;
    mutex mx;
    void AddOrder(const Order& order);
    friend MatchingEngine;

   public:
    bool CancelOrder(int id);
};

#endif