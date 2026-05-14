#include <iostream>
#include "threadsafe_queue.cpp"

int main() {
    ThreadsafeQueue tsq;

    std::thread producer([&tsq] {
        for (int i = 0; i < 10; ++i) {
            tsq.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    std::thread consumer([&tsq] {
        int value;
        for (int i = 0; i < 10; ++i) {
            tsq.wait_and_pop(value);
            std::cout << "Consumer popped: " << value << std::endl;
        }
    });

    producer.join();
    consumer.join();

    return 0;
}