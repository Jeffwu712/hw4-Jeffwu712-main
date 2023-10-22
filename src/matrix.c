#include "global.h"


int SparseMatrix(int** M, int** S, int* D){
        int rows = D[0];
    int cols = D[1];
    int max_dimension = (rows > cols) ? rows : cols;
    int non_zero_count = 0;

    // Check if the matrix qualifies as a sparse matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (*(*(M + i) + j) != 0) {
                non_zero_count++;
                if (non_zero_count > max_dimension) {
                    // Matrix is not sparse
                    return -1;
                }
            }
        }
    }

    // Initialize the sparse matrix S using pointer dereferencing
    *S = (int*)malloc(3 * max_dimension * sizeof(int));
    int* sRow = *S;
    int* sColumn = *S + max_dimension;
    int* sValue = *S + 2 * max_dimension;

    // Initialize S with zeros
    for (int i = 0; i < max_dimension; i++) {
        sRow[i] = 0;
        sColumn[i] = 0;
        sValue[i] = 0;
    }

    int col_index = 0;
    // Fill the sparse matrix S with non-zero elements using pointer dereferencing
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (*(*(M + i) + j) != 0) {
                sRow[col_index] = i;
                sColumn[col_index] = j;
                sValue[col_index] = *(*(M + i) + j);
                col_index++;
            }
        }
    }

    return non_zero_count;
}
int Addition(int** M, int** N, int** A, int* D){
   // TO BE IMPLEMENTED
    abort();
}
int Multiplication(int** M, int** N, int** A, int* D){
   // TO BE IMPLEMENTED
    abort();
}
int Transpose(int** A, int** AT, int* D){
    // TO BE IMPLEMENTED
    abort();
}

// Helper functions for Testing
int** initializeMatrix(int n, int m, int* values){
    int** ret = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        ret[i] = (int*)malloc(m*sizeof(int));
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            ret[i][j] = values[i*m+j];
        }
    }
    return ret;
}

void freeMatrix(int n, int** M){
    for(int i=0; i<n; i++){
        free(M[i]);
    }
    free(M);
}