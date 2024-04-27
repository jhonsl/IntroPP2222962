#include <stdio.h>
#include <mpi.h>

// Autor: Jhon Edinson Salazar Lemus
// Codigo: 2222962

// Function prototype declaration
void arrange(int, int);
int array[100], array1[100];
int i, j, temp, max, count, maxdigits = 0, c = 0;

void arrange(int k, int n) {
    int i, j, temp;
    for (i = k; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (array1[i] > array1[j]) {
                temp = array1[i];
                array1[i] = array1[j];
                array1[j] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size, t, n = 1;

    MPI_Init(&argc, &argv);  // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the number of processes

    // Only the root process will handle the input and output
    if (rank == 0) {
        printf("Enter the size of the array: ");
        scanf("%d", &count);
        printf("Enter the elements of the array: ");
        for (i = 0; i < count; i++) {
            scanf("%d", &array[i]);
            array1[i] = array[i];
        }
    }

    // Broadcast the size and the array to all processes
    MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(array, count, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(array1, count, MPI_INT, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime(); // Start measuring time

    if (rank == 0) {
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
            int temp_index = i;
            for (j = i + 1; j < count; j++) {
                if (max > (array[j] / n)) {
                    max = array[j] / n;
                    temp_index = j;
                }
            }
            temp = array1[temp_index];
            array1[temp_index] = array1[i];
            array1[i] = temp;
            temp = array[temp_index];
            array[temp_index] = array[i];
            array[i] = temp;
        }

        for (i = 0; i < count; ) {
            int t1 = array[i] / n;
            for (j = i + 1; j < count && t1 == (array[j] / n); j++);
            arrange(i, j);
            i = j;
        }

        printf("\n\nSorted array (Postman sort): \n");
        for (i = 0; i < count; i++)
            printf("%d ", array1[i]);

        // Calculate and print the elapsed time
        double end_time = MPI_Wtime();
        double time_elapsed = end_time - start_time;
        printf("\n\nTime elapsed: %f seconds\n", time_elapsed);
    }

    MPI_Finalize();
}
