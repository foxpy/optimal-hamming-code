#pragma once
#include <stddef.h>
#include "matrix.h"

void hamming_parameters(size_t s, size_t* n, size_t* k);
bit** hamming_H(size_t n, size_t k);
bit** hamming_G(bit *const* H);
bit** hamming_decode(bit *const* encoded, bit *const* G);
