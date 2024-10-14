# Lab1-GEMM

The lab consists of two parts:
- **Part 1**: Optimizing matrix multiplication.
- **Part 2**: Implementing the `im2col` algorithm.

## Project Structure

```bash
.
├── im2col                            # im2col implementation (for Part 2)
│   ├── im2col.cpp                    # Source code for im2col algorithm
│   ├── run_im2col.sh                 # Script to run the im2col algorithm
│   └── test                          # Test files for im2col
│       ├── run_test_im2col.sh        # Script to run im2col test
│       └── test_im2col.cpp           # Source code for testing im2col
├── log
│   └── res.txt                       # Log file containing results of the matrix multiplication
└── matmul_optimization               # Matrix multiplication optimization (for Part 1)
    ├── include                       # Head files for the project
    │   ├── common.h                  # Common utility functions and definitions
    │   ├── matmul.h                  # Head file for matrix multiplication functions
    │   ├── optimize.h                # Head file for optimization techniques
    │   └── utils.h                   # Utility functions for the project
    ├── loop_unrolling.cpp            # Implementation of loop unrolling optimization
    ├── main.cpp                      # Main entry point for running matrix multiplication
    ├── matmul.cpp                    # Basic matrix multiplication implementation
    ├── run_matmul.sh                 # Script to run matrix multiplication
    └── tiling.cpp                    # Implementation of tiling optimization
```

## How to Run

### matmul (optimization)

To run the matrix multiplication optimizations, simply execute the provided run script. There are three aspects that can be adjusted based on your testing needs:

- **Add the function to be tested**: In the `main.cpp` file, you can add or modify the matrix multiplication function that you want to test.

- **Modify matrix size**: In the `common.h`, you can modify the variable `n` to change the size of the matrix.

- **Adjust tile size**: In `tiling.cpp`, you can modify the `TILE_SIZE` value to experiment with different tile sizes in the tiling optimization.

### im2col
To run the `im2col` algorithm, simply execute the provided script in the `im2col` directory.

#### im2col Test

In the `im2col/test` directory, there is a test file (`test_im2col.cpp`) that demonstrates the process of the `im2col` algorithm. This test can print both the matrix before and after applying `im2col`, allowing you to visually verify the correctness of the algorithm.

