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

## Repository Structure

```text
CS509_CSM1019_CSM1023/
│
├── README.md
├── common_wrapper/
│   └── wrapper.cpp
│
└── assignment3/
    ├── driver/
    ├── include/
    ├── src/
    ├── tests/
    └── test_output/
```

## Common Wrapper

The common wrapper provides a single interface for accessing the assignments in the repository.

# Assignment 03 - Gradient Descent and Maxflow-Mincut

## Objective

The objective of this assignment is to implement Gradient Descent and
Maxflow-Mincut.

Gradient Descent works on a generic one-variable polynomial and supports
the required polynomial degrees 2, 4, 6, 8 and 10.

Maxflow-Mincut works on a directed graph with edge capacities. The graph is
provided as an adjacency list and is converted to CSR before the algorithm
is executed.

The execution time reported for each test contains only the algorithm
execution time.

## Algorithm / Approach

### Gradient Descent

Gradient Descent is an iterative optimization algorithm used to find a
minimum of a function.

For this assignment, the function is represented as:

```text
f(x) = c0 + c1*x + c2*x^2 + ... + cd*x^d
```

The derivative is:

```text
f'(x) = c1 + 2*c2*x + 3*c3*x^2 + ... + d*cd*x^(d-1)
```

Starting from the given initial value, the algorithm updates `x` using:

```text
x_new = x - learning_rate * f'(x)
```

The process stops when:

```text
|f'(x)| <= tolerance
```

or when the maximum number of iterations is reached.

The same polynomial evaluation and derivative evaluation logic is used for
all required degrees instead of implementing separate functions for each
test case.

The program produces:

- Polynomial degree
- Final `x`
- Final `f(x)`
- Number of iterations
- Convergence status
- Execution time

### Maxflow-Mincut

Maxflow finds the maximum amount of flow that can be sent from a source
vertex to a sink vertex without exceeding the capacity of any directed
edge.

The algorithm works on a residual graph. After the maximum flow has been
calculated, the minimum cut is obtained from the final residual graph.

Starting from the source, all vertices reachable using edges with positive
residual capacity form the source side of the cut. The remaining vertices
form the sink side.

The capacities of the original edges going from the source side to the
sink side are summed to obtain the minimum-cut capacity.

The result must satisfy:

```text
Maximum Flow = Minimum Cut Capacity
```

The program produces:

- Source
- Sink
- Maximum flow
- Minimum cut capacity
- Source side of the minimum cut
- Sink side of the minimum cut
- Cut edges
- Execution time

## Input Format

### Gradient Descent

```text
DEGREE d
COEFFICIENTS c0 c1 c2 ... cd
INITIAL_X x0
LEARNING_RATE alpha
TOLERANCE epsilon
MAX_ITERATIONS n
```

The coefficients are given in increasing order of power.

For example:

```text
DEGREE 6
COEFFICIENTS 0 0 1 0 0.5 0 0.1
INITIAL_X 2
LEARNING_RATE 0.02
TOLERANCE 0.000001
MAX_ITERATIONS 20000
```

### Maxflow-Mincut

```text
V E
u0 degree neighbor1 capacity1 neighbor2 capacity2 ...
u1 degree neighbor1 capacity1 ...
...
u(V-1) degree ...
SOURCE s
SINK t
```

The graph is directed, so only outgoing edges are listed for each vertex.
Residual reverse edges are created internally by the max-flow algorithm.

## Output Format

### Gradient Descent

```text
Algorithm: Gradient Descent
Degree: <degree>
Final x: approximately <value>
Final f(x): approximately <value>
Iterations: <value>
Converged: true/false
Execution time: <value> ms
```

### Maxflow-Mincut

```text
Algorithm: Maxflow-Mincut
Source: <source>
Sink: <sink>
Maximum flow: <value>
Minimum cut capacity: <value>
Source side: <vertices>
Sink side: <vertices>
Cut edges:
<u> <v> <capacity>
...
Execution time: <value> ms
```

Different valid minimum cuts may produce different source/sink partitions
or cut-edge lists, but the cut capacity must equal the maximum flow.

## Helper Functions / CSR Conversion

The Maxflow-Mincut graph is first read from the input file as an adjacency
list and then converted into CSR representation before the algorithm runs.

