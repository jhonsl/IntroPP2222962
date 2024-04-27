#!/bin/bash
#SBATCH --job-name=PostmanSortOMP
#SBATCH --output=output_postmanSortOMP.txt
#SBATCH --error=error_postmanSortOMP.txt   
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4  
#SBATCH --time=00:10:00
#SBATCH --mem=1G

# Cargar el módulo necesario
module load devtools/gcc/9.2.0

./mpi_postmanSort << EOF
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