#include <boost/asio.hpp>
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <thread>

using namespace std::chrono;

class HeartbeatManager {
public:
    HeartbeatManager(boost::asio::io_context& io_context, int interval_ms, int timeout_ms)
        : io_context_(io_context), 
          heartbeat_timer_(io_context, std::chrono::milliseconds(interval_ms)), 
          heartbeat_interval_ms_(interval_ms), 
          timeout_threshold_ms_(timeout_ms) {}

    // Register a thread's heartbeat
    void registerThread(std::thread::id tid) {
        io_context_.post([this, tid]() {
            heartbeats_[tid] = steady_clock::now();
        });
    }

    // Update heartbeat for a thread
    void updateHeartbeat(std::thread::id tid) {
        io_context_.post([this, tid]() {
            heartbeats_[tid] = steady_clock::now();
            std::cout << "✅ Heartbeat received from Thread " << tid << std::endl;
        });
    }

    // Start monitoring heartbeats
    void startMonitoring() {
        monitorHeartbeats();
    }

private:
    boost::asio::io_context& io_context_;
    boost::asio::steady_timer heartbeat_timer_;
    std::unordered_map<std::thread::id, steady_clock::time_point> heartbeats_;
    int heartbeat_interval_ms_;
    int timeout_threshold_ms_;

    void monitorHeartbeats() {
        io_context_.post([this]() {
            auto now = steady_clock::now();
            for (const auto& [tid, last_beat] : heartbeats_) {
                auto duration = duration_cast<milliseconds>(now - last_beat).count();
                if (duration > timeout_threshold_ms_) {
                    std::cerr << "⚠️ Thread " << tid << " is INACTIVE (Last beat: " << duration << "ms ago)\n";
                }
            }
        });

        // Schedule next check
        heartbeat_timer_.expires_after(std::chrono::milliseconds(heartbeat_interval_ms_));
        heartbeat_timer_.async_wait([this](const boost::system::error_code&) {
            monitorHeartbeats();
        });
    }
};

// Worker thread function
void workerFunction(HeartbeatManager& hbManager, int id) {
    std::thread::id tid = std::this_thread::get_id();
    hbManager.registerThread(tid);

    while (true) {
        hbManager.updateHeartbeat(tid);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Simulate work
    }
}

int main() {
    boost::asio::io_context io_context;
    HeartbeatManager hbManager(io_context, 1000, 3000);  // Check every 1s, timeout after 3s

    std::vector<std::thread> workers;
    for (int i = 1; i <= 3; ++i) {
        workers.emplace_back(workerFunction, std::ref(hbManager), i);
    }

    // Start monitoring in a separate thread
    std::thread monitorThread([&]() { 
        hbManager.startMonitoring();
        io_context.run(); 
    });

    // Join threads
    for (auto& worker : workers) worker.join();
    monitorThread.join();

    return 0;
}
