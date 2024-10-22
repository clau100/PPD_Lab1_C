//
// Created by claud on 22.10.2024.
//

#ifndef UTILS_H
#define UTILS_H
#include <string>

void printStaticArrayToFile(int array[1001][1001], int N, int M, const std::string& filename);
void printStaticKernelToFile(int c[6][6], int n, int m, const std::string& filename);
void printDynamicArrayToFile(int** array, int N, int M, const std::string& filename);
int** generateRandomArrayDynamic(int N, int M);
void generateRandomArrayStatic(int mat[1001][1001], int N, int M);
void generateRandomKernelStaic(int c[6][6], int n, int m);
bool areFilesEqual(const std::string& filename1, const std::string& filename2);
int getValueDynamic(int** mat, int N, int M, int i, int j);
int getValueStatic(int mat[1001][1001], int N, int M, int i, int j);
#endif //UTILS_H
