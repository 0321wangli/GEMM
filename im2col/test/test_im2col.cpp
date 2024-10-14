#include <sys/time.h>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

constexpr int height = 5;
constexpr int width = 5;
constexpr int in_channels = 3;
constexpr int out_channels = 1;
constexpr int kernel_size = 3;
constexpr int stride = 1;
constexpr int padding = 0;
constexpr int output_height = (height - kernel_size + 2 * padding) / stride + 1;
constexpr int output_width = (width - kernel_size + 2 * padding) / stride + 1;

int input[in_channels][height][width];                                                 // input image
int input_col[output_height * output_width][in_channels * kernel_size * kernel_size];  // im2col input

int kernel[out_channels][in_channels][kernel_size][kernel_size];        // kernel
int kernel_col[in_channels * kernel_size * kernel_size][out_channels];  // im2col kernel

int output[out_channels][output_height][output_width];       // output
int output_col[output_height * output_width][out_channels];  // im2col output

void init() {
    for (int c = 0; c < in_channels; ++c) {
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                input[c][h][w] = rand() % 10 + 1;
            }
        }
    }

    for (int c = 0; c < out_channels; ++c) {
        for (int ic = 0; ic < in_channels; ++ic) {
            for (int kh = 0; kh < kernel_size; ++kh) {
                for (int kw = 0; kw < kernel_size; ++kw) {
                    kernel[c][ic][kh][kw] = rand() % 10 + 1;
                }
            }
        }
    }
    memset(output, 0, sizeof(output));
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

void print_mat() {
    printf("input\n");
    for (int c = 0; c < in_channels; ++c) {
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                cout << input[c][h][w] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    printf("kernel\n");
    for (int c = 0; c < out_channels; ++c) {
        for (int ic = 0; ic < in_channels; ++ic) {
            for (int kh = 0; kh < kernel_size; ++kh) {
                for (int kw = 0; kw < kernel_size; ++kw) {
                    cout << kernel[c][ic][kh][kw] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << endl;
    }
}

void print_im2col() {
    printf("input_col\n");
    for (int i = 0; i < output_height * output_width; ++i) {
        for (int j = 0; j < in_channels * kernel_size * kernel_size; ++j) {
            cout << input_col[i][j] << " ";
        }
        cout << endl;
    }

    printf("kernel_col\n");
    for (int i = 0; i < in_channels * kernel_size * kernel_size; ++i) {
        for (int j = 0; j < out_channels; ++j) {
            cout << kernel_col[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    init();
    print_mat();
    im2col_input();
    im2col_kernel();
    print_im2col();
    return 0;
}
