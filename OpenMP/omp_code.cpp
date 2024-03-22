/*
  Purpose:

    BinarySearchOpenMP is an example of parallelizing an existing code for binary search 
    by introducing OpenMP directives in the bubble sort process to improve performance for Intro to Parallel Programming Students.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    24 September 2003
    22 March 2024 by Jhon Edinson, demonstrating OpenMP 
parallelization.

  Author:
    Original Author
  OpenMP Modification:
    22 March 2024 by Jhon Edinson, as part of a learning exercise in an educational context. 
    This OpenMP Modification introduces parallelization in the bubble sort algorithm, 
    aiming to reduce the sorting time by utilizing multiple processors. The binary search 
    part remains unchanged, focusing the parallelization efforts on the data preparation phase.

*/

#include <stdio.h>
#include <time.h>
#include <omp.h> // Include OpenMP library for parallelization.

void bubble_sort(int [], int);
int binary_search_parallel(int [], int, int);

int main() {
    clock_t start = clock(); // Start measuring total execution time of the program.
    
    int key, size, i, result = -1;
    int list[100]; // Increase the array size to 100 for broader testing.

    // Requests the list size and elements from the user, printing them as they are entered.
    printf("Enter size of a list: ");
    scanf("%d", &size);
    printf("Enter elements\n");
    for (i = 0; i < size; i++) {
        scanf("%d", &list[i]);
        printf("%d ", list[i]);
    }
    printf("\n");
    
    bubble_sort(list, size); // Sort the array using the parallelized bubble sort function.
    
    printf("\nEnter key to search\n");
    scanf("%d", &key);
    printf("%d\n", key); // Prints the search key entered by the user.
    
    // Performs the parallel binary search and prints the result.
    result = binary_search_parallel(list, size, key);
    if (result != -1) {
        printf("Key found at index %d\n", result);
    } else {
        printf("Key not found\n");
    }
    
    // Stop the timer and calculate the elapsed time.
    clock_t end = clock();
    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %f seconds\n", time_elapsed); // Print the total execution time.
    
    return 0;
}

void bubble_sort(int list[], int size) {
    int temp, i, j;
    int swapped;
    do {
        swapped = 0;
        #pragma omp parallel for private(temp, j) shared(list) reduction(+:swapped)
        for (i = 0; i < size - 1; i++) {
            if (list[i] > list[i + 1]) {
                temp = list[i];
                list[i] = list[i + 1];
                list[i + 1] = temp;
                swapped = 1; // A flag to keep track if any swapping happened.
            }
        }
    } while (swapped != 0); // Repeat until no swapping is needed, indicating the array is sorted.
}

int binary_search_parallel(int list[], int size, int key) {
    int index = -1;
    #pragma omp parallel
    {
        int start, end, mid, tid, nthreads;
        tid = omp_get_thread_num(); // Gets the thread number in the current parallel block.
        nthreads = omp_get_num_threads(); // Gets the total number of threads.
        start = tid * size / nthreads; // Divides the array among the threads.
        end = (tid + 1) * size / nthreads - 1;

        // Binary search within the segment assigned to this thread.
        while (start <= end) {
            mid = start + (end - start) / 2;
            if (list[mid] == key) {
                #pragma omp critical
                {
                    index = mid; // Updates the result within a critical section.
                }
                break; // Exit the loop once the element is found.
            } else if (list[mid] < key) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
    }
    return index; // Returns the index of the found key or -1 if not found.
}
