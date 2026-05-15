#include <iostream>
#include "ring_buffer.h"
#include "threadsafe_queue.cpp"

int main() {

    std::cout << "Hello World" << std::endl;

    RingBuffer<int> rb(3);

    rb.push(1);
    rb.push(2);
    rb.push(3);
    
    std::cout << "START: RingBuffer Program" << std::endl;
    std::cout << "Buffer full: " << rb.full() << std::endl; // 1 (true)

    rb.push(4); 

    std::cout << "Popped: " << rb.pop() << std::endl; // 2
    std::cout << "Popped: " << rb.pop() << std::endl; // 3
    std::cout << "Popped: " << rb.pop() << std::endl; // 4

    std::cout << "FINISH: RingBuffer Program" << std::endl;

    ThreadsafeQueue tsq;

    std::cout << "START: ThreadsafeQueue Program" << std::endl;

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

    std::cout << "FINISH: ThreadsafeQueue Program" << std::endl;

    return 0;
}