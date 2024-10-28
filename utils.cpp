//
// Created by claud on 22.10.2024.
//
#include "utils.h"

#include <fstream>
#include <iostream>
#include <random>

void printDynamicArrayToFile(int** array, int N, int M, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            outFile << array[i][j] << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
}

void printStaticKernelToFile(int c[6][6], int n, int m, const std::string &filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            outFile << c[i][j] << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
}

void printStaticArrayToFile(int array[1001][1001], int N, int M, const std::string &filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            outFile << array[i][j] << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
}

int** generateRandomArrayDynamic(int N, int M) {
    int** array = new int*[N];
    for (int i = 0; i < N; ++i) {
        array[i] = new int[M];
    }

    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(1, 9); // Define the range

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            array[i][j] = distr(gen); // Generate numbers between 1 and 10
        }
    }

    return array;
}

bool areFilesEqual(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1, std::ios::binary | std::ios::ate);
    std::ifstream f2(file2, std::ios::binary | std::ios::ate);

    if (!f1.is_open() || !f2.is_open()) {
        std::cerr << "Error opening one of the files." << std::endl;
        return false;
    }

    // Compare file sizes first
    if (f1.tellg() != f2.tellg()) {
        return false; // Different file sizes mean files are not equal
    }

    // Move back to the beginning of both files
    f1.seekg(0, std::ios::beg);
    f2.seekg(0, std::ios::beg);

    // Compare byte by byte
    char c1, c2;
    while (f1.get(c1) && f2.get(c2)) {
        if (c1 != c2) {
            return false;
        }
    }

    // If we reached this point, the files are equal
    return true;
}

int getValueDynamic(int** mat, int N, int M, int i, int j) {
    if (i < 0) i = 0;
    if (i >= N) i = N - 1;
    if (j < 0) j = 0;
    if (j >= M) j = M - 1;
    return mat[i][j];
}

int getValueStatic(int mat[1001][1001], int N, int M, int i, int j) {
    if (i < 0) i = 0;
    if (i >= N) i = N - 1;
    if (j < 0) j = 0;
    if (j >= M) j = M - 1;
    return mat[i][j];
}


void generateRandomArrayStatic(int mat[1001][1001], int N, int M) {
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(1, 9); // Define the range

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            mat[i][j] = distr(gen); // Generate numbers between 1 and 10
        }
    }
}

void generateRandomKernelStaic(int c[6][6], int n, int m) {
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(1, 9); // Define the range

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            c[i][j] = distr(gen); // Generate numbers between 1 and 10
        }
    }
}