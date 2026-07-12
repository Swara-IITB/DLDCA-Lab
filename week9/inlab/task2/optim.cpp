/*

This code contains implementationss for:
1. Transpose of a matrix
2. Addition of two matrices
3. Subtraction of two matrices
4. Matrix multiplication

*/

#include "../common/matrix.hpp"
#include <immintrin.h>

matrix* transpose(matrix *a) {
    auto [r, c] = a->size();
    matrix *res = new matrix(c, r);
    // compute res
    return res;
}
matrix* add(matrix *a, matrix *b) {
    auto [r1, c1] = a->size();
    auto [r2, c2] = b->size();
    if (r1 != r2 || c1 != c2) {
        return nullptr; // Dimension mismatch
    }
    matrix *res = new matrix(r1, c1);
    // compute res
    return res;
}
matrix* sub(matrix *a, matrix *b) {
    auto [r1, c1] = a->size();
    auto [r2, c2] = b->size();
    if (r1 != r2 || c1 != c2) {
        return nullptr; // Dimension mismatch
    }
    matrix *res = new matrix(r1, c1);
    // compute res
    return res;
}
matrix* matmul(matrix *a, matrix *b) {
    auto [r1, c1] = a->size();
    auto [r2, c2] = b->size();
    if (c1 != r2) {
        return nullptr; // Dimension mismatch
    }
    matrix *res = new matrix(r1, c2);       
    // compute res
    return res;
}