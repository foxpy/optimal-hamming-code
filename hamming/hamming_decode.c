#include <assert.h>
#include <stddef.h>
#include "matrix.h"
#include "hamming.h"

ptrdiff_t data_row(bit *const* G, size_t m) {
    size_t pos;
    size_t ones = 0;
    for (size_t i = 0; i < MATRIX_SIZE_N(G); ++i) {
        bit b = G[m][i];
        if (b) {
            ++ones;
            pos = i;
        }
    }
    if (ones == 1) {
        return pos;
    } else {
        return -1;
    }
}

bit** hamming_decode(bit *const* encoded, bit *const* G) {
    assert(MATRIX_SIZE_M(encoded) == MATRIX_SIZE_M(G));
    assert(MATRIX_SIZE_N(encoded) == 1);
    size_t decoded_fill = 0;
    bit** decoded = matrix_new(MATRIX_SIZE_N(G), 1);
    for (size_t i = 0; i < MATRIX_SIZE_M(G); ++i) {
        ptrdiff_t index = data_row(G, i);
        if (index != -1) {
            decoded[index][0] = encoded[i][0];
            ++decoded_fill;
        }
    }
    assert(decoded_fill == MATRIX_SIZE_M(decoded));
    return decoded;
}
