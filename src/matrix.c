#include "global.h"


int SparseMatrix(int** M, int** S, int* D){
    int r,c = D[0],D[1]; //initializes values
    int max;
    //checks which is the greater dimension
    if (r > c) {
        max = r;
    }
    else {
        max = c;
    }
    int res = 0;

    // Check if the matrix sparse or 
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (*(*(M + i) + j) != 0) { // if we found non-zero element we increase count
                res++;
                if (res > max) {//if there are more non-zero elements than highest dimension, then not sparse
                    return -1;
                }
            }
        }
    }

    // Initialize the sparse matrix S using pointer dereferencing
    *S = (int*)malloc(3 * max * sizeof(int));
    int* sr = *S; //rows of s
    int* sc = *S + max; //columns of s
    int* sz = *S + 2 * max;

    // Initialize S with zeros
    for (int i = 0; i < max; i++) {
        sr[i] = 0;
        sc[i] = 0;
        sz[i] = 0;
    }

    int col_index = 0;
    // Fill the sparse matrix S with non-zero elements using pointer dereferencing
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (*(*(M + i) + j) != 0) {
                sr[col_index] = i;
                sc[col_index] = j;
                sz[col_index] = *(*(M + i) + j);
                col_index++;
            }
        }
    }

    return res;
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