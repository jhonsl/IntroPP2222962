#include <stdio.h>
#include <time.h>


void arrange(int, int);  // Function prototype declaration
int array[100], array1[100];
int i, j, temp, max, count, maxdigits = 0, c = 0;

int main() {
    clock_t start = clock(); // Start measuring total execution time of the program.
    int t, n = 1;

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
    for (i = 0; i < count; i++) {
        t = array[i];
        c = 0;  // Reset digit count for each number
        while (t > 0) {
            c++;
            t = t / 10;
        }
        if (maxdigits < c)
            maxdigits = c;  // Update maximum number of digits
    }
    for (t = 0; t < maxdigits - 1; t++)
        n *= 10;

    for (i = 0; i < count; i++) {
        max = array[i] / n;
        int t = i;
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

    for (i = 0; i < count; ) {
        int t1 = array[i] / n;
        for (j = i + 1; j < count && t1 == (array[j] / n); j++);
        arrange(i, j);
        i = j;
    }
    n /= 10;

    printf("\n\nSorted array (Postman sort): \n");
    for (i = 0; i < count; i++)
        printf("%d ", array1[i]);

    // Stop the timer and calculate the elapsed time.
    clock_t end = clock();
    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n\nTime elapsed: \n%f seconds\n", time_elapsed); // Print the total execution time.

    return 0;
}

// Function to sort a sequence of numbers with the same base
void arrange(int k, int n) {
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
