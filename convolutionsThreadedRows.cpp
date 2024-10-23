//
// Created by claud on 22.10.2024.
//
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include "convolutionsThreadedRows.h"
#include "utils.h"
std::mutex mtx_rows;


void convolveChunkRowsDynamic(int** mat, int N, int M, int** c, int n, int m, int startRow, int endRow, int** result) {
    int half_n = n / 2;
    int half_m = m / 2;

    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < M; ++j) {
            int sum = 0;
            for (int ki = -half_n; ki <= half_n; ++ki) {
                for (int kj = -half_m; kj <= half_m; ++kj) {
                    sum += getValueDynamic(mat, N, M, i + ki, j + kj) * c[ki + half_n][kj + half_m];
                }
            }
            std::lock_guard<std::mutex> lock(mtx_rows);
            result[i][j] = sum;
        }
    }
}

int** convolve_rows_dynamic(int** mat, int N, int M, int** c, int n, int m, int p) {
    int** result = new int*[N];
    for (int i = 0; i < N; ++i) {
        result[i] = new int[M];
    }

    std::vector<std::thread> threads;
    int rowsPerThread = N / p;
    int remainingRows = N % p;
    int startRow = 0;

    for (int i = 0; i < p; ++i) {
        int endRow = startRow + rowsPerThread + (i < remainingRows ? 1 : 0);
        threads.emplace_back(convolveChunkRowsDynamic, mat, N, M, c, n, m, startRow, endRow, result);
        startRow = endRow;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

void convolveChunkRowsStatic(int mat[1001][1001], int N, int M, int c[6][6], int n, int m, int startRow, int endRow, int res[1001][1001]) {
    int half_n = n / 2;
    int half_m = m / 2;

    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < M; ++j) {
            int sum = 0;
            for (int ki = -half_n; ki <= half_n; ++ki) {
                for (int kj = -half_m; kj <= half_m; ++kj) {
                    sum += getValueStatic(mat, N, M, i + ki, j + kj) * c[ki + half_n][kj + half_m];
                }
            }
            std::lock_guard<std::mutex> lock(mtx_rows);
            res[i][j] = sum;
        }
    }
}

void convolve_rows_static(int mat[1001][1001], int N, int M, int c[6][6], int n, int m, int p, int res[1001][1001]) {
    std::vector<std::thread> threads;
    int rowsPerThread = N / p;
    int remainingRows = N % p;
    int startRow = 0;

    for (int i = 0; i < p; ++i) {
        int endRow = startRow + rowsPerThread + (i < remainingRows ? 1 : 0);
        threads.emplace_back(convolveChunkRowsStatic, mat, N, M, c, n, m, startRow, endRow, res);
        startRow = endRow;
    }

    for (auto& thread : threads) {
        thread.join();
    }
}