#include "class_Order_Queue.hpp"

// 2)созданный ордер попадает в очередь
void OrderQueue::Push(const Order& order) {
    lock_guard<mutex> lg(mx);  // лочим mutex
    orders.push(
        order);  // добавляем ордер в очередь для дальнейшего добавления в книгу
    cv.notify_one();  // оповещаем cv о добавлении
}
// 4)ордер извлекается из очереди
Order OrderQueue::Pop() {
    unique_lock<mutex> ul(
        mx);  // захватываем mutex, чтобы не добавлялись ордера пока извлекаем
    cv.wait(ul, [this]() {
        return !orders.empty();
    });                            // проверяем что очередь не пуста
    Order order = orders.front();  // копируем для возврата
    orders.pop();                  // удаляем
    return order;
}

// костыль
bool OrderQueue::TryPop(Order& order) {
    lock_guard<mutex> lg(mx);
    if (!orders.empty()) {
        order = orders.front();
        orders.pop();
        return true;
    } else {
        return false;
    }
}
// проверка на пустоту очереди
bool OrderQueue::IsEmpty() {
    lock_guard<mutex> l(mx);
    return orders.empty();
}
