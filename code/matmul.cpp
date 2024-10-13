// g++ matmul.cpp -o matmul -std=c++17 -O3 -Wall && ./matmul

#include <sys/time.h>
#include <cassert>
#include <cstring>
#include <iostream>

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + 1e-6 * tv.tv_usec;
}

constexpr int n = 256;
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

void matmul() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmul_unrolled_2() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 2) {
                C[i][j] += A[i][k] * B[k][j] + A[i][k + 1] * B[k + 1][j];
            }
        }
    }
}

void matmul_unrolled_4() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 4) {
                C[i][j] += A[i][k] * B[k][j] + A[i][k + 1] * B[k + 1][j] + A[i][k + 2] * B[k + 2][j] + A[i][k + 3] * B[k + 3][j];
            }
        }
    }
}

void matmul_unrolled_8() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 8) {
                C[i][j] += A[i][k] * B[k][j] + A[i][k + 1] * B[k + 1][j] + A[i][k + 2] * B[k + 2][j] + A[i][k + 3] * B[k + 3][j] +
                           A[i][k + 4] * B[k + 4][j] + A[i][k + 5] * B[k + 5][j] + A[i][k + 6] * B[k + 6][j] + A[i][k + 7] * B[k + 7][j];
            }
        }
    }
}

void matmul_unrolled_16() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 16) {
                C[i][j] += A[i][k] * B[k][j] + A[i][k + 1] * B[k + 1][j] + A[i][k + 2] * B[k + 2][j] + A[i][k + 3] * B[k + 3][j] +
                           A[i][k + 4] * B[k + 4][j] + A[i][k + 5] * B[k + 5][j] + A[i][k + 6] * B[k + 6][j] + A[i][k + 7] * B[k + 7][j] +
                           A[i][k + 8] * B[k + 8][j] + A[i][k + 9] * B[k + 9][j] + A[i][k + 10] * B[k + 10][j] + A[i][k + 11] * B[k + 11][j] +
                           A[i][k + 12] * B[k + 12][j] + A[i][k + 13] * B[k + 13][j] + A[i][k + 14] * B[k + 14][j] + A[i][k + 15] * B[k + 15][j];
            }
        }
    }
}

void matmul_unrolled_32() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 32) {
                C[i][j] += A[i][k] * B[k][j] + A[i][k + 1] * B[k + 1][j] + A[i][k + 2] * B[k + 2][j] + A[i][k + 3] * B[k + 3][j] +
                           A[i][k + 4] * B[k + 4][j] + A[i][k + 5] * B[k + 5][j] + A[i][k + 6] * B[k + 6][j] + A[i][k + 7] * B[k + 7][j] +
                           A[i][k + 8] * B[k + 8][j] + A[i][k + 9] * B[k + 9][j] + A[i][k + 10] * B[k + 10][j] + A[i][k + 11] * B[k + 11][j] +
                           A[i][k + 12] * B[k + 12][j] + A[i][k + 13] * B[k + 13][j] + A[i][k + 14] * B[k + 14][j] + A[i][k + 15] * B[k + 15][j] +
                           A[i][k + 16] * B[k + 16][j] + A[i][k + 17] * B[k + 17][j] + A[i][k + 18] * B[k + 18][j] + A[i][k + 19] * B[k + 19][j] +
                           A[i][k + 20] * B[k + 20][j] + A[i][k + 21] * B[k + 21][j] + A[i][k + 22] * B[k + 22][j] + A[i][k + 23] * B[k + 23][j] +
                           A[i][k + 24] * B[k + 24][j] + A[i][k + 25] * B[k + 25][j] + A[i][k + 26] * B[k + 26][j] + A[i][k + 27] * B[k + 27][j] +
                           A[i][k + 28] * B[k + 28][j] + A[i][k + 29] * B[k + 29][j] + A[i][k + 30] * B[k + 30][j] + A[i][k + 31] * B[k + 31][j];
            }
        }
    }
}

