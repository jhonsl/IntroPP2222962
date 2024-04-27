#!/bin/bash
#SBATCH --job-name=postmanSortMPI  
#SBATCH --output=output_postmanSortMPI.txt
#SBATCH --error=error_postmanSortMPI.txt   
#SBATCH --ntasks=4                   
#SBATCH --nodes=1                    
#SBATCH --time=00:10:00               
#SBATCH --mem=1G                     

module load devtools/mpi/openmpi/4.1.2

mpirun -np $SLURM_NTASKS ./mpi_postmanSort << EOF
100  
40
26
72
36
91
68
96
12
43
47
34
46
95
43
32
26
82
74
60
69
70
14
88
12
18
59
17
37
48
85
15
57
49
68
83
58
12
57
76
15
40
77
32
9
48
17
72
93
8
30
36
52
68
47
44
63
85
1
99
89
67
69
13
36
78
11
79
26
37
2
58
64
83
36
83
19
18
25
88
12
43
32
11
12
2
4
55
44
3
21
14
32
16
54
32
67
66
54
32
1
EOF