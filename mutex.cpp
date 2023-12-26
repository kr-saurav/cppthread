#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex gLock;
static int shared_value= 0;

void shared_value_increment(){
    gLock.lock(); // if we don't use this mutex lock then our final value can be less than 1000.
        shared_value = shared_value + 1; // this line is critical section
    gLock.unlock();
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