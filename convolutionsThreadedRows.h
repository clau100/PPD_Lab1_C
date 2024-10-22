//
// Created by claud on 22.10.2024.
//

#ifndef CONVOLUTIONSTHREADEDROWS_H
#define CONVOLUTIONSTHREADEDROWS_H

int** convolve_rows_dynamic(int** mat, int N, int M, int** c, int n, int m, int p);
void convolve_rows_static(int mat[1001][1001], int N, int M, int c[6][6], int n, int m, int p, int res[1001][1001]);


#endif //CONVOLUTIONSTHREADEDROWS_H