void matmul_unrolled_64() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 64) {
                C[i][j] += A[i][k] * B[k][j] + A[i][k + 1] * B[k + 1][j] + A[i][k + 2] * B[k + 2][j] + A[i][k + 3] * B[k + 3][j] +
                           A[i][k + 4] * B[k + 4][j] + A[i][k + 5] * B[k + 5][j] + A[i][k + 6] * B[k + 6][j] + A[i][k + 7] * B[k + 7][j] +
                           A[i][k + 8] * B[k + 8][j] + A[i][k + 9] * B[k + 9][j] + A[i][k + 10] * B[k + 10][j] + A[i][k + 11] * B[k + 11][j] +
                           A[i][k + 12] * B[k + 12][j] + A[i][k + 13] * B[k + 13][j] + A[i][k + 14] * B[k + 14][j] + A[i][k + 15] * B[k + 15][j] +
                           A[i][k + 16] * B[k + 16][j] + A[i][k + 17] * B[k + 17][j] + A[i][k + 18] * B[k + 18][j] + A[i][k + 19] * B[k + 19][j] +
                           A[i][k + 20] * B[k + 20][j] + A[i][k + 21] * B[k + 21][j] + A[i][k + 22] * B[k + 22][j] + A[i][k + 23] * B[k + 23][j] +
                           A[i][k + 24] * B[k + 24][j] + A[i][k + 25] * B[k + 25][j] + A[i][k + 26] * B[k + 26][j] + A[i][k + 27] * B[k + 27][j] +
                           A[i][k + 28] * B[k + 28][j] + A[i][k + 29] * B[k + 29][j] + A[i][k + 30] * B[k + 30][j] + A[i][k + 31] * B[k + 31][j] +
                           A[i][k + 32] * B[k + 32][j] + A[i][k + 33] * B[k + 33][j] + A[i][k + 34] * B[k + 34][j] + A[i][k + 35] * B[k + 35][j] +
                           A[i][k + 36] * B[k + 36][j] + A[i][k + 37] * B[k + 37][j] + A[i][k + 38] * B[k + 38][j] + A[i][k + 39] * B[k + 39][j] +
                           A[i][k + 40] * B[k + 40][j] + A[i][k + 41] * B[k + 41][j] + A[i][k + 42] * B[k + 42][j] + A[i][k + 43] * B[k + 43][j] +
                           A[i][k + 44] * B[k + 44][j] + A[i][k + 45] * B[k + 45][j] + A[i][k + 46] * B[k + 46][j] + A[i][k + 47] * B[k + 47][j] +
                           A[i][k + 48] * B[k + 48][j] + A[i][k + 49] * B[k + 49][j] + A[i][k + 50] * B[k + 50][j] + A[i][k + 51] * B[k + 51][j] +
                           A[i][k + 52] * B[k + 52][j] + A[i][k + 53] * B[k + 53][j] + A[i][k + 54] * B[k + 54][j] + A[i][k + 55] * B[k + 55][j] +
                           A[i][k + 56] * B[k + 56][j] + A[i][k + 57] * B[k + 57][j] + A[i][k + 58] * B[k + 58][j] + A[i][k + 59] * B[k + 59][j] +
                           A[i][k + 60] * B[k + 60][j] + A[i][k + 61] * B[k + 61][j] + A[i][k + 62] * B[k + 62][j] + A[i][k + 63] * B[k + 63][j];
            }
        }
    }
}

