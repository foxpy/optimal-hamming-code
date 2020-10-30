#pragma once
#include <stddef.h>
typedef _Bool bit;

#define MATRIX_SIZE_M(matrix) (((size_t*)(matrix))[-2])
#define MATRIX_SIZE_N(matrix) (((size_t*)(matrix))[-1])

bit** matrix_new(size_t m, size_t n);
void matrix_free(bit** matrix);
bit** matrix_multiply(bit *const* A, bit *const* B);
char* matrix_to_string(bit *const* matrix);
