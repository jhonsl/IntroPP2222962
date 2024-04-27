#include <stdio.h>
#include <time.h>
#include <omp.h> // Include the OpenMP header

// Autor: Jhon Edinson Salazar Lemus
// Codigo: 2222962

void arrange(int, int);  // Function prototype declaration
int array[100], array1[100];
int i, j, temp, max, count, maxdigits = 0, c = 0;

int main() {
    double start_time = omp_get_wtime(); // Start measuring total execution time of the program using OpenMP.

    printf("Enter the size of the array: ");
    scanf("%d", &count);
    printf("Enter the elements of the array: ");
    for (i = 0; i < count; i++) {
        scanf("%d", &array[i]);
        array1[i] = array[i];
    }

    // Print the original array as it was entered
    printf("\nOriginal array: \n");
    for (i = 0; i < count; i++) {
        printf("%d ", array1[i]);
    }
    
    int t, n = 1;
    #pragma omp parallel for private(t, c) shared(maxdigits, array)
    for (i = 0; i < count; i++) {
        t = array[i];
        c = 0;  // Reset digit count for each number
        while (t > 0) {
            c++;
            t = t / 10;
        }
        #pragma omp critical
        {
            if (maxdigits < c) {
                maxdigits = c;  // Update maximum number of digits
            }
        }
    }
    
    #pragma omp parallel for private(t)
    for (t = 0; t < maxdigits - 1; t++) {
        n *= 10;
    }

    #pragma omp parallel for private(j, t, temp) shared(array, array1)
    for (i = 0; i < count; i++) {
        max = array[i] / n;
        t = i;
        for (j = i + 1; j < count; j++) {
            if (max > (array[j] / n)) {
                max = array[j] / n;
                t = j;
            }
        }
        temp = array1[t];
        array1[t] = array1[i];
        array1[i] = temp;
        temp = array[t];
        array[t] = array[i];
        array[i] = temp;
    }

    // Parallelize this loop might require careful handling of the shared and private variables
    for (i = 0; i < count; ) {
        int t1 = array[i] / n;
        int end = i + 1;
        while (end < count && array[end] / n == t1) {
            end++;
        }
        arrange(i, end);
        i = end;
    }

    printf("\n\nSorted array (Postman sort): \n");
    for (i = 0; i < count; i++)
        printf("%d ", array1[i]);

    double end_time = omp_get_wtime();
    double time_elapsed = end_time - start_time;
    printf("\n\nTime elapsed: %f seconds\n", time_elapsed); // Print the total execution time.

    return 0;
}

void arrange(int k, int n) {
    int i, j, temp;
    for (i = k; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (array1[i] > array1[j]) {
                temp = array1[i];
                array1[i] = array1[j];
                array1[j] = temp;
            }
        }
    }
}