void matmul_unrolled_128() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 128) {
                C[i][j] +=
                    A[i][k] * B[k][j] + A[i][k + 1] * B[k + 1][j] + A[i][k + 2] * B[k + 2][j] + A[i][k + 3] * B[k + 3][j] +
                    A[i][k + 4] * B[k + 4][j] + A[i][k + 5] * B[k + 5][j] + A[i][k + 6] * B[k + 6][j] + A[i][k + 7] * B[k + 7][j] +
                    A[i][k + 8] * B[k + 8][j] + A[i][k + 9] * B[k + 9][j] + A[i][k + 10] * B[k + 10][j] + A[i][k + 11] * B[k + 11][j] +
                    A[i][k + 12] * B[k + 12][j] + A[i][k + 13] * B[k + 13][j] + A[i][k + 14] * B[k + 14][j] + A[i][k + 15] * B[k + 15][j] +
                    A[i][k + 16] * B[k + 16][j] + A[i][k + 17] * B[k + 17][j] + A[i][k + 18] * B[k + 18][j] + A[i][k + 19] * B[k + 19][j] +
                    A[i][k + 20] * B[k + 20][j] + A[i][k + 21] * B[k + 21][j] + A[i][k + 22] * B[k + 22][j] + A[i][k + 23] * B[k + 23][j] +
                    A[i][k + 24] * B[k + 24][j] + A[i][k + 25] * B[k + 25][j] + A[i][k + 26] * B[k + 26][j] + A[i][k + 27] * B[k + 27][j] +
                    A[i][k + 28] * B[k + 28][j] + A[i][k + 29] * B[k + 29][j] + A[i][k + 30] * B[k + 30][j] + A[i][k + 31] * B[k + 31][j] +
                    A[i][k + 32] * B[k + 32][j] + A[i][k + 33] * B[k + 33][j] + A[i][k + 34] * B[k + 34][j] + A[i][k + 35] * B[k + 35][j] +
                    A[i][k + 36] * B[k + 36][j] + A[i][k + 37] * B[k + 37][j] + A[i][k + 38] * B[k + 38][j] + A[i][k + 39] * B[k + 39][j] +
                    A[i][k + 40] * B[k + 40][j] + A[i][k + 41] * B[k + 41][j] + A[i][k + 42] * B[k + 42][j] + A[i][k + 43] * B[k + 43][j] +
                    A[i][k + 44] * B[k + 44][j] + A[i][k + 45] * B[k + 45][j] + A[i][k + 46] * B[k + 46][j] + A[i][k + 47] * B[k + 47][j] +
                    A[i][k + 48] * B[k + 48][j] + A[i][k + 49] * B[k + 49][j] + A[i][k + 50] * B[k + 50][j] + A[i][k + 51] * B[k + 51][j] +
                    A[i][k + 52] * B[k + 52][j] + A[i][k + 53] * B[k + 53][j] + A[i][k + 54] * B[k + 54][j] + A[i][k + 55] * B[k + 55][j] +
                    A[i][k + 56] * B[k + 56][j] + A[i][k + 57] * B[k + 57][j] + A[i][k + 58] * B[k + 58][j] + A[i][k + 59] * B[k + 59][j] +
                    A[i][k + 60] * B[k + 60][j] + A[i][k + 61] * B[k + 61][j] + A[i][k + 62] * B[k + 62][j] + A[i][k + 63] * B[k + 63][j] +
                    A[i][k + 64] * B[k + 64][j] + A[i][k + 65] * B[k + 65][j] + A[i][k + 66] * B[k + 66][j] + A[i][k + 67] * B[k + 67][j] +
                    A[i][k + 68] * B[k + 68][j] + A[i][k + 69] * B[k + 69][j] + A[i][k + 70] * B[k + 70][j] + A[i][k + 71] * B[k + 71][j] +
                    A[i][k + 72] * B[k + 72][j] + A[i][k + 73] * B[k + 73][j] + A[i][k + 74] * B[k + 74][j] + A[i][k + 75] * B[k + 75][j] +
                    A[i][k + 76] * B[k + 76][j] + A[i][k + 77] * B[k + 77][j] + A[i][k + 78] * B[k + 78][j] + A[i][k + 79] * B[k + 79][j] +
                    A[i][k + 80] * B[k + 80][j] + A[i][k + 81] * B[k + 81][j] + A[i][k + 82] * B[k + 82][j] + A[i][k + 83] * B[k + 83][j] +
                    A[i][k + 84] * B[k + 84][j] + A[i][k + 85] * B[k + 85][j] + A[i][k + 86] * B[k + 86][j] + A[i][k + 87] * B[k + 87][j] +
                    A[i][k + 88] * B[k + 88][j] + A[i][k + 89] * B[k + 89][j] + A[i][k + 90] * B[k + 90][j] + A[i][k + 91] * B[k + 91][j] +
                    A[i][k + 92] * B[k + 92][j] + A[i][k + 93] * B[k + 93][j] + A[i][k + 94] * B[k + 94][j] + A[i][k + 95] * B[k + 95][j] +
                    A[i][k + 96] * B[k + 96][j] + A[i][k + 97] * B[k + 97][j] + A[i][k + 98] * B[k + 98][j] + A[i][k + 99] * B[k + 99][j] +
                    A[i][k + 100] * B[k + 100][j] + A[i][k + 101] * B[k + 101][j] + A[i][k + 102] * B[k + 102][j] + A[i][k + 103] * B[k + 103][j] +
                    A[i][k + 104] * B[k + 104][j] + A[i][k + 105] * B[k + 105][j] + A[i][k + 106] * B[k + 106][j] + A[i][k + 107] * B[k + 107][j] +
                    A[i][k + 108] * B[k + 108][j] + A[i][k + 109] * B[k + 109][j] + A[i][k + 110] * B[k + 110][j] + A[i][k + 111] * B[k + 111][j] +
                    A[i][k + 112] * B[k + 112][j] + A[i][k + 113] * B[k + 113][j] + A[i][k + 114] * B[k + 114][j] + A[i][k + 115] * B[k + 115][j] +
                    A[i][k + 116] * B[k + 116][j] + A[i][k + 117] * B[k + 117][j] + A[i][k + 118] * B[k + 118][j] + A[i][k + 119] * B[k + 119][j] +
                    A[i][k + 120] * B[k + 120][j] + A[i][k + 121] * B[k + 121][j] + A[i][k + 122] * B[k + 122][j] + A[i][k + 123] * B[k + 123][j] +
                    A[i][k + 124] * B[k + 124][j] + A[i][k + 125] * B[k + 125][j] + A[i][k + 126] * B[k + 126][j] + A[i][k + 127] * B[k + 127][j];
            }
        }
    }
}

