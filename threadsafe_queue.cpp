#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadsafeQueue {
private:
    mutable std::mutex mut;
    std::queue<int> data_queue;
    std::condition_variable data_cond;

public:
    void push(int new_value) {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(std::move(new_value));
        data_cond.notify_one();
    }

    void wait_and_pop(int& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this] { return !data_queue.empty(); });
        value = std::move(data_queue.front());
        data_queue.pop();
    }

    bool try_pop(int& value) {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty()) {
            return false;
        }
        value = std::move(data_queue.front());
        data_queue.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lk(mut); 
        return data_queue.size();
    }

    void clear() {
        std::lock_guard<std::mutex> lk(mut);
        data_queue = std::queue<int>();
    }
};