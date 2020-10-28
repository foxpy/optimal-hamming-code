#include <stddef.h>
#include <string.h>
#include <qc.h>
#include "matrix.h"

bit** matrix_new(size_t m, size_t n) {
    size_t* mem = emalloc(m * sizeof(bit*) + 2 * sizeof(size_t));
    mem[0] = m;
    mem[1] = n;
    bit** ret = (bit**) &mem[2];
    for (size_t i = 0; i < m; ++i) {
        ret[i] = emalloc(n * sizeof(bit));
        memset(ret[i], 0, n * sizeof(bit));
    }
    return ret;
}
