#ifndef OPTIMIZE_H
#define OPTIMIZE_H

// loop unrolling
void matmul_unrolling_2();
void matmul_unrolling_4();
void matmul_unrolling_8();
void matmul_unrolling_16();
void matmul_unrolling_32();
void matmul_unrolling_64();
void matmul_unrolling_128();

// tiling + (loop unrolling)
void matmul_tiling();
void matmul_tiling_unrolling_4();
void matmul_tiling_unrolling_8();
void matmul_tiling_unrolling_16();
void matmul_tiling_unrolling_32();

#endif
