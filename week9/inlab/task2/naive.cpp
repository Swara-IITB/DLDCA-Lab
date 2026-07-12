/*

This code contains implementationss for:
1. Transpose of a matrix
2. Addition of two matrices
3. Subtraction of two matrices
4. Matrix multiplication

*/

#include "../common/matrix.hpp"

matrix* transpose(matrix *a) {
    auto [r, c] = a->size();
    matrix *res = new matrix(c, r);
    for (uint64_t i = 0; i < r; i++) {
        for (uint64_t j = 0; j < c; j++) {
            *(res->element(j, i)) = *(a->element(i, j));
        }
    }
    return res;
}
matrix* add(matrix *a, matrix *b) {
    auto [r1, c1] = a->size();
    auto [r2, c2] = b->size();
    if (r1 != r2 || c1 != c2) {
        return nullptr; // Dimension mismatch
    }
    matrix *res = new matrix(r1, c1);
    for (uint64_t i = 0; i < r1; i++) {
        for (uint64_t j = 0; j < c1; j++) {
            *(res->element(i, j)) = *(a->element(i, j)) + *(b->element(i, j));
        }
    }
    return res;
}
matrix* sub(matrix *a, matrix *b) {
    auto [r1, c1] = a->size();
    auto [r2, c2] = b->size();
    if (r1 != r2 || c1 != c2) {
        return nullptr; // Dimension mismatch
    }
    matrix *res = new matrix(r1, c1);
    for (uint64_t i = 0; i < r1; i++) {
        for (uint64_t j = 0; j < c1; j++) { 
            *(res->element(i, j)) = *(a->element(i, j)) - *(b->element(i, j));
        }
    }
    return res;
}
matrix* matmul(matrix *a, matrix *b) {
    auto [r1, c1] = a->size();
    auto [r2, c2] = b->size();
    if (c1 != r2) {
        return nullptr; // Dimension mismatch
    }
    matrix *res = new matrix(r1, c2);       
    for (uint64_t i = 0; i < r1; i++) {
        for (uint64_t j = 0; j < c2; j++) {
            for (uint64_t k = 0; k < c1; k++) {
                *(res->element(i, j)) += (*(a->element(i, k))) * (*(b->element(k, j)));
            }
        }
    }
    return res;
}