#include <stdio.h>
#include <time.h>
#include <unistd.h> // For Sleep() on Windows
#include <semaphore.h> 
#include <pthread.h> 

sem_t sem; // sem_wait(mutex) and sem_post(mutex)
int WCET_thr2 = 3;

//C library to print
//printf() – Prints formatted output to the console.
//fprintf() – Prints formatted output to a file or stream.
//sprintf() – Prints formatted output to a string.
//snprintf() – Safer version of sprintf() with buffer size control.

// execute C file
// cd "C:\Users\assyl\Downloads\All\01_Software_development\C_C++\A4_Coding"      
// gcc -o Binary_search Binary_search.c
// ./Binary_search
//cd C:/Users/assyl/Downloads/All/01_Software_development/C_C++/A4_Coding
// Function to perform binary search on array

// Execute on Linux
// wsl --install --distribution Ubuntu-22.04

void binarySearch(int arr[], int n, int key) 
{ 
    int low = 0, high = n - 1, mid; 
    while (low <= high) { 
        mid = (low + high) / 2; 
        if (arr[mid] == key) { 
            printf("Element found at index %d\n", mid); 
            return; 
        } 
        if (arr[mid] < key) 
            low = mid + 1; 
        else
            high = mid - 1; 
    } 
    printf("Element not found\n"); 
}

// Use of time.h to print each second since execution
// Time object is clock_t
// Function clock() returns the number of clock ticks elapsed since the program was launched = current time
// CLOCKS_PER_SEC is a constant which is 1000000 on most of the systems
// clock_t is a data type which is used to store the time in clock ticks

void clock_timee(){
    printf("Seconds since execution %ld\n", clock()/CLOCKS_PER_SEC );
}

void print_tab(int arr[] ,int n){
    printf("[ ");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("] \n");
}

void sorting(int arr[],int n){
    //Selection sort
    int min, temp;
    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min])
                min = j;
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
    print_tab(arr,n);
}

void* function2(void* args){
    sem_wait(&sem);
    printf("Thread2 work begins\n");
    printf("Wait for 3 seconds\n");
    sleep(3);
    printf("End of thread2 work\n");
    //sem_post(&sem);
    return NULL;
}

void* function1(void* args){
    printf("Hello from thread1\n");
    printf("Critical section waiting for thread 2 work\n");
    sem_post(&sem);
    //sleep(WCET_thr2);
    //sem_wait(&sem);
    //printf("Thread1 can now continue\n");
    
    return NULL 
    ;
}

int main() 
{ 
    /*
    printf("Execution time : ");
	clock_timee();
	// Binary search on a sorted array
    int arr[] = {2, 3, 4, 10, 40, 53, 60, 69 , 70, 79, 80, 83, 87, 90, 92, 100}; 
    int n = sizeof(arr)/sizeof(arr[0]); // Size in bits of the array
    int key = 69;
	printf("Binary search in :\n");
	print_tab(arr,n);
    binarySearch(arr, n, key); 

    // Sort array
	printf("Unsorted : ");
    int arr2[] = {4, 80, 83, 10, 69, 70, 40, 79, 87, 90, 92, 100, 2, 60, 3, 53}; 
    int n2 = sizeof(arr2)/sizeof(arr2[0]);// Size in bits of the array 
	print_tab(arr2, n2);
	printf("Sorted : ");
    sorting(arr2, n2);
    // Binary search
	printf("Binary search in the sorted array :\n");
    binarySearch(arr2, n2, key); 

    // Execution time
	printf("Execution time : ");
    sleep(1); // Sleep for 1 seconds
    clock_timee(); // Not working
    */
    // Semaphore
    sem_init(&sem, 0, 1);
    // Creates two threads
    pthread_t thread_1;
    pthread_create(&thread_1, NULL, function1, NULL);
    pthread_t thread_2;
    pthread_create(&thread_2, NULL, function2, NULL);
    // Thread 1 will wait for thread two first part to finish, executes and then give back the hand to thread 2
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    
    sem_destroy(&sem);
    printf("\nFin du programme \n");
	return 0;
}