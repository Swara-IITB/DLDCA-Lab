/*

This file contains implementationss for:
1. Outer product of 2 matrices
2. Convolution of 2 matrices
3. Wierd multiplication of a matrix

*/

#include "../common/matrix.hpp"
#include <cmath>
#include <immintrin.h>

matrix* outer(matrix *a, matrix *b) {
    auto [r1, c1] = a->size();
    auto [r2, c2] = b->size();
    matrix *res = new matrix(r1 * r2, c1 * c2);
    // compute res
    for (uint64_t i = 0; i < r1; i++) {
        for (uint64_t j = 0; j < c1; j++) {
            for (uint64_t p = 0; p < r2; p++) {
                for (uint64_t q = 0; q <= c2-4; q+=4) {
                    _mm256_storeu_pd(res->element(i * r2 + p, j * c2 + q),_mm256_mul_pd(_mm256_set1_pd(*(a->element(i, j))),_mm256_loadu_pd((b->element(p, q)))));
                }
                for(uint64_t q = (c2/4)*4; q<c2; q++){
                    *(res->element(i * r2 + p, j * c2 + q)) = (*(a->element(i, j))) * (*(b->element(p, q)));  
                }
            }
        }
    }
    return res;
}

matrix* convolve(matrix* a, matrix* b) {
    // output matrix dim must be same as a-> dim
    // and a->dim must be greater than b->dim
    auto [r1, c1] = a->size();
    auto [r2, c2] = b->size();
    if (r1 < r2 || c1 < c2) {
        return nullptr; // Dimension mismatch   
    }
    if (r2 % 2 == 0 || c2 % 2 == 0) {
        return nullptr; // Kernel dimensions must be odd
    }
    matrix* res = new matrix(r1, c1);
    // compute res
    for (int i = (r2 - 1)/2; i < r1 - (r2 - 1)/2; i++) {
        for (int j = (c2 - 1)/2; j < c1 - (c2 - 1)/2; j++) {
            double sum = 0.0;
            for (int k = -((int64_t)r2 - 1)/2; k <= ((int64_t)r2 - 1)/2; k++) {
                int li = -((int64_t)c2 - 1)/2, l = li, m = (((int64_t)c2 - 1)/2)-l;
                __m256d t = _mm256_setzero_pd();
                for (int x =0; x <= m-4; x+=4) {// (;x<=m; x++)
                    l = li + x;
                    t = _mm256_fmadd_pd(_mm256_loadu_pd(a->element(i + k, j + l)),_mm256_loadu_pd(b->element(k + (r2 - 1)/2, l + (c2 - 1)/2)),t);
                }
                double tmp[4];
                _mm256_storeu_pd(tmp,t);
                for(int x=0; x<4; x++){
                    sum+=tmp[x];
                }
                for (int x = (m/4)*4; x <= m; x++) {// (;x<=m; x++)
                    l = li + x;
                    sum += (*(a->element(i + k, j + l))) * (*(b->element(k + (r2 - 1)/2, l + (c2 - 1)/2)));
                }
            }
            *(res->element(i, j)) = sum;
        }
    }
    return res;
}

matrix* weirdMul(matrix* a, matrix* b) {
    auto [r1, c1] = a->size();
    auto [r2, c2] = b->size();
    if (c1 != r2) {
        return nullptr; // Dimension mismatch
    }
    matrix* res = new matrix(r1, c2);
    // compute res
    for (uint64_t i = 0; i < r1; i++) {
        for (uint64_t j = 0; j <= c2-4; j+=4) {
            __m256d summ = _mm256_setzero_pd();
            for (uint64_t k = 0; k < c1; k++) {
                double aik = *(a->element(i, k));
                if (*(a->element(i,k)) > 0.5) {
                    summ = _mm256_fmadd_pd(_mm256_set1_pd(aik),_mm256_loadu_pd(b->element(k, j)),summ);
                }
                else {
                    summ = _mm256_sub_pd(summ,_mm256_mul_pd(_mm256_set1_pd(1.0 - aik),_mm256_loadu_pd(b->element(k, j))));
                }
            }
            _mm256_storeu_pd(res->element(i, j),summ);
        }
        for(uint64_t j = (c2/4)*4; j < c2; j++){
            double sum = 0.0;
            for (uint64_t k = 0; k < c1; k++) {
                if (*(a->element(i,k)) > 0.5) {
                    sum += (*(a->element(i, k))) * (*(b->element(k, j)));
                }
                else {
                    sum -= (1 - *(a->element(i, k))) * (*(b->element(k, j)));
                }
            }
            *(res->element(i, j)) = sum;
        }
    }
    return res;
}