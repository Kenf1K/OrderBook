#pragma once
#ifndef _CLASS_ORDER_HPP_
#define _CLASS_ORDER_HPP_
#include <fstream>
#include <stdexcept>

#include "class_order_status.hpp"
#include "class_order_type.hpp"
using namespace std;
class OrderBook;
class MatchingEngine;
class Order {
    unsigned int id;
    static unsigned int nextId;
    float price;
    unsigned int quantity;
    TypeOrder type;
    OrderStatus status;

    friend class OrderBook;
    friend class MatchingEngine;

   public:
    Order();
    Order(float price, unsigned int quantity, TypeOrder type);
    float GetPrice() const;
    unsigned int GetId() const;
    unsigned int GetQuantity() const;
    TypeOrder GetType() const;
    OrderStatus GetStatus() const;
};
ostream& operator<<(std::ostream& os, TypeOrder type);
ostream& operator<<(std::ostream& os, OrderStatus status);

#endif