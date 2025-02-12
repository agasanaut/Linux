#include <iostream>
#include <boost/asio.hpp>
#include <mutex>
#include <thread>

class TimerClass {
public:
    TimerClass() : timer(io, boost::asio::chrono::seconds(2)), stopped(false) {}

    void start() {
        std::cout << "Starting one-shot timer..." << std::endl;
        timer.async_wait(std::bind(&TimerClass::timerCallback, this, std::placeholders::_1));
        io.run(); // Run the io_context to process the timer event
        std::cout << "Timer thread finished." << std::endl;
    }

    void stop() {
        std::lock_guard<std::mutex> lock(mutex);
        stopped = true;
        timer.cancel();
        io.stop();
    }

private:
    void timerCallback(const boost::system::error_code& e) {
        std::lock_guard<std::mutex> lock(mutex);
        if (stopped) {
            return;
        }
        if (!e) {
            std::cout << "Timer expired!" << std::endl;
            // Restart the timer
            timer.expires_after(boost::asio::chrono::seconds(2));
            timer.async_wait(std::bind(&TimerClass::timerCallback, this, std::placeholders::_1));
        }
    }

    boost::asio::io_context io;
    boost::asio::steady_timer timer;
    std::mutex mutex;
    bool stopped;
};

int main() {
    TimerClass timerClass;
    std::thread timerThread(&TimerClass::start, &timerClass);

    std::this_thread::sleep_for(std::chrono::seconds(5));
    timerClass.stop();

    timerThread.join();
    return 0;
}
