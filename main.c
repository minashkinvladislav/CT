#include <stdio.h>
#include "matrix.c"

int main() {
    MATRIX_ERR err;
    matrix *mt = init_matrix(3, 4, &err);
    remove_matrix(mt, &err);
    return 0;
}
