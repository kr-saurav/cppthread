#include <future>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;
//



//1) method 1




//void factorial(int N){
//   int res = 1 ;
//   for(int i = N ; i > 1 ; i--)
//      res*=i ;
//   cout << "Result is: " << res << endl;
//}
//
//int main(){
//
//   // here if we just dont want to print factorial in child thread but we also want to return
//   // the result in main thread then .
//
//   std::thread t1(factorial , 4);
//   t1.join() ;
//
//   return 0 ;
//}




//2) method 2




//std::mutex mu; // need mutex because x is shared variable between both threads.
//std::condition_variable cond; // coz need to be sure that first child thread set x = res then only parent thread fetches it.
//
// here we can see we need two global variables to be handled to get our work done.
//void factorial(int N, int &x){
//   int res = 1 ;
//   for(int i = N ; i > 1 ; i--)
//      res*=i ;
//   cout << "Result is: " << res << endl;
//   x = res ;
//}
//
//int main(){
//
//   // here if we just dont want to print factorial in child thread but we also want to return
//   // the result in main thread then .
//   int x ;
//   std::thread t1(factorial , 4 , std::ref(x));
//
//   t1.join() ;
//   cout << x << endl;
//   return 0 ;
//}





// final approach.(future)




//
//int factorial(int N){
//   int res = 1 ;
//   for(int i = N ; i > 1 ; i--)
//      res*=i ;
//   cout << "Result is: " << res << endl;
//   return res ;
//}
//
//int main(){
//
//   // here if we just dont want to print factorial in child thread but we also want to return
//   // the result in main thread then .
//   int x ;
//   //std::thread t1(factorial , 4 , std::ref(x));
//   //std::future<int> fu = std::async(factorial, 5); // future class represents an obj where we can get value in future.
//   // above line may or may not create a new thread.
//   //std::future<int> fu = std::async(std::launch::deferred ,factorial, 6);
//   // above line will, for sure, not create a new thread. and get() will be executed in tha same main thread.
//    std::future<int> fu = std::async(std::launch::async ,factorial, 7);
//   //// above line will, for sure, create a new thread.
//   x = fu.get() ; // this waits untill child thread finishes. so first child thread finishes its work then x gets value from that thread.
//   // any future obj can call get() function only once.
//
//
//   return 0 ;
//}

// promise(when we want to pass some value from main to child thread some time after the creation of thread.

int factorial(std::future<int>& f){
   int res = 1 ;

   int N = f.get();

   for(int i = N ; i > 1 ; i--)
      res*=i ;
   cout << "Result is: " << res << endl;
   return res ;
}

int main(){

   int x ;
   std:: promise<int> p ;
   std:: future<int> f = p.get_future();
   // std::shared_future<int> sf = f.share() // doing this we can pass this in multiple future objects and can call sf.get() multiple times unlike in normal future<int> f where we can call f.get() only 1 time.
   std:: future<int> fu = std::async(std::launch::async ,factorial, std::ref(f));
   std::this_thread::sleep_for(chrono::milliseconds(20));
   p.set_value(7);


   x = fu.get() ;

   cout << "get from child: " << x << endl;
   return 0 ;
}

