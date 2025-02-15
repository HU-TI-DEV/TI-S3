#include <iostream>
#include <thread>
  
using namespace std;

int teller = 0;  
const int AANTAL = 100000;

void telop() {
   for (int i = 0; i < AANTAL; i++) {
	teller++;
    }
}



int main(int argc, char **argv) {
   thread t1(telop);
   thread t2(telop);
   thread t3(telop);
   thread t4(telop);
   t1.join();
   t2.join();
   t3.join();
   t4.join();
   cout << "'\nteller = " << teller;
   cout << " (" << 4 * AANTAL << " expected)";
   cout << endl;
   return 0;
}