#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

matrix * init_matrix(int rows, int cols, MATRIX_ERR *err) {
    if (rows <= 0) {
        fprintf(stderr, "Invalid argument: rows\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (cols <= 0) {
        fprintf(stderr, "Invalid argument: cols\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    matrix *mt =(matrix *)malloc(sizeof(matrix));
    if (mt == NULL) {
        fprintf(stderr, "Not enough memory\n");
        if (err != NULL)
            *err = EMALLOC;
        return NULL;
    }
    mt->rows = rows;
    mt->cols = cols;
    mt->arr = (int **)malloc(rows * sizeof(int *));
    if (mt->arr == NULL) {
        fprintf(stderr, "Not enough memory\n");
        if (err != NULL)
            *err = EMALLOC;
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        mt->arr[i] = (int *)malloc(cols * sizeof(int));
        if (mt->arr[i] == NULL) {
            fprintf(stderr, "Not enough memory\n");
            if (err != NULL)
                *err = EMALLOC;
            return NULL;
        }
    }
    *err = ESUCCESS;
    return mt;
}

void remove_matrix(matrix * mt, MATRIX_ERR *err) {
    if (mt == NULL) {
        fprintf(stderr, "Invalid argument: matrix is not initialized\n");
        if (err != NULL)
            *err = EINVARG;
        return;
    }
    if (mt->arr == NULL) {
        fprintf(stderr, "Invalid argument: matrix is empty\n");
        if (err != NULL)
            *err = EINVARG;
        return;
    }
    for (int i  = 0; i < mt->rows; i++) {
        if (mt->arr[i] == NULL) {
            fprintf(stderr, "Invalid argument: matrix doesn't have a row\n");
            if (err != NULL)
                *err = EINVARG;
            return;
        }
        free(mt->arr[i]);
    }
    free(mt->arr);
    free(mt);
    *err = ESUCCESS;
}

matrix * fill_matrix(matrix * mt, MATRIX_ERR *err);

matrix * clear_matrix(matrix * mt, MATRIX_ERR *err);

matrix * add_matrix(matrix * mt1, matrix * mt2, MATRIX_ERR *err);

matrix * sub_matrix(matrix * mt1, matrix * mt2, MATRIX_ERR *err);

matrix * mult_matrix(matrix * mt1, matrix * mt2, MATRIX_ERR *err);
