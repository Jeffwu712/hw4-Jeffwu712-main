#include "global.h"


int SparseMatrix(int** M, int** S, int* D){
    int r = D[0]; //initializes values
    int c = D[1];
    int max;
    
    if (r > c) {//checks which is the greater dimension
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
    
    int* sr = *S; //rows of s
    int* sc = max + *S; //columns of s
    int* sv = (2 * max) + *S;

    int column = 0;
        // Fill the sparse matrix S with non-zero elements using pointer dereferencing
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (*(*(M + i) + j) != 0) {
                *(sr + column) = i;
                *(sc + column) = *(*(M + i) + j);
                *(sv + column) = j;
                column++;
            }
        }
}
    return res; //returns res which contains the amount of non zero values
}
int Addition(int** M, int** N, int** A, int* D) {
    int rows1 = D[0];
    int columns1 = D[1];
    int rows2 = D[2];
    int columns2 = D[3];
    int rows3 = D[4];
    int columns3 = D[5];
    if (rows1 == rows2 && columns1 == columns2) {//if compatiable 
        if (rows3 == rows1 && columns3 == columns1) {//A also comptabile 
            for (int i = 0; i < rows1; i++) {
                for (int j = 0; j < columns1; j++) {//striaghtforwads addition
                    *((*(A + i)) + j) =  *((*(N + i)) + j) + *((*(M + i)) + j); 
                }
            }
            return 1; 
        } else if (rows3 >= rows1 && columns3 >= columns1) {//// A is oversized
            for (int i = 0; i < rows1; i++) {//addition on all elements
                for (int j = 0; j < columns1; j++) {
                    *((*(A + i)) + j) = *((*(N + i)) + j) + *((*(M + i)) + j);
                }
            }
            return 2;
        } else {//if A not compatible 
            return -3;
        }
    } else {//M and N not compatible
        for (int i = 0; i < rows3; i++) {//additon of overlap
            for (int j = 0; j < columns3; j++) {
                if (columns1&& j < i < rows1 ) {
                    *((*(A + i)) + j) = *((*(M + i)) + j);
                    if ( j < columns2&& i < rows2) {
                        *((*(A + i)) + j) += *((*(N + i)) + j);
                    }
                } else if (i < rows2 && j < columns2) {
                    *((*(A + i)) + j) = *((*(N + i)) + j);
                }
            }
        }
        if (rows3 >= rows1 && columns3 >= columns1 && rows3 >= rows2 && columns3 >= columns2) {//A overlap
            for (int i = 0; i < rows1; i++) {
                for (int j = 0; j < columns1; j++) {
                    *((*(A + i)) + j) = *((*(N + i)) + j) + *((*(M + i)) + j);
                }
            }
            return -1;
        } else {
            return -2;
        }
    }
}
int Multiplication(int** M, int** N, int** A, int* D) {
    int rows1 = D[0];
    int rows2 = D[2];
    int rows3 = D[4];
    int column1 = D[1];
    int column2 = D[3];
    int column3 = D[5];
    for (int i = 0; i < rows3; i++) {
        for (int j = 0; j < column3; j++) {
            int ans = 0;
            if (i < rows1 && j < column2) {
                for (int k = 0; k < column1; k++) {
                    ans += *((*(M + i)) + k) * *((*(N + k)) + j);
                }
            }
            *((*(A + i)) + j) = ans;
        }
    }
    if (column1 != rows2) {
        if ( column3 >= column2&&rows3 >= rows1 ) {// If A is oversized
            for (int i = 0; i < rows1; i++) { //calc ans
                for (int j = 0; j < column2; j++) {
                    int ans = 0;
                    for (int k = 0; k < column1; k++) {
                        ans += *((*(M + i)) + k) * *((*(N + k)) + j);
                    }
                    *((*(A + i)) + j) = ans;
                }
            }
            return -1;
        } else { // IF A not compatible, and holds overlapping dimensions
            return -2;
        }
    } else {//M and N are compatible
        if (rows3 == rows1 && column3 == column2) {
            return 1;
        } else if (rows3 >= rows1 && column3 >= column2) {//// A is oversized
            for (int i = 0; i < rows1; i++) {//multiplication
                for (int j = 0; j < column2; j++) {
                    int ans = 0;
                    for (int k = 0; k < column1; k++) {
                        ans += *((*(M + i)) + k) * *((*(N + k)) + j);
                    }
                    *((*(A + i)) + j) = ans;
                }
            }
            return 2; 
        } else {//A not compatiable
            return -3;
        }
    }
}
int Transpose(int** A, int** AT, int* D) {
    int rows1 = D[0];
    int column1 = D[1];
    int rows2 = D[2];
    int column2 = D[3];

    if (rows1 == column2 && column1 == rows2) {//A AT compatible
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < column1; j++) {
                *((*(AT + j)) + i) = *((*(A + i)) + j);
            }
        }
        return 1; 
    } else if (rows2 >= column1 && column2 >= rows1) {////compatible and oversized
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < column1; j++) {
                *((*(AT + j)) + i) = *((*(A + i)) + j);
            }
        }
        return 2; 
    } else {// Dimensions not compatible
        
        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < column2; j++) {
                if (i < rows1 && j < column1) {
                    *((*(AT + i)) + j) = *((*(A + i)) + j);
                }
            }
        }
        if (rows2 >= column1 && column2 >= rows1) {
            return -1; 
        } else {//not compatible and no space
            return -1; // Keep this as -1
        }
    }
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