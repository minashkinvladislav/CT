#include <stdio.h>
#include "matrix.c"

int main() {
    MATRIX_ERR err;
    matrix *matrix = init_matrix(3, 4, &err);
    printf("%d", matrix->arr[2][2]);
    return 0;
}
