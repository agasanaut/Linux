#include<iostream>
#include<future>
#include<unistd.h>

void someFunction()
{
    std::cout << "someFunction() called" << std::endl;
    usleep(10000000);

}

int main()
{
    std::cout << "Hello World!" << std::endl;

    auto result = std::async(std::launch::async, someFunction);  // or use  std::launch::deferred instead of std::launch::async

    result.get(); //if u use std ddeferred then thread starts here

    std::cout << "someFunction() returned " << std::endl;

    return 0;
}