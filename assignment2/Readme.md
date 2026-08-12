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

## Repository Structure

CS509_CSM1019_CSM1023/
│
├── README.md
├── common_wrapper/
│   └── wrapper.cpp
│
└── assignment2/
    ├── driver/
    │   ├── driver.cpp
    │   ├── printer.cpp
    │   ├── printer.h
    │   ├── reader.cpp
    │   ├── reader.h
    │   ├── timer.cpp
    │   └── timer.h
    │
    ├── include/
    │   ├── graph.h
    │   ├── csr.h
    │   ├── triangle_count.h
    │   ├── betweenness.h
    │   └── connected_components.h
    │
    ├── src/
    │   ├── graph.cpp
    │   ├── csr.cpp
    │   ├── triangle_count.cpp
    │   ├── betweenness.cpp
    │   └── connected_components.cpp
    │
    ├── tests/
    ├── test_output/
    └── README.md


## Common Wrapper

The common wrapper provides a single interface for accessing the assignments in this repository.

# Assignment 02 - Graph Analytics

## Objective

The objective of this assignment is to implement Triangle Counting,
Betweenness Centrality and Connected Components using CSR
(Compressed Sparse Row) representation.

The graph is given as an adjacency list in the input file. It is first
converted into the graph representation and then into CSR. After that,
the selected algorithm is executed.

All three algorithms in this part use unweighted undirected graphs.


## Algorithm / Approach

### Triangle Counting

Triangle Counting finds groups of three vertices where every vertex is
connected to the other two.

For every vertex, the algorithm checks pairs of its neighbours and
checks whether those neighbours are also connected.

The adjacency lists are sorted before converting the graph to CSR. This
makes the common-neighbour checks faster.

The program produces:

- Total number of triangles
- Individual triangles for the smaller test cases

For example, for the smallest test cases the output can contain:

```text
Total triangles: 3

Triangles found:
(0, 1, 2)
(1, 2, 3)
(3, 4, 5)
```

The assignment requires listing individual triangles for the two
smallest graph sizes. For larger graphs only the total count is
printed.


### Betweenness Centrality

Betweenness Centrality measures how often a vertex occurs on shortest
paths between other pairs of vertices.

A vertex with a high value can be considered more important as a bridge
between different parts of the graph.

For the unweighted graphs, Brandes' algorithm is used. The algorithm
performs BFS from every vertex and then calculates the centrality value.

The program prints the raw centrality value for every vertex.

The values are printed to two decimal places.

Example:

```text
Algorithm: Betweenness Centrality
Vertex Centrality
0 0.00
1 3.00
2 4.00
3 3.00
4 0.00
```

The values are not normalized.


### Connected Components

Connected Components finds the separate groups of vertices in an
undirected graph.

A new traversal is started whenever an unvisited vertex is found.
Vertices reached by the same traversal are assigned the same component
number.

The program produces:

- Number of connected components
- Component number of every vertex

Example:

```text
Algorithm: Connected Components
Number of components: 4

Vertex Component
0 0
1 0
2 0
3 0
4 1
5 1
6 2
7 3
```

Component numbers start from 0 and are assigned in the order in which
the components are discovered.


## Input Format

All three algorithms use an unweighted undirected adjacency-list graph.

```text
V E
vertex degree neighbour1 neighbour2 ...
vertex degree neighbour1 neighbour2 ...
...
SOURCE is not required
```

Example:

```text
6 8
0 2 1 2
1 3 0 2 3
2 3 0 1 3
3 4 1 2 4 5
4 2 3 5
5 2 3 4
```

Here:

- `V` is the number of vertices
- `E` is the number of undirected edges
- `degree` is the number of neighbours of that vertex
- Each undirected edge is present in the adjacency list of both
  endpoints

There is no `SOURCE` line because all three algorithms work on the
whole graph.

A vertex with no neighbours is written as:

```text
u 0
```


## Helper Functions / CSR Conversion

The graph is first read from the input file as an adjacency list.

The adjacency lists are sorted and then converted into CSR
representation before running the algorithm.

The CSR structure contains:

- `row_ptr` - starting and ending positions of neighbours
- `col_idx` - neighbour vertex numbers
- `values` - edge values

Since these graphs are unweighted, the edge values are set to 1.

The CSR conversion is treated as preprocessing and is not included in
the algorithm execution time.

The CSR conversion function from the previous assignment is reused
instead of copying the conversion code again.


## File Structure


- `driver/driver.cpp` - Main driver program and menu for selecting algorithms and tests
- `driver/reader.cpp` - Reads and validates graph data from test files
- `driver/reader.h` - Header file for graph input functions
- `driver/timer.cpp` - Execution timer
- `driver/timer.h` - Timer declarations
- `driver/printer.cpp` - Writes algorithm results and execution time to output files as per algorithm
- `driver/printer.h` - Printer function declarations
- `include/` - Header files for graph, CSR and algorithms
- `src/` - Implementations of CSR, Triangle Counting, Betweenness Centrality and Connected Components
- `tests/` - Input test files
- `test_output/` - Generated output files
- `Readme.md` - Assignment documentation


