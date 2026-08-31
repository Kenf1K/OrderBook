#include "class_Matching_Engine.hpp"

MatchingEngine::MatchingEngine(OrderQueue& queue, OrderBook& book)
    : queue(queue), book(book), ost("trade.csv", ios::app) {}
// 3) попадаем в метод Process,который вызывает метод Pop(переходить в файл
// OrderQueue.cpp)
void MatchingEngine::Process(int limit) {
    int processed = 0;
    while (processed < limit) {
        if (queue.IsEmpty()) {
            break;
        }
        Order order = queue.Pop();  // копируем извлеченный ордер из очереди
        book.AddOrder(order);       // добавляем ордер в книгу
        MatchOrders();              // вызываем матчинг
        processed++;
    }
}
// 5) сердце программы
void MatchingEngine::MatchOrders() {
    lock_guard<mutex> lock(
        book.mx);  // захватываем mutex книги ордеров, чтобы книга не менялась
    while (!book.buy.empty() &&
           !book.sell.empty()) {  // пока очереди не будут пусты
        float buyPrice = book.buy.begin()->first;
        float sellPrice = book.sell.begin()->first;
        if (buyPrice < sellPrice)
            break;  //  если цены не совпдают считать нечего

        auto& buyVec = book.buy.begin()->second;    // берем  вектор для покупки
        auto& sellVec = book.sell.begin()->second;  // ,берем вектор для продажи

        auto& buyOrder = buyVec.front();  // берем первый ордер из вектора
        auto& sellOrder = sellVec.front();

        unsigned int tradeQty = min(buyOrder.quantity, sellOrder.quantity);

        buyOrder.quantity -= tradeQty;
        sellOrder.quantity -= tradeQty;

        if (buyOrder.quantity == 0) {
            buyOrder.status = OrderStatus::filled;
            ost << "Type: " << buyOrder.type << " id: " << buyOrder.id
                << " Price: " << buyOrder.price
                << " Quantity: " << buyOrder.quantity << " " << buyOrder.status
                << "\n";
            buyVec.erase(buyVec.begin());  // удаляем из вектора
        } else {
            buyOrder.status = OrderStatus::partial;
            ost << "Type: " << buyOrder.type << " id: " << buyOrder.id
                << " Price: " << buyOrder.price
                << " Quantity: " << buyOrder.quantity << " " << buyOrder.status
                << "\n";
        }

        if (sellOrder.quantity == 0) {
            sellOrder.status = OrderStatus::filled;
            ost << "Type: " << sellOrder.type << " id: " << sellOrder.id
                << " Price: " << sellOrder.price
                << " Quantity: " << sellOrder.quantity << " "
                << sellOrder.status << "\n";
            sellVec.erase(sellVec.begin());
        } else {
            sellOrder.status = OrderStatus::partial;
            ost << "Type: " << sellOrder.type << " id: " << sellOrder.id
                << " Price: " << sellOrder.price
                << " Quantity: " << sellOrder.quantity << " "
                << sellOrder.status << "\n";
        }

        if (buyVec.empty()) book.buy.erase(book.buy.begin());  // удаляем цены
        if (sellVec.empty())
            book.sell.erase(book.sell.begin());  // удаляем цены
    }
}
