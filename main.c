#include <stdio.h>
#include "matrix.c"

int main() {
    MATRIX_ERR err;
    matrix *mt = init_matrix(3, 4, &err);
    mt = fill_matrix(mt, &err);
    printf("%d\n", mt->arr[2][2]);
    print_matrix(mt, &err);
    mt = fill_matrix(mt, &err);
    print_matrix(mt, &err);
    remove_matrix(mt, &err);
    return 0;
}
