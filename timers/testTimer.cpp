#include <iostream>
#include <boost/asio.hpp>
#include <mutex>
#include <thread>
#include <vector>

bool isFirst = true;

class TimerClass {
public:
    TimerClass(boost::asio::io_context& ctx, int id, int interval)
        : timer(ctx, boost::asio::chrono::seconds(interval)), timer_id(id), stopped(false) {}

    void start() {
        std::cout << "Starting Timer " << timer_id << "..." << std::endl;
        timer.async_wait(std::bind(&TimerClass::timerCallback, this, std::placeholders::_1));
    }

    void stop() {
        std::lock_guard<std::mutex> lock(mutex);
        stopped = true;
        timer.cancel();
    }

private:
    void timerCallback(const boost::system::error_code& e) {
        if (stopped) {
            return;
        }
        if (!e) {
            if (isFirst) {
                isFirst = false;
                std::cout << "All timers waiting." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(20));
            }

            std::cout << "Timer " << timer_id << " expired!" << std::endl;
            // Restart the timer
            timer.expires_after(boost::asio::chrono::seconds(2));
            timer.async_wait(std::bind(&TimerClass::timerCallback, this, std::placeholders::_1));
        }
    }

    boost::asio::steady_timer timer;
    std::mutex mutex;
    bool stopped;
    int timer_id;
};

int main() {
    boost::asio::io_context io;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard = boost::asio::make_work_guard(io);

    std::vector<std::unique_ptr<TimerClass>> timers;
    std::thread ioThread([&]() { io.run(); }); // Run io_context in a separate thread

    // Create multiple timers
    for (int i = 0; i < 3; ++i) {
        timers.emplace_back(std::make_unique<TimerClass>(io, i + 1, 2));
        timers.back()->start();
    }

    std::this_thread::sleep_for(std::chrono::seconds(20));

    // Stop all timers
    for (auto& timer : timers) {
        timer->stop();
    }

    work_guard.reset(); // Allow io_context to stop once work is done
    io.stop();
    ioThread.join();

    std::cout << "All timers stopped." << std::endl;
    return 0;
}
