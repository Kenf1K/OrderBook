#include <chrono>
#include <random>

#include "class_Matching_Engine.hpp"
#include "class_Order_Book.hpp"
#include "class_Order_Queue.hpp"
#include "class_order.hpp"
void GenerateOrders(OrderQueue& queue, int count) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> priceDist(50.0f, 500.0f);
    uniform_int_distribution<int> quantityDist(1, 100);
    uniform_int_distribution<int> typeDist(0, 1);

    for (int i = 0; i < count; ++i) {
        float price = priceDist(gen);
        int quantity = quantityDist(gen);
        TypeOrder type =
            (typeDist(gen) == 0) ? TypeOrder::buy : TypeOrder::sell;

        Order order(price, quantity, type);
        queue.Push(order);
    }
}

int main() {
    OrderQueue queue;
    OrderBook book;
    MatchingEngine engine(queue, book);
    GenerateOrders(queue, 350000);
    auto start = chrono::high_resolution_clock::now();

    thread engineThread(&MatchingEngine::Process, &engine, 350000);
    engineThread.join();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "TIME: " << duration.count() << "\n";

    return 0;
}