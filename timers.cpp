#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

int ARRAY_SIZE = 100000;

void sub1(){
  int j = ARRAY_SIZE;
  int staticIntArray[ARRAY_SIZE]; //array on the stack
  int array[ARRAY_SIZE];
  for (int i = 0; i < ARRAY_SIZE; i++){
     array[j] = i+1;
  }
}

void sub2(){
  //Using array on the stack
  int staticIntArray[ARRAY_SIZE]; 
  int array[ARRAY_SIZE];
  for (int i = 0; i < ARRAY_SIZE; i++){
    array[i] = rand();
  }
}
void sub3(){
// pointer on the stack but array on the heap.
  int *ptrArray = new int[ARRAY_SIZE];
   int array[ARRAY_SIZE];
  for (int i = 0; i < ARRAY_SIZE; i++){
    ptrArray[i] = rand();
  }
}

int main(){

// Statically with large array
  clock_t time_req;
  time_req = clock();
  sub1();
  time_req = clock() - time_req;
  cout << "Using statical method, it took: " << (float)time_req / CLOCKS_PER_SEC << " seconds" << endl;

  //Stack with large array
  time_req = clock();
  sub2();
  time_req = clock() - time_req;
  cout << "Using stack method, it took: " << (float)time_req / (CLOCKS_PER_SEC) << " seconds" << endl;

  // Heap with large array
  time_req = clock();
  sub3();
  time_req = clock() - time_req;
  cout << "Using heap method, it took: " << (float)time_req / CLOCKS_PER_SEC << " seconds" << endl;
}