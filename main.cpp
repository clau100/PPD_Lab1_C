#include <cassert>
#include <iostream>
#include <fstream>
#include <chrono>
#include "convolutionsThreadedRows.h"
#include "convolutionsThreadedColumns.h"
#include "utils.h"

int N, M;
int n, m;
int **mat = nullptr, **c = nullptr, **res = nullptr;
int mat1[1001][1001], c1[6][6], res1[1001][1001];
int p;
std::string filename_input = "input_mat.txt", filename_input_c = "input_c.txt";
std::string filename_output_iterative = "output.txt", filename_output = "output1.txt";

int** convolve_iterative_dynamic(int** mat, int N, int M, int** c, int n, int m) {
    int** result = new int*[N];
    for (int i = 0; i < N; ++i) {
        result[i] = new int[M];
    }

    int half_n = n / 2;
    int half_m = m / 2;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int sum = 0;
            for (int ki = -half_n; ki <= half_n; ++ki) {
                for (int kj = -half_m; kj <= half_m; ++kj) {
                    sum += getValueDynamic(mat, N, M, i + ki, j + kj) * c[ki + half_n][kj + half_m];
                }
            }
            result[i][j] = sum;
        }
    }

    return result;
}

void convolve_iterative_static(int mat[1001][1001], int N, int M, int c1[6][6], int n, int m) {
    int half_n = n / 2;
    int half_m = m / 2;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int sum = 0;
            for (int ki = -half_n; ki <= half_n; ++ki) {
                for (int kj = -half_m; kj <= half_m; ++kj) {
                    sum += getValueStatic(mat, N, M, i + ki, j + kj) * c1[ki + half_n][kj + half_m];
                }
            }
            res1[i][j] = sum;
        }
    }
}

int main() {
    std::cin >> p;
    N = M = 10;
    n = m = 3;

    // DYNAMIC
    // mat = generateRandomArrayDynamic(N, M);
    // c = generateRandomArrayDynamic(n, m);
    // printDynamicArrayToFile(mat, N, M, filename_input);
    // printDynamicArrayToFile(c, n, m, filename_input_c);
    //
    // auto start = std::chrono::high_resolution_clock::now();
    // res = convolve_iterative_dynamic(mat, N, M, c, n, m);
    // auto end = std::chrono::high_resolution_clock::now();
    //
    // printDynamicArrayToFile(res, N, M, filename_output_iterative);
    //
    // res = convolve_rows_dynamic(mat, N, M, c, n, m, p);
    // printDynamicArrayToFile(res, N, M, filename_output);
    //
    // if(!areFilesEqual(filename_output_iterative, filename_output)) {
    //     assert("Files are not equal");
    //     return 1;
    // }

    // STATIC
    generateRandomArrayStatic(mat1, N, M);
    generateRandomKernelStaic(c1, n, m);
    printStaticArrayToFile(mat1, N, M, filename_input);
    printStaticKernelToFile(c1, n, m, filename_input_c);

    auto start = std::chrono::high_resolution_clock::now();
    convolve_iterative_static(mat1, N, M, c1, n, m);
    auto end = std::chrono::high_resolution_clock::now();

    printStaticArrayToFile(res1, N, M, filename_output_iterative);

    convolve_rows_static(mat1, N, M, c1, n, m, p, res1);
    printStaticArrayToFile(res1, N, M, filename_output);

    if(!areFilesEqual(filename_output_iterative, filename_output)) {
        assert("Files are not equal");
        return 1;
    }

    std::chrono::duration<double> duration = end - start;
    std::cout <<  duration.count() / 1E6;

    // for (int i = 0; i < N; ++i) {
    //     delete[] mat[i];
    //     delete[] res[i];
    // }
    // delete[] mat;
    // delete[] res;
    //
    // for (int i = 0; i < n; ++i) {
    //     delete[] c[i];
    // }
    // delete[] c;

    return 0;
}