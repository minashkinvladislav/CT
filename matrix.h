#ifndef _MATRIX_H
#define _MATRIX_H
typedef struct matrix {
    int rows;
    int cols;
    int ** arr;
} matrix;

typedef enum {
    ESUCCESS = 0,
    EFULLROW,
    EEMPTY,
    EMALLOC,
    EINVARG
} MATRIX_ERR;

matrix *init_matrix(int rows, int cols, MATRIX_ERR *err);

void remove_matrix(matrix * matrix, MATRIX_ERR *err);

matrix * fill_matrix(matrix * matrix, MATRIX_ERR *err);

matrix * clear_matrix(matrix * matrix, MATRIX_ERR *err);

matrix * add_matrix(matrix * matrix1, matrix * matrix2, MATRIX_ERR *err);

matrix * sub_matrix(matrix * matrix1, matrix * matrix2, MATRIX_ERR *err);

matrix * mult_matrix(matrix * matrix1, matrix * matrix2, MATRIX_ERR *err);

#endif //_MATRIX_H
