#include <iostream>
#include <thread>
#include <string>
#include <pthread.h>

void thread_wrapper(void (*func)(), const std::string& name) {
    pthread_setname_np(pthread_self(), name.c_str());  // Set name
    func();  // Execute the actual function
}

void network_task() {
    std::cout << "Network thread started" << std::endl;
}

void io_task() {
    std::cout << "I/O thread started" << std::endl;
}

int main() {
    std::thread net_thread(thread_wrapper, network_task, "net_thread");
    std::thread io_thread(thread_wrapper, io_task, "io_thread");

    net_thread.join();
    io_thread.join();
    return 0;
}
