#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    mt->arr = NULL;
    *err = ESUCCESS;
    return mt;
}

void remove_matrix(matrix * mt, MATRIX_ERR *err) {
    if (mt == NULL) {
        fprintf(stderr, "Invalid argument: matrix is not initialized(remove)\n");
        if (err != NULL)
            *err = EINVARG;
        return;
    }
    if (mt->arr == NULL) {
        free(mt->arr);
        free(mt);
        *err = ESUCCESS;
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

matrix * fill_matrix(matrix * mt, MATRIX_ERR *err) {

    if (mt == NULL) {
        fprintf(stderr, "Invalid argument: matrix is not initialized(fill)\n");
        if (err != NULL)
            *err = EINVARG;
        return mt;
    }
    printf("Please, enter the matrix in the following format \'1 2;3 4\': ");

    int row_curr = 0;
    int col_curr = 0;
    int number = 0;
    int f = 0;
    int f1 = 1;
    int f2 = 1;
    char ch[2];

    matrix * tmt = init_matrix(mt->rows, mt->cols, err);
    tmt->arr = (int **)malloc(tmt->rows * sizeof(int *));
    if (tmt->arr == NULL) {
        fprintf(stderr, "Not enough memory\n");
        if (err != NULL)
            *err = EMALLOC;
        return NULL;
    }
    for (int i = 0; i < tmt->rows; i++) {
        tmt->arr[i] = (int *)malloc(tmt->cols * sizeof(int));
        if (tmt->arr[i] == NULL) {
            fprintf(stderr, "Not enough memory\n");
            if (err != NULL)
                *err = EMALLOC;
            return NULL;
        }
    }
    while (1) {

        fgets(ch, sizeof(ch), stdin); // считали символ

        if (ch[0] == '\n') {
            if ((f1 == 1) || (f2 == 1)) {
                fprintf(stderr, "Invalid argument: symbols before new line\n");
                if (err != NULL)
                    *err = EINVARG;
                remove_matrix(tmt, err);
                return mt;
            }
            tmt->arr[row_curr][col_curr] = number;
            break;
        } // обработали случай конца строки

        if (!(isdigit(ch[0]) || (ch[0] == ' ') || (ch[0] == ';'))) {
            fprintf(stderr, "Invalid argument: matrix entered in not specified format\n");
            if (err != NULL)
                *err = EINVARG;
            remove_matrix(tmt, err);
            return mt;
        } // проверили на правильность ввода символа

        if ((f1 == 1) && (ch[0] == ' ')) {
            fprintf(stderr, "Invalid argument: two spaces in a row\n");
            if (err != NULL)
                *err = EINVARG;
            remove_matrix(tmt, err);
            return mt;
        }
        if (ch[0] == ' ') {
            f1 = 1;
        } else {
            f1 = 0;
        } // обработали случай двух пробелов

        if ((f2 == 1) && (ch[0] == ';')) {
            fprintf(stderr, "Invalid argument: two ; in a row\n");
            if (err != NULL)
                *err = EINVARG;
            remove_matrix(tmt, err);
            return mt;
        }
        if (ch[0] == ';') {
            f2 = 1;
        } else {
            f2 = 0;
        } // обработали случай двух ;

        // проверка значений колонок и строк
        if (col_curr >= tmt->cols) {
            fprintf(stderr, "Invalid argument: too many cols\n");
            if (err != NULL)
                *err = EINVARG;
            remove_matrix(tmt, err);
            return mt;
        } // обработали случай избытка столбцов

        if (row_curr >= tmt->rows) {
            fprintf(stderr, "Invalid argument: too many rows\n");
            if (err != NULL)
                *err = EINVARG;
            remove_matrix(tmt, err);
            return mt;
        } // обработали случай избытка строк

        if ((ch[0] == ' ') || (ch[0] == ';')){
            tmt->arr[row_curr][col_curr] = number;
            number = 0;
            f = 0;
            if (ch[0] == ' ') {
                col_curr += 1;
            }
            if (ch[0] == ';') {
                row_curr += 1;
                if (col_curr < tmt->cols - 1) {
                    fprintf(stderr, "Invalid argument: not enough cols\n");
                    if (err != NULL)
                        *err = EINVARG;
                    remove_matrix(tmt, err);
                    return mt;
                } // обработали случай недостатка столбцов
                col_curr = 0;
            }
            continue;
        } // вводим значения чисел

        if (f == 1) {
            fprintf(stderr, "Invalid argument: leading zeros in number\n");
            if (err != NULL)
                *err = EINVARG;
            remove_matrix(tmt, err);
            return mt;
        } // обработали случай лидирующих нулей
        if (ch[0] == '0') {
            f = 1;
        } else {
            f = 0;
        } // проверка на лидирующий ноль
        number = number * 10 + ch[0] - '0'; // обновили значение числа
    }
    // сделать проверку на правильное количество строк
    if (row_curr < tmt->rows - 1) {
        fprintf(stderr, "Invalid argument: not enough rows\n");
        if (err != NULL)
            *err = EINVARG;
        remove_matrix(tmt, err);
        return mt;
    } // обработали случай недостатка строк
    if (col_curr < tmt->cols - 1) {
        fprintf(stderr, "Invalid argument: not enough cols\n");
        if (err != NULL)
            *err = EINVARG;
        remove_matrix(tmt, err);
        return mt;
    } // обработали случай недостатка столбцов в последней строке
    *err = ESUCCESS;
    remove_matrix(mt, err);
    return tmt;
}

void print_matrix(matrix * mt, MATRIX_ERR *err) {
    if (mt == NULL) {
        fprintf(stderr, "Invalid argument: matrix is not initialized(remove)\n");
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
    for (int i = 0; i < mt->rows; i++) {
        for (int j = 0; j < mt->cols; j++) {
            printf("row = %d, col = %d, number = %d\n", i, j, mt->arr[i][j]);
        }
    }
    *err = ESUCCESS;
}

matrix * clear_matrix(matrix * mt, MATRIX_ERR *err) {
    if (mt == NULL) {
        fprintf(stderr, "Invalid argument: matrix is not initialized(remove)\n");
        if (err != NULL)
            *err = EINVARG;
        return mt;
    }
    if (mt->arr == NULL) {
        fprintf(stderr, "Invalid argument: matrix is empty\n");
        if (err != NULL)
            *err = EINVARG;
        return mt;
    }
    for (int i  = 0; i < mt->rows; i++) {
        if (mt->arr[i] == NULL) {
            fprintf(stderr, "Invalid argument: matrix doesn't have a row\n");
            if (err != NULL)
                *err = EINVARG;
            return mt;
        }
        free(mt->arr[i]);
    }
    free(mt->arr);
    mt->arr = NULL;
    *err = ESUCCESS;
    return mt;
}

matrix * add_matrix(matrix * mt1, matrix * mt2, MATRIX_ERR *err) {
    if (mt1 == NULL) {
        fprintf(stderr, "Invalid argument: matrix1 is not initialized\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (mt1->arr == NULL) {
        fprintf(stderr, "Invalid argument: matrix1 is empty\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (mt2 == NULL) {
        fprintf(stderr, "Invalid argument: matrix2 is not initialized\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (mt2->arr == NULL) {
        fprintf(stderr, "Invalid argument: matrix2 is empty\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if ((mt1->cols != mt2->cols) || (mt1->rows != mt2->rows)) {
        fprintf(stderr, "Invalid argument: rows or cols not equal\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    matrix * tmt = init_matrix(mt1->rows, mt1->cols, err);
    tmt->arr = (int **)malloc(tmt->rows * sizeof(int *));
    if (tmt->arr == NULL) {
        fprintf(stderr, "Not enough memory\n");
        if (err != NULL)
            *err = EMALLOC;
        return NULL;
    }
    for (int i = 0; i < tmt->rows; i++) {
        tmt->arr[i] = (int *)malloc(tmt->cols * sizeof(int));
        if (tmt->arr[i] == NULL) {
            fprintf(stderr, "Not enough memory\n");
            if (err != NULL)
                *err = EMALLOC;
            return NULL;
        }
    }
    for (int i = 0; i < mt1->rows; i++) {
        for (int j = 0; j < mt1->cols; j++) {
            tmt->arr[i][j] =  mt1->arr[i][j] + mt2->arr[i][j];
        }
    }
    *err = ESUCCESS;
    return tmt;
}

matrix * sub_matrix(matrix * mt1, matrix * mt2, MATRIX_ERR *err) {
    if (mt1 == NULL) {
        fprintf(stderr, "Invalid argument: matrix1 is not initialized\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (mt1->arr == NULL) {
        fprintf(stderr, "Invalid argument: matrix1 is empty\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (mt2 == NULL) {
        fprintf(stderr, "Invalid argument: matrix2 is not initialized\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (mt2->arr == NULL) {
        fprintf(stderr, "Invalid argument: matrix2 is empty\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if ((mt1->cols != mt2->cols) || (mt1->rows != mt2->rows)) {
        fprintf(stderr, "Invalid argument: rows or cols not equal\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    matrix * tmt = init_matrix(mt1->rows, mt1->cols, err);
    tmt->arr = (int **)malloc(tmt->rows * sizeof(int *));
    if (tmt->arr == NULL) {
        fprintf(stderr, "Not enough memory\n");
        if (err != NULL)
            *err = EMALLOC;
        return NULL;
    }
    for (int i = 0; i < tmt->rows; i++) {
        tmt->arr[i] = (int *)malloc(tmt->cols * sizeof(int));
        if (tmt->arr[i] == NULL) {
            fprintf(stderr, "Not enough memory\n");
            if (err != NULL)
                *err = EMALLOC;
            return NULL;
        }
    }
    for (int i = 0; i < mt1->rows; i++) {
        for (int j = 0; j < mt1->cols; j++) {
            tmt->arr[i][j] =  mt1->arr[i][j] - mt2->arr[i][j];
        }
    }
    *err = ESUCCESS;
    return tmt;
}

matrix * mult_matrix(matrix * mt1, matrix * mt2, MATRIX_ERR *err) {
    if (mt1 == NULL) {
        fprintf(stderr, "Invalid argument: matrix1 is not initialized\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (mt1->arr == NULL) {
        fprintf(stderr, "Invalid argument: matrix1 is empty\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (mt2 == NULL) {
        fprintf(stderr, "Invalid argument: matrix2 is not initialized\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (mt2->arr == NULL) {
        fprintf(stderr, "Invalid argument: matrix2 is empty\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    if (mt1->cols != mt2->rows) {
        fprintf(stderr, "Invalid argument: number of cols in mt1 is not equal to number of rows in mt2\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }
    matrix * tmt = init_matrix(mt1->rows, mt2->cols, err);
    tmt->arr = (int **)malloc(tmt->rows * sizeof(int *));
    if (tmt->arr == NULL) {
        fprintf(stderr, "Not enough memory\n");
        if (err != NULL)
            *err = EMALLOC;
        return NULL;
    }
    for (int i = 0; i < tmt->rows; i++) {
        tmt->arr[i] = (int *)malloc(tmt->cols * sizeof(int));
        if (tmt->arr[i] == NULL) {
            fprintf(stderr, "Not enough memory\n");
            if (err != NULL)
                *err = EMALLOC;
            return NULL;
        }
    }
    for (int i = 0; i < mt1->rows; i++) {
        for (int j = 0; j < mt2->cols; j++) {
            int number = 0;
            for (int k = 0; k < mt2->rows; k++) {
                number += mt1->arr[i][k] * mt2->arr[k][j];
            }
            tmt->arr[i][j] = number;
        }
    }
    *err = ESUCCESS;
    return tmt;
}
