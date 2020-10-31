#include <stddef.h>
#include <stdbool.h>
#include <qc.h>
#include "matrix.h"

static ptrdiff_t find_systematic_column(bit *const* matrix, size_t num) {
    for (size_t i = 0; i < MATRIX_SIZE_N(matrix); ++i) {
        bool found = true;
        for (size_t j = 0; j < MATRIX_SIZE_M(matrix); ++j) {
            if (matrix[j][i] != (j == num ? 1 : 0)) {
                found = false;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}

static void swap_columns(bit *const* matrix, size_t a, size_t b) {
    for (size_t i = 0; i < MATRIX_SIZE_M(matrix); ++i) {
        bit tmp = matrix[i][a];
        matrix[i][a] = matrix[i][b];
        matrix[i][b] = tmp;
    }
}

size_t* matrix_to_systematic(bit** matrix, qc_err* err) {
    if (MATRIX_SIZE_N(matrix) <= MATRIX_SIZE_M(matrix)) {
        qc_err_set_error(err, "Systematic form transformation is supported for m < n matrices only");
        return NULL;
    }
    size_t* permutation = emalloc(MATRIX_SIZE_N(matrix) * sizeof(size_t));
    for (size_t i = 0; i < MATRIX_SIZE_N(matrix); ++i) {
        permutation[i] = i;
    }
    size_t tail = MATRIX_SIZE_N(matrix) - MATRIX_SIZE_M(matrix);
    for (size_t i = 0; i < MATRIX_SIZE_M(matrix); ++i) {
        ptrdiff_t sys_index = find_systematic_column(matrix, i);
        if (sys_index == -1) {
            qc_err_set_error(err, "This matrix cannot be transformed into systematic form");
            free(permutation);
            return NULL;
        }
        swap_columns(matrix, sys_index, tail);
        size_t tmp = permutation[sys_index];
        permutation[sys_index] = tail;
        permutation[tail] = tmp;
        ++tail;
    }
    return permutation;
}
