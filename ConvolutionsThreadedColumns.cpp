//
// Created by claud on 22.10.2024.
//
#include "ConvolutionsThreadedColumns.h"
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include "utils.h"
std::mutex mtx_cols;

void convolveChunkColsDynamic(int** mat, int N, int M, int** c, int n, int m, int startCol, int endCol, int** result) {
    int half_n = n / 2;
    int half_m = m / 2;

    for (int j = startCol; j < endCol; ++j) {
        for (int i = 0; i < N; ++i) {
            int sum = 0;
            for (int ki = -half_n; ki <= half_n; ++ki) {
                for (int kj = -half_m; kj <= half_m; ++kj) {
                    sum += getValueDynamic(mat, N, M, i + ki, j + kj) * c[ki + half_n][kj + half_m];
                }
            }
            std::lock_guard<std::mutex> lock(mtx_cols);
            result[i][j] = sum;
        }
    }
}

int** convolve_cols_dynamic(int** mat, int N, int M, int** c, int n, int m, int p) {
    int** result = new int*[N];
    for (int i = 0; i < N; ++i) {
        result[i] = new int[M];
    }

    std::vector<std::thread> threads;
    int colsPerThread = M / p;
    int remainingCols = M % p;
    int startCol = 0;

    for (int i = 0; i < p; ++i) {
        int endCol = startCol + colsPerThread + (i < remainingCols ? 1 : 0);
        threads.emplace_back(convolveChunkColsDynamic, mat, N, M, c, n, m, startCol, endCol, result);
        startCol = endCol;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

void convolveChunkColsStatic(int mat[1001][1001], int N, int M, int c[6][6], int n, int m, int startCol, int endCol, int res[1001][1001]) {
    int half_n = n / 2;
    int half_m = m / 2;

    for (int j = startCol; j < endCol; ++j) {
        for (int i = 0; i < N; ++i) {
            int sum = 0;
            for (int ki = -half_n; ki <= half_n; ++ki) {
                for (int kj = -half_m; kj <= half_m; ++kj) {
                    sum += getValueStatic(mat, N, M, i + ki, j + kj) * c[ki + half_n][kj + half_m];
                }
            }
            std::lock_guard<std::mutex> lock(mtx_cols);
            res[i][j] = sum;
        }
    }
}

void convolve_cols_static(int mat[1001][1001], int N, int M, int c[6][6], int n, int m, int p, int res[1001][1001]) {
    std::vector<std::thread> threads;
    int colsPerThread = M / p;
    int remainingCols = M % p;
    int startCol = 0;

    for (int i = 0; i < p; ++i) {
        int endCol = startCol + colsPerThread + (i < remainingCols ? 1 : 0);
        threads.emplace_back(convolveChunkColsStatic, mat, N, M, c, n, m, startCol, endCol, res);
        startCol = endCol;
    }

    for (auto& thread : threads) {
        thread.join();
    }
}