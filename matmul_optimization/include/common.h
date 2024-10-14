#ifndef COMMON_H
#define COMMON_H

constexpr int n = 1024;
extern int A[n][n];
extern int B[n][n];
extern int BT[n][n];
extern int AT[n][n];
extern int C[n][n];
extern int C_groundtruth[n][n];

void init();
void test();
void run_test(void (*matmul_func)(), const char* func_name);

#endif
