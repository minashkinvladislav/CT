#include "matrix.c"

int main() {
    MATRIX_ERR err;
    matrix * mt1 = init_matrix(3, 4, &err);
    matrix * mt2 = init_matrix(4, 3, &err);
    mt1 = fill_matrix(mt1, &err);
    mt2 = fill_matrix(mt2, &err);
    matrix * plus = add_matrix(mt1, mt1, &err);
    matrix * minus = sub_matrix(mt1, mt1, &err);
    print_matrix(plus, &err);
    print_matrix(minus, &err);
    print_matrix(mt1, &err);
    print_matrix(mt2, &err);
    matrix * tmt = mult_matrix(mt1, mt2, &err);
    print_matrix(tmt, &err);
    clear_matrix(mt1, &err);
    clear_matrix(mt2, &err);
    remove_matrix(plus, &err);
    remove_matrix(minus, &err);
    remove_matrix(mt1, &err);
    remove_matrix(mt2, &err);
    remove_matrix(tmt, &err);
    return 0;
}
