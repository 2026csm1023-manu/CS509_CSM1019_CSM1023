Repository contains the Lab assignment .

## Student Details
Assignment Mode: Buddy Task

**Student 1**
- Name: Karan Patel
- Entry Number: 2026CSM1019

**Student 2**
- Name: Manvendra Singh
- Entry Number: 2026CSM1023

## Language and Environment

- Language: C++
- Compiler: g++
- Compiler Version: 16.1.0
- C++ Standard: C++17
- Operating System: Windows


## Repository Structureh
CS509_CSM1019_CSM1023/
│
├── README.md
├── common_wrapper/
│   └── wrapper.cpp
│
└── assignment1/
    ├── driver/
    │   ├── driver.cpp
    │   ├── timer.cpp
    │   └── timer.h
    │
    ├── include/
    │   ├── graph.h
    │   ├── csr.h
    │   ├── bfs.h
    │   ├── dfs.h
    │   ├── sssp.h
    │   └── printer.h
    │
    ├── src/
    │   ├── graph.cpp
    │   ├── csr.cpp
    │   ├── bfs.cpp
    │   ├── dfs.cpp
    │   ├── sssp.cpp
    │   └── printer.cpp
    │
    ├── tests/
    ├── test_output/
    ├── Makefile
    └── README.md


## Common Wrapper: Build and Usage

The common wrapper provides a single interface for accessing the assignments in this repository.






# Assignment 01 - Graph Algorithms

## Objective

The objective of this assignment is to implement BFS, DFS and Single Source Shortest Path algorithms using CSR (Compressed Sparse Row) representation.

The graph is given as an adjacency list in the input file. It is first converted to Graph and then to  CSR and then the selected algorithm is executed.

## Algorithm / Approach

### BFS

Breadth First Search is implemented using a queue.
The algorithm starts from the given source vertex and visits the graph level by level.
The program produces:
- BFS traversal
- Minimum edge distance from the source to every vertex
Unreachable vertices are represented as `INF`.

### DFS

Depth First Search is implemented using a stack.
The algorithm starts from the source vertex and continues visiting unvisited neighbouring vertices until traversal is complete.
The output contains the DFS traversal starting from the source.

### SSSP

Single Source Shortest Path is implemented using Dijkstra's algorithm.
A priority queue is used to select the vertex having the minimum current distance.
The output contains the shortest distance from the source to every vertex.
Unreachable vertices are represented as `INF`.




## Input Format

### BFS and DFS

Input graphs are unweighted.

```text
V E
vertex degree neighbour1 neighbour2 ...
vertex degree neighbour1 neighbour2 ...
...
SOURCE source
```

Example:

```text
5 5
0 2 1 2
1 2 0 3
2 3 0 3 4
3 2 1 2
4 1 2
SOURCE 0
```

### SSSP

SSSP uses a weighted graph.

```text
V E
vertex degree neighbour1 weight1 neighbour2 weight2 ...
...
SOURCE source
```

All edge weights must be positive.


## Helper Functions / CSR Conversion

The graph is first read from the input file as an adjacency list.

Before running BFS, DFS or SSSP, the adjacency list is converted into CSR representation.

The CSR structure contains:

- `row_ptr` - starting position of neighbours for each vertex
- `col_idx` - neighbour vertex numbers
- `values` - edge weights

CSR conversion is treated as preprocessing and is not included in algorithm execution time.

## File Structure

- `driver/driver.cpp` - main driver program
- `driver/timer.cpp` - execution timer
- `driver/timer.h` - timer declarations
- `src/graph.cpp` - reads and validates graph input
- `src/csr.cpp` - converts adjacency list to CSR
- `src/bfs.cpp` - BFS implementation
- `src/dfs.cpp` - DFS implementation
- `src/sssp.cpp` - SSSP implementation
- `src/printer.cpp` - writes algorithm results to output files
- `include/` - header files
- `tests/` - test input files
- `test_output/` - generated output files
- `Makefile` - compilation instructions


