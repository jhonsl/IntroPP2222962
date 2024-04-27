![image](https://github.com/jhonsl/IntroPP2222962/assets/69093836/088dec2f-aabe-4530-8ed0-021c23fb3ce3)# Proyecto de Ordenamiento con OpenMP y MPI

## Descripción del Proyecto

Este proyecto implementa un algoritmo de ordenamiento que utiliza tanto MPI (Message Passing Interface) como OpenMP (Open Multi-Processing) para mejorar el rendimiento en entornos de computación de alto rendimiento (HPC). El objetivo es demostrar cómo las técnicas de paralelización pueden mejorar significativamente el tiempo de ejecución para tareas intensivas de computación, como el ordenamiento de grandes conjuntos de datos.

## Estructura del Código

El repositorio incluye los siguientes archivos:

-   `mpi_postmanSort.c`: Código principal utilizando MPI para distribuir la carga de trabajo en múltiples nodos.
-   `omp_postmanSort.c`: Versión que utiliza OpenMP para el paralelismo a nivel de hilos en un único nodo.
-   `run_mpi_postmanSort.sbatch`: Script para ejecutar `mpi_postmanSort.c` en un sistema con SLURM usando sbatch.
-   `run_omp_postmanSort.sbatch`: Script para ejecutar `omp_postmanSort.c` en un sistema con SLURM usando sbatch.

## Instrucciones de Compilación y Ejecución

### Compilación

#### Para MPI:

```bash
module load devtools/mpi/openmpi/4.1.2
mpicc -o mpi_postmanSort mpi_postmanSort.c
```

#### Para OpenMP:

```bash
module load devtools/gcc/9.2.0
gcc -fopenmp -o omp_postmanSort omp_postmanSort.c
```

### Compilación en Modo Interactivo

#### Para MPI:

```bash
module load devtools/mpi/openmpi/4.1.2
mpirun -np 4 ./mpi_postmanSort
```

#### Para OpenMP:

```bash
module load devtools/gcc/9.2.0
export OMP_NUM_THREADS=4
./omp_postmanSort
```

### Ejecución en Modo Pasivo (usando sbatch)

```bash
sbatch run_mpi_sort.sbatch
sbatch run_omp_sort.sbatch
```

## Tiempos de Ejecución y Análisis de Resultados

-   **Original (Serial)**: `0.000000 seconds`
  
  ![image](https://github.com/jhonsl/IntroPP2222962/assets/69093836/a8a029b1-637d-478e-9cf9-07106dbf4144)

-   **MPI**: `0.000088 seconds`
  
  ![image](https://github.com/jhonsl/IntroPP2222962/assets/69093836/24902ce4-79ed-4513-a541-1cffc54763be)

-   **OpenMP**: `0.000057 seconds`
  
  ![image](https://github.com/jhonsl/IntroPP2222962/assets/69093836/c4bf1c26-208c-4ce6-bc7c-e24fbe2c6bd1)


Estos tiempos muestran que, aunque la versión MPI tiene un tiempo ligeramente mayor, esto se debe principalmente a la sobrecarga de la inicialización y comunicación de MPI. La versión OpenMP muestra una mejora significativa en el tiempo de ejecución, aprovechando efectivamente la arquitectura de memoria compartida para reducir el tiempo de procesamiento. La implementación OpenMP fue la más rápida debido a su eficiencia en la utilización de recursos computacionales locales y menor sobrecarga en comparación con MPI en este contexto específico de una carga de trabajo relativamente pequeña.
