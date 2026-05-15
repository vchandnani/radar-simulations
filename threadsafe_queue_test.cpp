#include <gtest/gtest.h>
#include <thread>
#include "threadsafe_queue.cpp"

TEST(ThreadsafeQueueTest, SizeAndClear) {
    ThreadsafeQueue tsq;

    std::thread producer([&tsq] {
        for (int i = 0; i < 10; ++i) {
            tsq.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    producer.join();

    ASSERT_EQ(tsq.size(), 10);
    ASSERT_FALSE(tsq.empty());

    tsq.clear();

    ASSERT_EQ(tsq.size(), 0);
    ASSERT_TRUE(tsq.empty());
}

TEST(ThreadsafeQueueTest, SumTryPop) {
    ThreadsafeQueue tsq;
    const int n = 10;
    const int expected_sum = n * (n + 1) / 2;
    int sum = 0;

    auto producer = [&tsq, n]() {
        for (int i = 1; i <= n; ++i) {
            tsq.push(i);
        }
    };

    auto consumer = [&tsq, &sum, n]() {
        int val = 0;

        for (int j = 1; j <= n; ++j) {
            bool res = tsq.try_pop(val);
            if (res) {
                sum += val;
            } else {
                std::cerr << "\t-- failed to read " << j << "th value\n";
            }
        }
    };

    std::thread producer_thread = std::thread{producer};
    std::this_thread::sleep_for(std::chrono::milliseconds{5});
    std::thread consumer_thread = std::thread{consumer};

    producer_thread.join();
    consumer_thread.join();

    ASSERT_EQ(sum, expected_sum);
    ASSERT_TRUE(tsq.empty());
}

TEST(ThreadsafeQueueTest, SumWaitAndPop) {
    ThreadsafeQueue tsq;
    const std::chrono::milliseconds delay{50};
    const int n = 10;
    const int expected_sum = n * (n + 1) / 2;
    int sum = 0;

    auto producer = [&tsq, &delay, n]() {
        for (int i = 1; i <= n; ++i) {
            tsq.push(i);
            std::this_thread::sleep_for(i * delay);
        }
    };

    auto consumer = [&tsq, &sum, n]() {
        int val = 0;

        for (int j = 1; j <= n; ++j) {
            tsq.wait_and_pop(val);
            sum += val;
        }
    };

    std::thread producer_thread = std::thread{producer};
    std::thread consumer_thread = std::thread{consumer};

    producer_thread.join();
    consumer_thread.join();

    ASSERT_EQ(sum, expected_sum);
    ASSERT_TRUE(tsq.empty());
}