The CSR structure contains:

- `row_ptr` - starting and ending positions of each vertex's neighbours
- `col_idx` - neighbouring vertex numbers
- `values` - edge capacities

CSR conversion is preprocessing and is not included in the algorithm
execution time.

Gradient Descent does not use CSR because it reads polynomial coefficients
and scalar optimization parameters directly from its input file.

## File Structure

- `driver/` - Main driver, input handling, timing and output handling
- `include/` - Header files for the graph structures and algorithms
- `src/` - Implementations of Gradient Descent and Maxflow-Mincut
- `tests/` - Input test files
- `test_output/` - Generated output files
- `README.md` - Assignment documentation

## Compilation

Using Makefile:

```bash
make
```

Direct compilation can be done using the source files in `driver/` and
`src/` with C++17.

## Execution

Run the compiled program using:

```powershell
.\program
```

The program provides the required algorithm/test selection through the
common wrapper or driver interface.

## Runtime Measurement

Only the execution of the selected algorithm is timed.

The following are NOT included in the measured time:

- File reading
- Input parsing
- Adjacency-list creation
- CSR conversion
- Output formatting
- Writing output files
- Other preprocessing/setup

The timer starts immediately before the algorithm call and stops
immediately after the algorithm finishes.

For Maxflow-Mincut, construction of the residual network from the prepared
CSR and minimum-cut extraction from the final residual graph are part of
the timed algorithm section.

Execution time is reported in milliseconds (ms).

## Test Cases and Result Table

### Gradient Descent Results

| Algorithm | Test File | Degree | Actual x | Actual f(x) | Iterations | Converged | Time (ms) | Status |
|---|---|---:|---:|---:|---:|---|---:|---|
| Gradient Descent | gd_01_output.txt | 2 | 0.000000 | 0.000000 | 0 | true | 0.003100 | Pass |
| Gradient Descent | gd_02_output.txt | 4 | 0.000000 | 0.000000 | 180 | true | 0.008100 | Pass |
| Gradient Descent | gd_03_output.txt | 6 | 0.000000 | 0.000000 | 349 | true | 0.021100 | Pass |
| Gradient Descent | gd_04_output.txt | 8 | 0.000000 | 0.000000 | 948 | true | 0.065200 | Pass |
| Gradient Descent | gd_05_output.txt | 10 | 0.000000 | 0.000000 | 2364 | true | 0.230700 | Pass |

### Maxflow-Mincut Test Cases

The required graph sizes are:

```text
10, 100, 1000, 10000, 50000
```

### Maxflow-Mincut Results

| Algorithm | Test File | Vertices | Source | Sink | Actual Flow | Cut Capacity | Time (ms) | Status |
|---|---|---:|---:|---:|---:|---:|---:|---|
| Maxflow-Mincut | maxflow_10_output.txt | 10 | 0 | 9 | 59 | 59 | 0 | Pass |
| Maxflow-Mincut | maxflow_100_output.txt | 100 | 0 | 99 | 108 | 108 | 0 | Pass |
| Maxflow-Mincut | maxflow_1000_output.txt | 1,000 | 0 | 999 | 27 | 27 | 0.999 | Pass |
| Maxflow-Mincut | maxflow_10000_output.txt | 10,000 | 0 | 9999 | 13 | 13 | 0.999 | Pass |
| Maxflow-Mincut | maxflow_50000_output.txt | 50,000 | 0 | 49999 | 1 | 1 | 27 | Pass |

For all supplied Maxflow-Mincut tests:

```text
Maximum Flow = Minimum Cut Capacity
```

## Complexity

### Gradient Descent

For a polynomial of degree `d`, evaluating the polynomial and its
derivative takes `O(d)` time per iteration.

If the algorithm performs `I` iterations:

- Time Complexity: `O(I * d)`
- Space Complexity: `O(d)`

### Maxflow-Mincut

The complexity depends on the maximum-flow algorithm used. For a Dinic
implementation:

- Time Complexity: `O(V^2 * E)` in the general case
- Space Complexity: `O(V + E)`

The minimum-cut extraction after maxflow is a graph traversal and takes:

- Time Complexity: `O(V + E)`
- Space Complexity: `O(V)`

The CSR graph storage itself requires `O(V + E)` space.