## Compilation

Using Makefile:

```bash
make
```

Direct compilation can be done using:

```bash
g++ -std=c++17 driver/driver.cpp driver/timer.cpp src/graph.cpp src/csr.cpp src/triangle_count.cpp src/betweenness_centrality.cpp src/connected_components.cpp src/printer.cpp -o program
```


## Execution

Run the compiled program using:

```powershell
.\program
```

The program provides the following algorithm choices:

```text
1. Triangle Counting
2. Betweenness Centrality
3. Connected Components
```

After selecting an algorithm, the user can:

```text
1. Run one test
2. Run all tests
```

For a single test, enter the required test filename.

Examples:

```text
tc_10.txt
bc_100.txt
cc_10000.txt
```

The result is stored in the `test_output/` directory.

For example:

```text
tests/tc_10.txt
        ->
test_output/tc_10_output.txt
```


## Runtime Measurement

Only the execution of the selected graph algorithm is timed.

The following are NOT included in the measured time:

- File reading
- Input parsing
- Adjacency list creation
- Sorting the input adjacency lists
- CSR conversion
- Output formatting
- Writing output to files

The timer starts immediately before the algorithm call and stops
immediately after the algorithm finishes.

Execution time is reported in milliseconds (ms).

For very small inputs the execution time is very small, so the values
can be close to zero.


## Test Cases and Result Table

The Assignment 2 specification uses different graph sizes for the
three algorithms because their running times are different.

Triangle Counting and Connected Components use:

```text
10, 100, 10000, 50000, 100000
```

Betweenness Centrality uses:

```text
10, 100, 1000, 5000, 10000
```

The larger BC graphs are reduced because Brandes' algorithm takes
O(V * E) time.


### Graph Results Table

| Algorithm | Test File | Vertices | Input Type | Actual Output | Time (ms) | Status |
| --------- | --------- | -------- | ---------- | ------------- | --------- | ------ |
| Triangle Counting | tc_10.txt | 10 | Unweighted adjacency list | 10 triangles | 0.0102 | Pass |
| Triangle Counting | tc_100.txt | 100 | Unweighted adjacency list | 100 triangles | 0.0243 | Pass |
| Triangle Counting | tc_10000.txt | 10000 | Unweighted adjacency list | 10000 triangles | 1.1784 | Pass |
| Triangle Counting | tc_50000.txt | 50000 | Unweighted adjacency list | 50000 triangles | 5.6215 | Pass |
| Triangle Counting | tc_100000.txt | 100000 | Unweighted adjacency list | 100000 triangles | 11.1303 | Pass |
| Betweenness Centrality | bc_10.txt | 10 | Unweighted adjacency list | Centrality for 10 vertices | 0.09 | Pass |
| Betweenness Centrality | bc_100.txt | 100 | Unweighted adjacency list | Centrality for 100 vertices | 5.90 | Pass |
| Betweenness Centrality | bc_1000.txt | 1000 | Unweighted adjacency list | Centrality for 1000 vertices | 248.38 | Pass |
| Betweenness Centrality | bc_5000.txt | 5000 | Unweighted adjacency list | Centrality for 5000 vertices | 6153.71 | Pass |
| Betweenness Centrality | bc_10000.txt | 10000 | Unweighted adjacency list | Centrality for 10000 vertices | 24331.93 | Pass |
| Connected Components | cc_10.txt | 10 | Unweighted adjacency list | 4 components | 0.0052 | Pass |
| Connected Components | cc_100.txt | 100 | Unweighted adjacency list | 4 components | 0.0155 | Pass |
| Connected Components | cc_10000.txt | 10000 | Unweighted adjacency list | 4 components | 1.1429 | Pass |
| Connected Components | cc_50000.txt | 50000 | Unweighted adjacency list | 4 components | 4.9959 | Pass |


## Extra Small Test Cases

Some additional 5-vertex test cases were also used as small sanity
checks:

| Algorithm | Test File | Vertices | Result | Time (ms) |
| --------- | --------- | -------- | ------ | --------- |
| Triangle Counting | tc_5.txt | 5 | 3 triangles | 0.0026 |
| Betweenness Centrality | bc_5.txt | 5 | Centrality calculated for all vertices | 0.04 |
| Connected Components | cc_5.txt | 5 | 4 components | 0.0037 |

These tests are extra and are not part of the required graph sizes.


## Complexity

### Triangle Counting

The algorithm checks pairs of neighbours for each vertex.

For the straightforward implementation:

- Time Complexity: `O(sum(degree(v)^2))`
- Space Complexity: `O(V + E)` including the graph representation


### Betweenness Centrality

Brandes' algorithm runs a BFS from every vertex.

For an unweighted graph:

- Time Complexity: `O(V * E)`
- Space Complexity: `O(V + E)` excluding the CSR graph storage


### Connected Components

Connected Components uses graph traversal to visit every vertex and
edge once.

- Time Complexity: `O(V + E)`
- Space Complexity: `O(V)` excluding graph storage