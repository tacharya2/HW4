#include <stdio.h>;
int main(void)  
{
    int staticIntArray[ARRAY_SIZE];//array on the stack
    int *ptrArray = new int[ARRAY_SIZE]; // pointer on the stack but array on the heap.
    double timeItTakes;
    clock_t tStart = clock();
    fillWithRandomNumbers(staticIntArray, ARRAY_SIZE);
    double time = static_cast<double>(clock() - static_cast<double>(tStart)/static_cast<double>(CLOCKS_PER_SEC));
    printf ("Array on stack time is %.10f\n", time);
    clock_t tStart2 = clock();
    fillWithRandomNumbers(ptrArray, ARRAY_SIZE);
    double time2 = static_cast<double>(clock() - static_cast<double>(tStart2)/static_cast<double>(CLOCKS_PER_SEC));
    printf ("Array on heap time is %.10f\n", time2);
    //cout << "Array on the heap time is " << (timeIntStack - time(NULL));
}
void fillWithRandomNumbers(int intArray[], int size)
{
    for(int i = 0; i<size; i++)
        intArray[i] = rand();
}