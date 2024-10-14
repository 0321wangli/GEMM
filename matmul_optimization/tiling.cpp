#define TILE_SIZE 64
#include <cstring>
#include "common.h"

void matmul_tiling() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i += TILE_SIZE) {
        for (int j = 0; j < n; j += TILE_SIZE) {
            for (int k = 0; k < n; k += TILE_SIZE) {
                for (int ii = i; ii < i + TILE_SIZE; ii++) {
                    for (int jj = j; jj < j + TILE_SIZE; jj++) {
                        for (int kk = k; kk < k + TILE_SIZE; kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

void matmul_tiling_unrolling_4() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i += TILE_SIZE) {
        for (int j = 0; j < n; j += TILE_SIZE) {
            for (int k = 0; k < n; k += TILE_SIZE) {
                for (int ii = i; ii < i + TILE_SIZE; ii++) {
                    for (int jj = j; jj < j + TILE_SIZE; jj++) {
                        for (int kk = k; kk < k + TILE_SIZE; kk += 4) {
                            C[ii][jj] +=
                                A[ii][kk] * B[kk][jj] + A[ii][kk + 1] * B[kk + 1][jj] + A[ii][kk + 2] * B[kk + 2][jj] + A[ii][kk + 3] * B[kk + 3][jj];
                        }
                    }
                }
            }
        }
    }
}

void matmul_tiling_unrolling_8() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i += TILE_SIZE) {
        for (int j = 0; j < n; j += TILE_SIZE) {
            for (int k = 0; k < n; k += TILE_SIZE) {
                for (int ii = i; ii < i + TILE_SIZE; ii++) {
                    for (int jj = j; jj < j + TILE_SIZE; jj++) {
                        for (int kk = k; kk < k + TILE_SIZE; kk += 8) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj] + A[ii][kk + 1] * B[kk + 1][jj] + A[ii][kk + 2] * B[kk + 2][jj] +
                                         A[ii][kk + 3] * B[kk + 3][jj] + A[ii][kk + 4] * B[kk + 4][jj] + A[ii][kk + 5] * B[kk + 5][jj] +
                                         A[ii][kk + 6] * B[kk + 6][jj] + A[ii][kk + 7] * B[kk + 7][jj];
                        }
                    }
                }
            }
        }
    }
}

void matmul_tiling_unrolling_16() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i += TILE_SIZE) {
        for (int j = 0; j < n; j += TILE_SIZE) {
            for (int k = 0; k < n; k += TILE_SIZE) {
                for (int ii = i; ii < i + TILE_SIZE; ii++) {
                    for (int jj = j; jj < j + TILE_SIZE; jj++) {
                        for (int kk = k; kk < k + TILE_SIZE; kk += 16) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj] + A[ii][kk + 1] * B[kk + 1][jj] + A[ii][kk + 2] * B[kk + 2][jj] +
                                         A[ii][kk + 3] * B[kk + 3][jj] + A[ii][kk + 4] * B[kk + 4][jj] + A[ii][kk + 5] * B[kk + 5][jj] +
                                         A[ii][kk + 6] * B[kk + 6][jj] + A[ii][kk + 7] * B[kk + 7][jj] + A[ii][kk + 8] * B[kk + 8][jj] +
                                         A[ii][kk + 9] * B[kk + 9][jj] + A[ii][kk + 10] * B[kk + 10][jj] + A[ii][kk + 11] * B[kk + 11][jj] +
                                         A[ii][kk + 12] * B[kk + 12][jj] + A[ii][kk + 13] * B[kk + 13][jj] + A[ii][kk + 14] * B[kk + 14][jj] +
                                         A[ii][kk + 15] * B[kk + 15][jj];
                        }
                    }
                }
            }
        }
    }
}

void matmul_tiling_unrolling_32() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i += TILE_SIZE) {
        for (int j = 0; j < n; j += TILE_SIZE) {
            for (int k = 0; k < n; k += TILE_SIZE) {
                for (int ii = i; ii < i + TILE_SIZE; ii++) {
                    for (int jj = j; jj < j + TILE_SIZE; jj++) {
                        for (int kk = k; kk < k + TILE_SIZE; kk += 32) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj] + A[ii][kk + 1] * B[kk + 1][jj] + A[ii][kk + 2] * B[kk + 2][jj] +
                                         A[ii][kk + 3] * B[kk + 3][jj] + A[ii][kk + 4] * B[kk + 4][jj] + A[ii][kk + 5] * B[kk + 5][jj] +
                                         A[ii][kk + 6] * B[kk + 6][jj] + A[ii][kk + 7] * B[kk + 7][jj] + A[ii][kk + 8] * B[kk + 8][jj] +
                                         A[ii][kk + 9] * B[kk + 9][jj] + A[ii][kk + 10] * B[kk + 10][jj] + A[ii][kk + 11] * B[kk + 11][jj] +
                                         A[ii][kk + 12] * B[kk + 12][jj] + A[ii][kk + 13] * B[kk + 13][jj] + A[ii][kk + 14] * B[kk + 14][jj] +
                                         A[ii][kk + 15] * B[kk + 15][jj] + A[ii][kk + 16] * B[kk + 16][jj] + A[ii][kk + 17] * B[kk + 17][jj] +
                                         A[ii][kk + 18] * B[kk + 18][jj] + A[ii][kk + 19] * B[kk + 19][jj] + A[ii][kk + 20] * B[kk + 20][jj] +
                                         A[ii][kk + 21] * B[kk + 21][jj] + A[ii][kk + 22] * B[kk + 22][jj] + A[ii][kk + 23] * B[kk + 23][jj] +
                                         A[ii][kk + 24] * B[kk + 24][jj] + A[ii][kk + 25] * B[kk + 25][jj] + A[ii][kk + 26] * B[kk + 26][jj] +
                                         A[ii][kk + 27] * B[kk + 27][jj] + A[ii][kk + 28] * B[kk + 28][jj] + A[ii][kk + 29] * B[kk + 29][jj] +
                                         A[ii][kk + 30] * B[kk + 30][jj] + A[ii][kk + 31] * B[kk + 31][jj];
                        }
                    }
                }
            }
        }
    }
}