void matmul_ikj() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmul_ikj_unrolled_2() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            int Aik = A[i][k];  // 提前加载 A[i][k]
            int j;
            for (j = 0; j <= n - 2; j += 2) {
                C[i][j] += Aik * B[k][j];
                C[i][j + 1] += Aik * B[k][j + 1];
            }
            for (; j < n; j++) {
                C[i][j] += Aik * B[k][j];
            }
        }
    }
}

void matmul_ikj_unrolled_4() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            int Aik = A[i][k];  // 提前加载 A[i][k]
            int j;
            for (j = 0; j <= n - 4; j += 4) {
                C[i][j] += Aik * B[k][j];
                C[i][j + 1] += Aik * B[k][j + 1];
                C[i][j + 2] += Aik * B[k][j + 2];
                C[i][j + 3] += Aik * B[k][j + 3];
            }
            for (; j < n; j++) {
                C[i][j] += Aik * B[k][j];
            }
        }
    }
}

void matmul_ikj_unrolled_8() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            int Aik = A[i][k];  // 提前加载 A[i][k]
            int j;
            for (j = 0; j <= n - 8; j += 8) {
                C[i][j] += Aik * B[k][j];
                C[i][j + 1] += Aik * B[k][j + 1];
                C[i][j + 2] += Aik * B[k][j + 2];
                C[i][j + 3] += Aik * B[k][j + 3];
                C[i][j + 4] += Aik * B[k][j + 4];
                C[i][j + 5] += Aik * B[k][j + 5];
                C[i][j + 6] += Aik * B[k][j + 6];
                C[i][j + 7] += Aik * B[k][j + 7];
            }
            for (; j < n; j++) {
                C[i][j] += Aik * B[k][j];
            }
        }
    }
}

void matmul_AT() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AT[i][j] = A[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += AT[k][i] * B[k][j];
            }
        }
    }
}

void matmul_AT_unrolled_2() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AT[i][j] = A[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 2) {
                C[i][j] += AT[k][i] * B[k][j] + AT[k + 1][i] * B[k + 1][j];
            }
        }
    }
}

void matmul_AT_unrolled_4() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AT[i][j] = A[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 4) {
                C[i][j] += AT[k][i] * B[k][j] + AT[k + 1][i] * B[k + 1][j] + AT[k + 2][i] * B[k + 2][j] + AT[k + 3][i] * B[k + 3][j];
            }
        }
    }
}

