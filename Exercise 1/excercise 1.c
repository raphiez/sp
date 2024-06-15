#include <stdio.h>
#include <stdlib.h>

void dump(double *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

void transpose(double *matrix, double *result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j * rows + i] = matrix[i * cols + j];
        }
    }
}

void add(double *matrix1, double *matrix2, double *result, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        result[i] = matrix1[i] + matrix2[i];
    }
}

void multiply(double *matrix1, double *matrix2, double *result, int rows1, int cols1, int cols2) {
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i * cols2 + j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }
}

void reshape(double *matrix, double *result, int old_rows, int old_cols, int new_rows, int new_cols) {
    if (old_rows * old_cols != new_rows * new_cols) {
        printf("Cannot reshape matrix: mismatch in number of elements。\n");
        return;
    }
    for (int i = 0; i < old_rows * old_cols; i++) {
        result[i] = matrix[i];
    }
}

int main() {
    int rows = 2, cols = 3;
    double matrix[] = {1, 2, 3, 4, 5, 6};
    double result[6];

    printf("original matrix:\n");
    dump(matrix, rows, cols);

    printf("\nTranspose matrix:\n");
    transpose(matrix, result, rows, cols);
    dump(result, cols, rows);

    double matrix2[] = {6, 5, 4, 3, 2, 1};
    printf("\nmatrix addition:\n");
    add(matrix, matrix2, result, rows, cols);
    dump(result, rows, cols);

    double matrix3[] = {1, 2, 1, 2, 1, 2};
    double result2[4];
    printf("\nmatrix multiplication:\n");
    multiply(matrix, matrix3, result2, rows, cols, 2);
    dump(result2, rows, 2);

    double result3[6];
    printf("\nReshape the Matrix:\n");
    reshape(matrix, result3, rows, cols, 3, 2);
    dump(result3, 3, 2);

    return 0;
}