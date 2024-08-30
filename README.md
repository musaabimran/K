
# Top K Shortest Path Problem

# Parallel Solution for the Top K Shortest Path Problem

## Problem Description
The task is to implement a parallel solution for the Top K Shortest Path Problem using MPI (Message Passing Interface) and OpenMP (Open Multi-Processing). The solution will involve reading a graph from a file, initializing a distance matrix, and applying parallelization techniques to efficiently compute the Kth shortest path.

## Solution Outline

### 1. Input
- **Graph Representation**: The input graph is a weighted graph. The graph should be provided in a file format that can be easily parsed. Each line of the file typically represents an edge with a source vertex, a destination vertex, and a weight.
- **Pre-processing**: Depending on the format of the input file, you may need to perform some pre-processing to convert the graph into a format suitable for the algorithm.

### 2. Initialization
- **Distance Matrix Initialization**: 
  - Create a distance matrix `D` where `D[i][j]` represents the weight of the edge between vertex `i` and vertex `j`.
  - Set `D[i][i]` to `0` since the distance from any vertex to itself is zero.
  - Set `D[i][j]` to infinity (`∞`) for all pairs `(i, j)` where there is no direct edge between `i` and `j`.

### 3. Parallelization Strategy
- **MPI Parallelization**:
  - Divide the graph into subgraphs, and assign each subgraph to an MPI process.
  - Each MPI process is responsible for computing the Kth shortest path within its subgraph.
  - After local computations, MPI processes exchange results to combine the local solutions into the global solution.

- **OpenMP Parallelization**:
  - Within each MPI process, use OpenMP to parallelize the loops that compute the shortest paths.
  - This could involve parallelizing the iteration over vertices or edges, depending on the algorithm used.
  - Ensure that shared data structures are appropriately synchronized to avoid race conditions.

### 4. Implementation Steps

#### a. Setup and Preprocessing
- Parse the input graph file and set up the initial distance matrix.
- Distribute the subgraphs among MPI processes.

#### b. MPI-Based Parallel Computation
- Distribute the workload across multiple MPI processes.
- Each process computes local shortest paths.

#### c. OpenMP-Based Parallelization
- Within each MPI process, parallelize the inner loops using OpenMP.
- Ensure that critical sections are synchronized.

#### d. Combining Results
- Use MPI to gather the local results from all processes.
- Compute the final Top K shortest paths based on the combined results.
Instructions for Compilation and Execution:

### 5. Execution 
    For Serial execution:

    g++ -o [executable name] [codefile].cpp
    ./[executable name]


    For Parallel execution:

    mpic++ -o [executable name] [codefile].cpp
    mpirun -n [process count] -f [machinefile] ./[executable name]



Option appears “Enter File to Read :” and the following options appear

[1]doctorwho.csv

[2]Email-Euron.txt

[3]Email-EuAll.txt
