#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <mutex>
#include <condition_variable>

class condvarQueue
{
    std::queue<int> produced_nums;
    std::mutex m;
    std::condition_variable cond_var;
    bool done = false;
    bool notified = false;
public:
    void push(int i)
    {
        std::unique_lock<std::mutex> lock(m);
        produced_nums.push(i);
        notified = true;
        cond_var.notify_one();
    }

    template<typename Consumer>
    void consume(Consumer consumer)
    {
        std::unique_lock<std::mutex> lock(m);
        while (!done) {
            while (!notified) {  // loop to avoid spurious wakeups
                cond_var.wait(lock);
            }
            while (!produced_nums.empty()) {
                consumer(produced_nums.front());
                produced_nums.pop();
            }
            notified = false;
        }
    }

    void close()
    {
        {
            std::lock_guard<std::mutex> lock(m);
            done = true;
            notified = true;
        }
        cond_var.notify_one();
    }
};

int main()
{
    condvarQueue queue;

    std::thread producer([&]() {
        for (int i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "producing " << i << '\n';
            queue.push(i);
        }
        queue.close();
        });

    std::thread consumer([&]() {
        queue.consume([](int input) {
            std::cout << "consuming " << input << '\n';
            });
        });

    producer.join();
    consumer.join();
}
