#include <iostream>
#include "ring_buffer.h"

int main() {
    RingBuffer<int> rb(3);

    rb.push(1);
    rb.push(2);
    rb.push(3);
    
    std::cout << "Buffer full: " << rb.full() << std::endl; // 1 (true)

    rb.push(4); 

    std::cout << "Popped: " << rb.pop() << std::endl; // 2
    std::cout << "Popped: " << rb.pop() << std::endl; // 3
    std::cout << "Popped: " << rb.pop() << std::endl; // 4

    return 0;
}