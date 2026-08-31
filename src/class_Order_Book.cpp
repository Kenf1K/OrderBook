#include "class_Order_Book.hpp"

void OrderBook::AddOrder(const Order& order) {
    lock_guard<mutex> lg(mx);
    if (order.GetType() == TypeOrder::buy) {
        buy[order.GetPrice()].emplace_back(order);
    } else {
        sell[order.GetPrice()].emplace_back(order);
    }
}

bool OrderBook::CancelOrder(int id) {
    lock_guard<mutex> lgCancelOrder(mx);
    if (id <= 0) {
        cout << "invalid id \n";
        return false;
    }
    for (auto& searchPrice : buy) {
        auto& orders = searchPrice.second;
        auto it = find_if(orders.begin(), orders.end(),
                          [id](const Order& order) { return id == order.id; });
        if (it != orders.end()) {
            if (it->status == OrderStatus::filled) {
                cout << "Order is already completed\n";
                return false;
            }
            if (it->status == OrderStatus::cancelled) {
                cout << "Order is already cancelled\n";
                return false;
            }
            orders.erase(it);
            if (orders.empty()) {
                buy.erase(searchPrice.first);
            }
            cout << "Order " << id << " is cancelled\n";
            return true;
        }
    }

    for (auto& searchPrice : sell) {
        auto& orders = searchPrice.second;
        auto it =
            find_if(orders.begin(), orders.end(),
                    [id](const Order& orders) { return id == orders.id; });
        if (it != orders.end()) {
            if (it->status == OrderStatus::filled) {
                cout << "Order is already completed\n";
                return false;
            }
            if (it->status == OrderStatus::cancelled) {
                cout << "Order is already cancelled\n";
                return false;
            }
            orders.erase(it);
            if (orders.empty()) {
                sell.erase(searchPrice.first);
            }
            cout << "Order " << id << " is cancelled\n";
            return true;
        }
    }
    cout << "Order is not be searching or is not exist\n";
    return false;
}