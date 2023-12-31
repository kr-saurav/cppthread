#include <iostream>
#include <thread>
#include <vector>

int main(){


    auto lambda = [](int x){
        std::cout << "Hello from thread!" << std::this_thread::get_id() << std::endl;
        std::cout << "Argument passed in: " << x << std::endl;
    };
    std::vector<std::thread> threads;

 // here sequentially 10 threads are getting created, if you print 10 thread ID then there will be same IDs all over.
 // same IDs because every iteration 1 thread is getting created and joined and getting terminated and then in next iteration again 1 thread is getting
 // created and so on.
 // so at any time only thread is running.


    for(int i = 0 ; i < 10 ; i++){
        threads.push_back(std::thread(lambda, i));
        threads[i].join();
    }

    std::cout << "hello from my main thread" << std::endl;
    return 0;
}