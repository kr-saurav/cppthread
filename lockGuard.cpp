#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex gLock;
static int shared_value= 0;

void shared_value_increment(){
    std::lock_guard<std::mutex> lock_Guard(gLock); // this is wrapper over mutex class and mutex got
    // itself released when corresponding function's scope ends.(implements a strictly scope-based mutex ownership wrapper)
    shared_value = shared_value + 1; // this line is critical section

}

int main(){

    std::vector<std::thread> threads;
    for(int i=0; i < 100; i++){
        threads.push_back(std::thread(shared_value_increment));
    }

    for(int i=0; i < 100; i++){
        threads[i].join();
    }

    std::cout << "Shared value:" << shared_value << std::endl;
    return 0;
}