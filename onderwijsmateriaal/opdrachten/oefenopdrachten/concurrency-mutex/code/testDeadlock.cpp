#include <iostream>
#include <thread>
#include <mutex>  
using namespace std;

int teller1 = 0;int teller2 = 0;
const int AANTAL = 100000;
mutex mtx_teller1;  mutex mtx_teller2;
void doe_iets_12() {
  for (int i = 0; i < AANTAL; i++) 
  {	
    mtx_teller1.lock();	
    mtx_teller2.lock();	
    teller2 = teller1+1;	
    teller1 = teller2;	
    mtx_teller1.unlock();	
    mtx_teller2.unlock();
  }
}
void doe_iets_21() {
  for (int i = 0; i < AANTAL; i++) 
  {	
    mtx_teller2.lock();	
    mtx_teller1.lock();	
    teller2 = teller1+1;	
    teller1 = teller2;	
    mtx_teller2.unlock();	
    mtx_teller1.unlock();
  }
}
int main(int argc, char **argv) 
{  
    thread t1(doe_iets_12);  
    thread t2(doe_iets_21);  
    t1.join();  
    t2.join();  
    cout << "we are lucky if we have not crashed";
    cout << endl;
  return 0;
}
