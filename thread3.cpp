#include <iostream>
#include <thread>
#include <vector>



int main(){

    auto lambda = [](int x){
        std::cout << "Hello from thread!" << std::endl;
        std::cout << "Argument passed in: " << x << std::endl;
    };
    std::vector<std::thread> threads;

    for(int i = 0 ; i < 10 ; i++){
        threads.push_back(std::thread(lambda, i));
        threads[i].join();
    }

    std::cout << "hello from my main thread" << std::endl;
    return 0;
}