README

### Descripción del Programa:

El programa `omp_code` es una aplicación de consola escrita en C++ que demuestra la búsqueda binaria, un algoritmo eficiente para encontrar un elemento en una lista ordenada. El proceso consta de dos partes principales: ordenación y búsqueda.

1. **Ordenación**: El programa recibe del usuario una lista de enteros de tamaño variable. Utiliza el algoritmo de burbuja, conocido por su simplicidad, para ordenar la lista. A pesar de que el algoritmo de burbuja no es el más eficiente para conjuntos de datos grandes, se ha seleccionado para fines educativos y de demostración. Para mejorar el rendimiento del proceso de ordenación, se aplica paralelización con OpenMP, una API de paralelismo en memoria compartida ampliamente utilizada.

2. **Búsqueda Binaria**: Tras ordenar la lista, el programa solicita al usuario que ingrese un 'key' para buscar. La búsqueda binaria divide repetidamente a la mitad el rango de números hasta que encuentra el 'key' o hasta que el rango se reduce a cero. Aunque el código inicial implementaba una búsqueda binaria recursiva, se ha adaptado una versión iterativa para explorar la viabilidad de su paralelización con OpenMP.

### Compilación y Ejecución:

-   **En máquinas locales**:

    -   Compilación: `g++ -fopenmp omp_code.cpp -o omp_code`
    -   Ejecución: `time ./omp_code`

-   **En GUANE-1**:
    -   Carga del módulo GCC (asegúrese de que la versión cargada soporte OpenMP): `module load compiler/gcc/9.2.0`
    -   Compilación: `g++ -fopenmp omp_code.cpp -o omp_code`
    -   Ejecución: Utilice un script de Slurm `code.sbatch` para enviar el trabajo al gestor de colas.

### Resumen de la Prueba
![image](https://github.com/jhonsl/IntroPP2222962/assets/69093836/449b02bb-6bf9-4329-8765-3db7ab973013)
![image](https://github.com/jhonsl/IntroPP2222962/assets/69093836/8d8c6aec-c507-4502-b62b-f1aea62b3131)

La salida proporcionada corresponde al resultado de una ejecución de prueba local del binario `omp_code`. La prueba se realizó para medir el rendimiento de los algoritmos de búsqueda binaria y ordenamiento de burbuja paralelizados, centrándose especialmente en las mejoras añadidas por la implementación de directivas OpenMP.

### Resultados de la Prueba

Las pruebas locales con gcc se llevaron a cabo en una lista de 20 enteros. Los resultados son los siguientes:

-   Se encontró con éxito la clave en la lista (lo que indica que los algoritmos funcionan según lo esperado).
-   Se muestra el tiempo total tomado para la ejecución (incluyendo tanto el ordenamiento como la búsqueda), mostrando la eficiencia del código.

En el procesado real se uso un array de 100 enteros, el resultado de este proceso se puede ver en el archivo output

![image](https://github.com/jhonsl/IntroPP2222962/assets/69093836/f6ac2189-790a-4ae9-887d-7277a39a3d2e)

### Conclusiones:

La ejecución de la versión paralelizada del programa en comparación con su contraparte secuencial muestra una disminución en el tiempo de ejecución. Este comportamiento se espera debido a que la ordenación paralela con OpenMP puede utilizar múltiples hilos para realizar el trabajo que de otro modo sería secuencial. Sin embargo, la magnitud de la mejora en el tiempo depende del tamaño del conjunto de datos y del número de núcleos de procesamiento utilizados.

En conjuntos de datos pequeños, la sobrecarga de la creación y gestión de los hilos de OpenMP puede contrarrestar las ganancias de rendimiento. En contraste, en conjuntos de datos más grandes, se espera que las mejoras sean más significativas. Además, factores como la caché del procesador y la especificidad de la arquitectura del sistema pueden influir en los resultados obtenidos.

Se observa que la búsqueda binaria paralela no presenta una mejora sustancial en comparación con su versión secuencial. Esto se debe a la dificultad de paralelizar eficientemente un algoritmo que depende de decisiones condicionales basadas en la comparación de elementos. En muchos casos, la búsqueda binaria es tan eficiente que la paralelización no resulta práctica ni beneficiosa.

Es crucial considerar que la paralelización no garantiza mejoras lineales y está sujeta a la ley de Amdahl, que postula que el aceleramiento proporcionado por un sistema paralelo está limitado por la fracción de tiempo que el sistema está realizando tareas que no pueden paralelizarse.

Para futuras implementaciones, se recomienda explorar algoritmos de ordenación más eficientes y adaptados a la paralelización, como QuickSort o MergeSort, y considerar estructuras de datos y algoritmos alternativos que se diseñen con la paralelización en mente desde el inicio.

### Referencias:

-   Documentación oficial de OpenMP: https://www.openmp.org/
-   "Structured Parallel Programming" por Michael McCool, Arch D. Robison y James Reinders.
-   "Parallel Programming in C with MPI and OpenMP" por Michael J. Quinn.
