#include <iostream>
#include <vector>
#include <cassert>
#include <sys/time.h>
#include <cstring>

using namespace std;

constexpr int height = 56;
constexpr int width = 56;
constexpr int in_channels = 3;
constexpr int out_channels = 64;

// constexpr int height = 5;
// constexpr int width = 5;
// constexpr int in_channels = 3;
// constexpr int out_channels = 1;

constexpr int kernel_size = 3;
constexpr int stride = 1;
constexpr int padding = 0;
constexpr int output_height = (height - kernel_size + 2 * padding) / stride + 1;
constexpr int output_width = (width - kernel_size + 2 * padding) / stride + 1;
constexpr int common_size = in_channels * kernel_size * kernel_size;

int input[in_channels][height][width]; // input image
int input_col[output_height * output_width][common_size]; // im2col input

int kernel[out_channels][in_channels][kernel_size][kernel_size]; // kernel
int kernel_col[common_size][out_channels]; // im2col kernel

int output[out_channels][output_height][output_width]; // output
int output_col[output_height * output_width][out_channels]; // im2col output

double get_time() {
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  return tv.tv_sec + 1e-6 * tv.tv_usec;
}

void init() {
    for (int c = 0; c < in_channels; ++c) {
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                input[c][h][w] = rand();
            }
        }
    }

    for (int c = 0; c < out_channels; ++c) {
        for (int ic = 0; ic < in_channels; ++ic) {
            for (int kh = 0; kh < kernel_size; ++kh) {
                for (int kw = 0; kw < kernel_size; ++kw) {
                    kernel[c][ic][kh][kw] = rand();
                }
            }
        }
    }

    for (int c = 0; c < out_channels; ++c) {
        for (int h = 0; h < output_height; ++h) {
            for (int w = 0; w < output_width; ++w) {
                output[c][h][w] = 0;
            }
        }
    }
}

void im2col_input() {
    for (int c = 0; c < in_channels; ++c) {
        for (int kh = 0; kh < kernel_size; ++kh) {
            for (int kw = 0; kw < kernel_size; ++kw) {
                for (int h = 0; h < output_height; ++h) {
                    for (int w = 0; w < output_width; ++w) {
                        int col_index = h * output_width + w;
                        input_col[col_index][c * kernel_size * kernel_size + kh * kernel_size + kw] = input[c][h + kh][w + kw];
                    }
                }
            }
        }
    }
}

void im2col_kernel() {
    for (int c = 0; c < in_channels; ++c) {
        for (int kh = 0; kh < kernel_size; ++kh) {
            for (int kw = 0; kw < kernel_size; ++kw) {
                for (int c_out = 0; c_out < out_channels; ++c_out) {
                    kernel_col[c * kernel_size * kernel_size + kh * kernel_size + kw][c_out] = kernel[c_out][c][kh][kw];
                }
            }
        }
    }
}

void matmul() {
    memset(output_col, 0, sizeof(output_col));
    for (int h = 0; h < output_height; ++h) {
        for (int w = 0; w < output_width; ++w) {
            for (int c_out = 0; c_out < out_channels; ++c_out) {
                for (int c = 0; c < common_size; ++c) {
                    output_col[h * output_width + w][c_out] += input_col[h * output_width + w][c] * kernel_col[c][c_out];
                }
            }
        }
    }
}

void direct_conv() {
    memset(output, 0, sizeof(output));
    for (int c_out = 0; c_out < out_channels; ++c_out) {
        for (int h = 0; h < output_height; ++h) {
            for (int w = 0; w < output_width; ++w) {
                for (int c = 0; c < in_channels; ++c) {
                    for (int kh = 0; kh < kernel_size; ++kh) {
                        for (int kw = 0; kw < kernel_size; ++kw) {
                            output[c_out][h][w] += input[c][h + kh][w + kw] * kernel[c_out][c][kh][kw];
                        }
                    }
                }
            }
        }
    }
}

void test() {
    for (int c = 0; c < out_channels; ++c) {
        for (int h = 0; h < output_height; ++h) {
            for (int w = 0; w < output_width; ++w) {
                assert(output[c][h][w] == output_col[h * output_width + w][c]);
            }
        }
    }
}

int main() {
    init();
    // print input
    // for (int c = 0; c < in_channels; ++c) {
    //     for (int h = 0; h < height; ++h) {
    //         for (int w = 0; w < width; ++w) {
    //             cout << input[c][h][w] << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    // print kernel
    // printf("kernel\n");
    // for (int c = 0; c < out_channels; ++c) {
    //     for (int ic = 0; ic < in_channels; ++ic) {
    //         for (int kh = 0; kh < kernel_size; ++kh) {
    //             for (int kw = 0; kw < kernel_size; ++kw) {
    //                 cout << kernel[c][ic][kh][kw] << " ";
    //             }
    //             cout << endl;
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    im2col_input();
    im2col_kernel();

    auto t = get_time();
    matmul();
    printf("im2col + matmul: %f\n", get_time() - t);
    // print output_col
    // for (int c = 0; c < out_channels; ++c) {
    //     for (int h = 0; h < output_height; ++h) {
    //         for (int w = 0; w < output_width; ++w) {
    //             cout << output_col[h * output_width + w][c] << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }
    t = get_time();
    direct_conv();
    printf("direct conv: %f\n", get_time() - t);

    // print output
    // for (int c = 0; c < out_channels; ++c) {
    //     for (int h = 0; h < output_height; ++h) {
    //         for (int w = 0; w < output_width; ++w) {
    //             cout << output[c][h][w] << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }
    test();
    return 0;
}
