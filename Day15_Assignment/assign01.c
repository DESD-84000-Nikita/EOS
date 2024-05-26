/*Create a thread to sort given array of 10 integers using selection sort. Main thread should print the result after sorting is completed.*/

#include <stdio.h>
#include <pthread.h>

#define ARRAY_SIZE 10

// Function to perform selection sort on the array
void selection_sort(int arr[], int n) {
    int i, j, min_index, temp;
    for (i = 0; i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        // Swap the found minimum element with the first element
        temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
    }
}

// Thread function to perform sorting
void *sort_thread(void *arg) {
    int *arr = (int *)arg;
    selection_sort(arr, ARRAY_SIZE);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    int arr[ARRAY_SIZE] = {5, 2, 9, 1, 7, 4, 8, 3, 6, 10};
    
    // Create a thread to sort the array
    pthread_create(&tid, NULL, sort_thread, (void *)arr);
    
    // Wait for the sorting thread to finish
    pthread_join(tid, NULL);
    
    // Print the sorted array
    printf("Sorted Array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}	
