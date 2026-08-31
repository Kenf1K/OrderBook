#include "class_order.hpp"

Order::Order() : price(0), quantity(0), type(TypeOrder::buy) {}
// 1)создаем ордер и идем в очередь
Order::Order(float price, unsigned int quantity, TypeOrder type) {
    if (price <= 0) {
        throw invalid_argument("Price must be greater than 0");
    }
    if (quantity <= 0) {
        throw invalid_argument("Quantity must be greater than 0");
    }
    this->price = price;
    this->quantity = quantity;
    this->type = type;
    status = OrderStatus::active;
    id = nextId++;
}

float Order::GetPrice() const { return price; }

unsigned int Order::GetId() const { return id; }

unsigned int Order::GetQuantity() const { return quantity; }

TypeOrder Order::GetType() const { return type; }

OrderStatus Order::GetStatus() const { return status; }

ostream& operator<<(ostream& os, TypeOrder type) {
    switch (type) {
        case TypeOrder::buy:
            return os << "buy";
        case TypeOrder::sell:
            return os << "sell";
        default:
            return os << "unknown";
    }
}

ostream& operator<<(ostream& os, OrderStatus status) {
    switch (status) {
        case OrderStatus::active:
            return os << "active";
        case OrderStatus::partial:
            return os << "partial";
        case OrderStatus::filled:
            return os << "filled";
        case OrderStatus::cancelled:
            return os << "cancelled";
        default:
            return os << "unknown";
    }
}

unsigned int Order::nextId = 1;
