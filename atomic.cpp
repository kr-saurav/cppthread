// @file atomics.cpp
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

static std::atomic<int> shared_value= 0; // no need for any lock when using atomic class

void shared_value_increment(){
    shared_value+=1; // we can't do shared_value = shared_value + 1 ; but can do post-increment.
}

int main(){

    std::vector<std::thread> threads;
    for(int i=0; i < 1000; i++){
        threads.push_back(std::thread(shared_value_increment));
    }

    for(int i=0; i < 1000; i++){
        threads[i].join();
    }

    std::cout << "Shared value:" << shared_value << std::endl;
    return 0;
}