void matmul_AT_unrolled_8() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AT[i][j] = A[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 8) {
                C[i][j] += AT[k][i] * B[k][j] + AT[k + 1][i] * B[k + 1][j] + AT[k + 2][i] * B[k + 2][j] + AT[k + 3][i] * B[k + 3][j] +
                           AT[k + 4][i] * B[k + 4][j] + AT[k + 5][i] * B[k + 5][j] + AT[k + 6][i] * B[k + 6][j] + AT[k + 7][i] * B[k + 7][j];
            }
        }
    }
}

void matmul_BT() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            BT[i][j] = B[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * BT[j][k];
            }
        }
    }
}

void matmul_BT_unrolled_2() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            BT[i][j] = B[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 2) {
                C[i][j] += A[i][k] * BT[j][k] + A[i][k + 1] * BT[j][k + 1];
            }
        }
    }
}

void matmul_BT_unrolled_4() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            BT[i][j] = B[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 4) {
                C[i][j] += A[i][k] * BT[j][k] + A[i][k + 1] * BT[j][k + 1] + A[i][k + 2] * BT[j][k + 2] + A[i][k + 3] * BT[j][k + 3];
            }
        }
    }
}

void matmul_BT_unrolled_8() {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            BT[i][j] = B[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 8) {
                C[i][j] += A[i][k] * BT[j][k] + A[i][k + 1] * BT[j][k + 1] + A[i][k + 2] * BT[j][k + 2] + A[i][k + 3] * BT[j][k + 3] +
                           A[i][k + 4] * BT[j][k + 4] + A[i][k + 5] * BT[j][k + 5] + A[i][k + 6] * BT[j][k + 6] + A[i][k + 7] * BT[j][k + 7];
            }
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
    // write into ../report/q1.txt
    FILE* fp = fopen("../report/q1.txt", "a");
    fprintf(fp, "%d %s %f\n", n, func_name, avg_time / 32);
    fclose(fp);
}

int main() {
    run_test(matmul, "matmul");
    // run_test(matmul_AT, "matmul_AT");
    // run_test(matmul_BT, "matmul_BT");
    // run_test(matmul_ikj, "matmul_ikj");
    run_test(matmul_unrolled_2, "matmul_unrolled_2");
    run_test(matmul_unrolled_4, "matmul_unrolled_4");
    run_test(matmul_unrolled_8, "matmul_unrolled_8");
    // run_test(matmul_unrolled_16, "matmul_unrolled_16");
    // run_test(matmul_unrolled_32, "matmul_unrolled_32");
    // run_test(matmul_unrolled_64, "matmul_unrolled_64");
    // run_test(matmul_unrolled_128, "matmul_unrolled_128");
    // run_test(matmul_ikj_unrolled_2, "matmul_ikj_unrolled_2");
    // run_test(matmul_ikj_unrolled_4, "matmul_ikj_unrolled_4");
    // run_test(matmul_ikj_unrolled_8, "matmul_ikj_unrolled_8");
    // run_test(matmul_AT_unrolled_2, "matmul_AT_unrolled_2");
    // run_test(matmul_AT_unrolled_4, "matmul_AT_unrolled_4");
    // run_test(matmul_AT_unrolled_8, "matmul_AT_unrolled_8");
    // run_test(matmul_BT_unrolled_2, "matmul_BT_unrolled_2");
    // run_test(matmul_BT_unrolled_4, "matmul_BT_unrolled_4");
    // run_test(matmul_BT_unrolled_8, "matmul_BT_unrolled_8");
    return 0;
}

// int main() {
//   float avg_time = 0.0f;

//   init();
//   for (int K = 0; K < 32; K++) {
//     auto t = get_time();
//     matmul();
//     // matmul_AT();
//     // matmul_BT();
//     // matmul_ikj();
//     test();
//     printf("%f\n", get_time() - t);
//     avg_time += get_time() - t;
//   }
//   printf("matmul Avg Time for Calculation: %f\n", avg_time / 32);
//   return 0;
// }
