#include <qc.h>
#include <string.h>
#include "matrix.h"
#include "hamming.h"

#define N 15
#define K 11

void compare(bit *const* I, bit *const* D) {
    char* I_str = matrix_to_string(I);
    char* D_str = matrix_to_string(D);
    qc_assert_format(strcmp(I_str, D_str) == 0, "Expected: \"%s\", got: \"%s", I_str, D_str);
    free(D_str);
    free(I_str);
}

int main() {
    bit** I = matrix_new(K, 1);
    matrix_fill_random(I);
    bit** H = hamming_H(N, K);
    bit** G = hamming_G(H);
    bit** C = matrix_multiply(G, I);
    bit** D = hamming_decode(C, G);
    compare(I, D);
    matrix_free(D);
    matrix_free(C);
    matrix_free(G);
    matrix_free(H);
    matrix_free(I);
}
