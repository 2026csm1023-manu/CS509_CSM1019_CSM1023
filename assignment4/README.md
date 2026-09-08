# Assignment 04 - K-Means Clustering and FastMap

## Objective

This buddy-task assignment implements K-Means clustering for point data and
FastMap for embedding objects described by pairwise distances. The driver reads
and validates each input file, times only the algorithm call, and writes a
readable result file.

## Algorithms / Approach

### K-Means Clustering

K-Means partitions `N` points in `D` dimensions into `K` clusters. The first
`K` input points are used as initial centroids for reproducible results. Each
iteration assigns points to their closest centroid, recomputes non-empty
centroids as point means, and measures the largest centroid shift. The algorithm
stops when assignments no longer change, the maximum shift is at most the input
tolerance, or the iteration limit is reached. An empty cluster retains its
previous centroid. WCSS is calculated from the final assignments and centroids.

- Time complexity: `O(iterations * N * K * D)`
- Space complexity: `O(N + K * D)` in addition to the input points

### FastMap

FastMap embeds objects into a `k`-dimensional Euclidean coordinate space. For
each dimension, the implementation uses two deterministic farthest-point sweeps
to select an approximate farthest pivot pair. It projects every object by the
law of cosines and deflates later distances by subtracting the squared
contributions of previously generated coordinates. Residual distances are
computed on demand, avoiding an additional `N x N` distance-matrix copy.

- Time complexity: `O(N * k^2)` after reading the provided matrix
- Extra space complexity: `O(N * k)`

## Input Format

### K-Means

```text
N D K
<N lines, each containing D floating-point coordinates>
MAX_ITERATIONS n
TOLERANCE epsilon
```

### FastMap

```text
N K
<N rows of N non-negative, symmetric distance values>
```

The FastMap reader rejects non-zero diagonal values, negative distances, and
non-symmetric matrices. The K-Means reader rejects invalid dimensions, `K > N`,
or non-positive tolerance and iteration limits.

## Test Cases

`gen.cpp` creates the required deterministic test files using random seed 42.
FastMap matrices are derived from randomly generated 3-dimensional points, so
they satisfy the distance-matrix requirements.

| File | N | D / distance input | K / target dimensions | Maximum iterations |
|---|---:|---:|---:|---:|
| `km_01.txt` | 100 | 2 | 3 | 300 |
| `km_02.txt` | 1,000 | 2 | 5 | 300 |
| `km_03.txt` | 10,000 | 5 | 8 | 300 |
| `km_04.txt` | 100,000 | 5 | 10 | 300 |
| `fm_01.txt` | 10 | full `N x N` matrix | 2 | - |
| `fm_02.txt` | 100 | full `N x N` matrix | 2 | - |
| `fm_03.txt` | 1,000 | full `N x N` matrix | 3 | - |
| `fm_04.txt` | 10,000 | full `N x N` matrix | 3 | - |

`fm_04.txt` contains 100 million distance values, so ensure sufficient free
disk space and memory before generating or running that required test.

## Build and Run

Use C++17 from the `assignment4` directory:

```powershell
g++ -std=c++17 driver\driver.cpp driver\reader.cpp driver\printer.cpp driver\timer.cpp src\kmeans.cpp src\fastmap.cpp -o assignment4.exe
g++ -std=c++17 gen.cpp -o gen.exe
.\gen.exe
.\assignment4.exe
```

The program menu selects K-Means or FastMap, then runs one named test or all
four required tests. Results are written to `outputs/<test-name>_output.txt`.
The repository-level `common_wrapper` menu includes Assignment 4 and launches
`assignment4\assignment4.exe`.

## Timing

The timer starts immediately before `kmeans` or `fastmap` is called and stops
immediately after it returns. File reading, validation, output formatting, and
file writing are excluded from the reported execution time. Times are reported
in milliseconds.

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
- C++ Standard: C++17
- Compiler: g++
- Operating System: Windows
