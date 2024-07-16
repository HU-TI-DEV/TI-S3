#include <iostream>
#include <string>
#include <thread>

void call_from_thread(std::string threadname) {
   for (int i = 0; i <= 100; i++) { std::cout << threadname; }
}

int main() {
   std::thread t1(call_from_thread, "a");
   std::thread t2(call_from_thread, "b");
   std::thread t3(call_from_thread, "c");

   t1.join();
   t2.join();
   t3.join();

   std::cout <<  std::endl;
   return 0;
}
