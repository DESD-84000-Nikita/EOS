/*Create a thread to sort given array of "n" integers using bubble sort. Main thread should print the result after sorting is completed.*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Struct to pass array and size to thread function
struct Array {
    int *arr;
    int size;
};

// Bubble sort function
void* bubbleSort(void* arg) {
    struct Array *arr = (struct Array*) arg;
    int n = arr->size;
    int *arrPtr = arr->arr;

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arrPtr[j] > arrPtr[j+1]) {
                // Swap
                int temp = arrPtr[j];
                arrPtr[j] = arrPtr[j+1];
                arrPtr[j+1] = temp;
            }
        }
    }

    // Thread is done, exit
    pthread_exit(NULL);
}

int main() {
    // Example array to sort
    int data[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(data) / sizeof(data[0]);

    // Creating a structure to pass to the thread function
    struct Array arr;
    arr.arr = data;
    arr.size = n;

    // Creating thread
    pthread_t tid;
    pthread_create(&tid, NULL, bubbleSort, &arr);

    // Waiting for the thread to finish
    pthread_join(tid, NULL);

    // Printing sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", data[i]);
    printf("\n");

    return 0;
}
