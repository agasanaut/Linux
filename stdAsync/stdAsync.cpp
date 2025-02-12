#include<iostream>
#include<future>
#include<unistd.h>


using namespace std;



int someFunction(int a , int b)
{
    std::cout << "someFunction() called" << std::endl;
    usleep(2000000);
    return a + b;
}


int main()
{
    std::cout << "Hello World!" << std::endl;

    auto result = std::async(std::launch::async, someFunction, 5 ,4);  // or use  std::launch::deferred instead of std::launch::async

    cout<< result.get(); //if u use std ddeferred then thread starts here

    std::cout << "someFunction() returned " << std::endl;

    return 0;
}