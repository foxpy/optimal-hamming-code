#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <qc.h>
#include "hamming.h"
#include "matrix.h"

static void print_transposed(bit *const* mat) {
    bit** transposed = matrix_transpose(matrix_clone(mat));
    char* str = matrix_to_string(transposed);
    printf("%s", str);
    free(str);
    matrix_free(transposed);
}

static size_t add_error(bit** vector) {
    size_t len = MATRIX_SIZE_M(vector);
    qc_rnd rnd;
    qc_rnd_init(&rnd);
    size_t error_position = qc_rnd_range64(&rnd, 0, len - 1);
    vector[error_position][0] ^= 1u;
    return error_position;
}

static void fix_error(bit** vector, size_t position) {
    vector[position - 1][0] ^= 1u;
}

static size_t syndrome_to_error_position(bit *const* S) {
    assert(MATRIX_SIZE_N(S) == 1);
    size_t ret = 0;
    for (size_t i = 0; i < MATRIX_SIZE_M(S); ++i) {
        ret <<= 1;
        ret += S[i][0];
    }
    return ret;
}

static void demonstrate(size_t n, size_t k) {
    printf("The best appropriate Hamming code is (%zu,%zu,3)\n", n, k);

    bit** H = hamming_H(n, k);
    char* H_str = matrix_to_string(H);
    bit** G = hamming_G(H);
    char* G_str = matrix_to_string(G);
    printf("Generator matrix G:\n%s", G_str);
    printf("Parity check matrix H:\n%s", H_str);

    bit** I = matrix_new(k, 1);
    matrix_fill_random(I);
    bit** C = matrix_multiply(G, I);
    fputs("Random information vector I: ", stdout);
    print_transposed(I);
    fputs("Encoded message C: ", stdout);
    print_transposed(C);

    size_t error_position = add_error(C);
    printf("Adding error at %zu: ", error_position + 1);
    print_transposed(C);
    bit** S = matrix_multiply(H, C);
    fputs("Syndrome S: ", stdout);
    print_transposed(S);

    size_t detected_error_position = syndrome_to_error_position(S);
    printf("Syndrome states the error takes place at %zu\n", detected_error_position);
    fix_error(C, detected_error_position);
    printf("Fixed error at %zu: ", detected_error_position);
    print_transposed(C);

    bit** D = hamming_decode(C, G);
    fputs("Decoded message: ", stdout);
    print_transposed(D);

    free(H_str);
    free(G_str);
    matrix_free(D);
    matrix_free(H);
    matrix_free(G);
    matrix_free(I);
    matrix_free(C);
    matrix_free(S);
}

int main(int argc, char* argv[]) {
    size_t k;
    qc_args* args = qc_args_new();
    qc_args_brief(args,
            "Find the most optimal Hamming code with specified information\n"
            "vector bit length, also generate appropriate matrices G and H\n");
    qc_args_unsigned_default(args, "k", 4, &k, "information vector bits");
    char* err;
    if (!qc_args_parse(args, argc, argv, &err)) {
        fprintf(stderr, "Failed to parse arguments: %s\n", err);
        free(err);
        qc_args_free(args);
        exit(EXIT_FAILURE);
    }
    if (k == 0) {
        fputs("k is expected to be positive\n", stderr);
        exit(EXIT_FAILURE);
    }
    size_t n = hamming_n(k);
    demonstrate(n, k);
    qc_args_free(args);
}
