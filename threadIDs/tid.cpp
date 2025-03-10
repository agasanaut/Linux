#include <iostream>
#include <thread>
#include <pthread.h>


void set_thread_name(const std::string& name) {
    pthread_setname_np(pthread_self(), name.c_str());
}

std::string get_thread_name() {
    char name[16];  // Linux supports names up to 16 characters
    pthread_getname_np(pthread_self(), name, sizeof(name));
    return std::string(name);
}


void threadfunc1() {
    set_thread_name(__FUNCTION__);
    std::cout << "Thread 1 ID: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(100));
}


void threadfunc2() {
    set_thread_name(__FUNCTION__);
    std::cout << "Thread 2 ID: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(100));
}

int main() {
    std::thread t1(threadfunc1);
    std::thread t2(threadfunc2);
    // Wait for the thread to finish
    t1.join();
    // Wait for the thread to finish
    t2.join();
    return 0;
}
// https://github.com/agasanaut/Linux/blob/main/threadIDs/tid.cpp
//example
//tejus@tejusAI:~$ cat /proc/20817/task/20823/comm 
//threadfunc2
