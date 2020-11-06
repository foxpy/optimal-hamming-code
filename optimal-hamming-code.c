#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <qc.h>
#include "hamming.h"
#include "matrix.h"

static void demonstrate(size_t n, size_t k) {
    printf("The best appropriate Hamming code is (%zu,%zu,3)\n", n, k);
    bit** H = hamming_H(n, k);
    bit** G = hamming_G(H);
    char* H_str = matrix_to_string(H);
    char* G_str = matrix_to_string(G);
    printf("Generator matrix G:\n%s", G_str);
    printf("Parity check matrix H:\n%s", H_str);
    free(H_str);
    free(G_str);
    matrix_free(H);
    matrix_free(G);
}

int main(int argc, char* argv[]) {
    size_t target_k;
    qc_args* args = qc_args_new();
    qc_args_brief(args,
            "Find the most optimal Hamming code with specified information\n"
            "vector bit length, also generate appropriate matrices G and H\n");
    qc_args_unsigned_default(args, "k", 4, &target_k, "information vector bits");
    char* err;
    if (!qc_args_parse(args, argc, argv, &err)) {
        fprintf(stderr, "Failed to parse arguments: %s\n", err);
        free(err);
        qc_args_free(args);
        exit(EXIT_FAILURE);
    }
    if (target_k == 0) {
        fputs("k is expected to be positive\n", stderr);
        exit(EXIT_FAILURE);
    }
    size_t s = 0, n = 0, k = 0;
    while (k < target_k) {
        ++s;
        hamming_parameters(s, &n, &k);
    }
    demonstrate(n - k + target_k, target_k);
    qc_args_free(args);
}
