#include "hamming.h"

static size_t powu(size_t x, size_t n) {
    size_t ret = 1;
    for (size_t i = 0; i < n; ++i) {
        ret *= x;
    }
    return ret;
}

void hamming_parameters(size_t s, size_t *n, size_t *k) {
    *n = powu(2, s) - 1;
    *k = *n - s;
}