Using Makefile:

```bash
make
```

Direct compilation:

```bash
g++ -std=c++17 driver/driver.cpp driver/timer.cpp src/graph.cpp src/csr.cpp src/bfs.cpp src/dfs.cpp src/sssp.cpp src/printer.cpp -o program
```




## Execution

Run the compiled program using:

```powershell
.\program
```

The program provides the following algorithm choices:

```text
1. BFS
2. DFS
3. SSSP
```

After selecting an algorithm, the user can:

```text
1. Run one test
2. Run all tests
```

For a single test, enter the required test filename.

Example:

```text
bfs_10.txt
```

The result is stored in the `test_output/` directory.

For example:

```text
tests/bfs_10.txt
        ->
test_output/bfs_10_output.txt
```


## Runtime Measurement

Only the execution of the selected graph algorithm is timed.

The following are NOT included in the measured time:

- File reading
- Input parsing
- Adjacency list creation
- CSR conversion
- Output formatting
- Writing output to files

The timer starts immediately before the BFS, DFS or SSSP call and stops immediately after the algorithm finishes.

Execution time is reported in milliseconds (ms).


## Test Cases and Result Table

## 9.2 Graph Results Table

| Algorithm | Test File | Vertices | Input Type | Source | Actual Output | Time (ms) | Status |
|-----------|-----------|----------|------------|--------|---------------|-----------|--------|
| BFS | bfs_10.txt | 10 | Unweighted adjacency list | 0 | Traversal + Distances | 0.0049 | Pass |
| BFS | bfs_100.txt | 100 | Unweighted adjacency list | 0 | Traversal + Distances | 0.0254 | Pass |
| BFS | bfs_10000.txt | 10000 | Unweighted adjacency list | 0 | Traversal + Distances | 1.3473 | Pass |
| BFS | bfs_50000.txt | 50000 | Unweighted adjacency list | 0 | Traversal + Distances | 8.1486 | Pass |
| BFS | bfs_100000.txt | 100000 | Unweighted adjacency list | 0 | Traversal + Distances | 20.0509 | Pass |
| DFS | dfs_10.txt | 10 | Unweighted adjacency list | 0 | Traversal | 0.0067 | Pass |
| DFS | dfs_100.txt | 100 | Unweighted adjacency list | 0 | Traversal | 0.0256 | Pass |
| DFS | dfs_10000.txt | 10000 | Unweighted adjacency list | 0 | Traversal | 2.2615 | Pass |
| DFS | dfs_50000.txt | 50000 | Unweighted adjacency list | 0 | Traversal | 11.1441 | Pass |
| DFS | dfs_100000.txt | 100000 | Unweighted adjacency list | 0 | Traversal | 31.1874 | Pass |
| SSSP | sssp_10.txt | 10 | Positive weighted adjacency list | 0 | Shortest Distances | 0.0058 | Pass |
| SSSP | sssp_100.txt | 100 | Positive weighted adjacency list | 0 | Shortest Distances | 0.0712 | Pass |
| SSSP | sssp_10000.txt | 10000 | Positive weighted adjacency list | 0 | Shortest Distances | 6.7052 | Pass |
| SSSP | sssp_50000.txt | 50000 | Positive weighted adjacency list | 0 | Shortest Distances | 38.6705 | Pass |
| SSSP | sssp_100000.txt | 100000 | Positive weighted adjacency list | 0 | Shortest Distances | 80.0717 | Pass |








## Complexity

### BFS

- Time Complexity: `O(V + E)`
- Space Complexity: `O(V)` excluding graph storage

### DFS

- Time Complexity: `O(V + E)`
- Space Complexity: `O(V)` excluding graph storage

### SSSP

Using Dijkstra's algorithm with a priority queue:

- Time Complexity: `O((V + E) log V)`
- Space Complexity: `O(V)` excluding graph storage



