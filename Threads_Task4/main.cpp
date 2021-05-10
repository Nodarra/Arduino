#include <iostream>
#include <pthread.h>

//Number of threads and partitions//
#define MAX_THREAD 2

//Numebr of array elements//
#define MAX 10

using namespace std;

int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; //array
int sum[2] = {0}; //sum of two threads, will be joined later
int part = 0; //partitions
int total;
int avg;

void* arraySum(void* arg)
{
    int thread_part = part++;
    
    for(int i = thread_part * (MAX / 2); i < (thread_part+1)*(MAX / 2); i++){
        sum[thread_part] += arr[i];
    }
}

int main()
{
    pthread_t threads[MAX_THREAD];
    
    for(int i = 0; i < MAX_THREAD; i++){ //Creating two threads
        pthread_create(&threads[i], NULL, arraySum, (void*)NULL);
    }
    
    for(int i = 0; i < MAX_THREAD; i++){//Joining two threads
        pthread_join(threads[i], NULL);
    }
    
    for(int i = 0; i < MAX_THREAD; i++){//Suming the threads outputs
        total += sum[i];
    }
    
    avg = total/MAX;
    
    cout << "Average of an array is: " << avg << endl;
}
