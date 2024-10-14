#include <cassert>
#include <iostream>
#include "common.h"
#include "matmul.h"
#include "optimize.h"
#include "utils.h"

int A[n][n];
int B[n][n];
int BT[n][n];
int AT[n][n];
int C[n][n];
int C_groundtruth[n][n];

void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand();
            B[i][j] = rand();
            C_groundtruth[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C_groundtruth[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void test() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            assert(C[i][j] == C_groundtruth[i][j]);
        }
    }
}

void run_test(void (*matmul_func)(), const char* func_name) {
    float avg_time = 0.0f;
    init();
    for (int K = 0; K < 32; K++) {
        auto t = get_time();
        matmul_func();
        test();
        printf("%f\n", get_time() - t);
        avg_time += get_time() - t;
    }
    printf("%s Avg Time for Calculation: %f\n", func_name, avg_time / 32);

    FILE* fp = fopen("../log/res.txt", "a");
    fprintf(fp, "%d %s %f\n", n, func_name, avg_time / 32);
    fclose(fp);
}

int main() {
    run_test(matmul, "matmul");
    run_test(matmul_ikj, "matmul_ikj");
    run_test(matmul_AT, "matmul_AT");
    run_test(matmul_BT, "matmul_BT");
    run_test(matmul_tiling, "matmul_tiling");
    run_test(matmul_tiling_unrolling_4, "matmul_tiling_unrolling_4");
    run_test(matmul_tiling_unrolling_8, "matmul_tiling_unrolling_8");
    run_test(matmul_tiling_unrolling_16, "matmul_tiling_unrolling_16");
    run_test(matmul_tiling_unrolling_32, "matmul_tiling_unrolling_32");
    run_test(matmul_unrolling_2, "matmul_unrolling_2");
    run_test(matmul_unrolling_4, "matmul_unrolling_4");
    run_test(matmul_unrolling_8, "matmul_unrolling_8");
    run_test(matmul_unrolling_16, "matmul_unrolling_16");
    run_test(matmul_unrolling_32, "matmul_unrolling_32");
    run_test(matmul_unrolling_64, "matmul_unrolling_64");
    run_test(matmul_unrolling_128, "matmul_unrolling_128");
    return 0;
}
