#include "vector.hpp"
#include <immintrin.h>  // for AVX

vector* vecAdd(vector* v1, vector* v2) {
    if (v1->dimension() != v2->dimension()) {
        return nullptr;
    }
    uint64_t dim = v1->dimension();
    vector* result = new vector(dim);
    __m256d a;
    __m256d b;
    __m256d c;
    uint64_t i=0, im = dim, k=0;
    while(im/4>0){
        k=4*i;
       auto a1= v1->element(k);
       auto b1= v2->element(k);
       auto c1= result->element(k);
        a = _mm256_loadu_pd(a1);
        b = _mm256_loadu_pd(b1);
        c = _mm256_add_pd(a,b);
        _mm256_storeu_pd(c1,c);
        i++;
        im -= 4;
    }
    uint64_t z = dim % 4;
    k = 4*i;
    auto a1= v1->element(k);
    auto b1= v2->element(k);
    auto c1= result->element(k);
    for(int j=0; j<z; j++){
       k++;
       *c1 = *a1 + *b1;
        a1= v1->element(k);
        b1= v2->element(k);
        c1= result->element(k);
    }
    
    return result;
}

vector* vecSub(vector* v1, vector* v2) {
    if (v1->dimension() != v2->dimension()) {
        return nullptr;
    }
    uint64_t dim = v1->dimension();
    vector* result = new vector(v1->dimension());
    __m256d a;
    __m256d b;
    __m256d c;
    uint64_t i=0, im = dim, k=0;
    while(im/4>0){
        k=4*i;
       auto a1= v1->element(k);
       auto b1= v2->element(k);
       auto c1= result->element(k);
        a = _mm256_loadu_pd(a1);
        b = _mm256_loadu_pd(b1);
        c = _mm256_sub_pd(a,b);
        _mm256_storeu_pd(c1,c);
        i++;
        im -= 4;
    }
    uint64_t z = dim % 4;
    k = 4*i;
    auto a1= v1->element(k);
    auto b1= v2->element(k);
    auto c1= result->element(k);
    for(int j=0; j<z; j++){
        k++;
       *c1 = *a1 - *b1;
        a1= v1->element(k);
        b1= v2->element(k);
        c1= result->element(k);
    }
    return result;
}

vector* vecElementMul(vector* v1, vector* v2) {
    if (v1->dimension() != v2->dimension()) {
        return nullptr;
    }
    uint64_t dim = v1->dimension();
    vector* result = new vector(v1->dimension());
    __m256d a;
    __m256d b;
    __m256d c;
    uint64_t i=0, im = dim, k=0;
    while(im/4>0){
        k=4*i;
       auto a1= v1->element(k);
       auto b1= v2->element(k);
       auto c1= result->element(k);
        a = _mm256_loadu_pd(a1);
        b = _mm256_loadu_pd(b1);
        c = _mm256_mul_pd(a,b);
        _mm256_storeu_pd(c1,c);
        i++;
        im -= 4;
    }
    uint64_t z = dim % 4;
    k = 4*i;
    auto a1= v1->element(k);
    auto b1= v2->element(k);
    auto c1= result->element(k);
    for(int j=0; j<z; j++){
        k++;
       *c1 = (*a1) * (*b1);
        a1= v1->element(k);
        b1= v2->element(k);
        c1= result->element(k);
    }
    return result;
}

vector* vecElementDiv(vector* v1, vector* v2) {
    if (v1->dimension() != v2->dimension()) {
        return nullptr;
    }
    uint64_t dim = v1->dimension();
    vector* result = new vector(v1->dimension());
    __m256d a;
    __m256d b;
    __m256d c;
    uint64_t i=0, im = dim, k=0;
    while(im/4>0){
        k=4*i;
       auto a1= v1->element(k);
       auto b1= v2->element(k);
       auto c1= result->element(k);
        a = _mm256_loadu_pd(a1);
        b = _mm256_loadu_pd(b1);
        c = _mm256_div_pd(a,b);
        _mm256_storeu_pd(c1,c);
        i++;
        im -= 4;
    }
    uint64_t z = dim % 4;
    k = 4*i;
    auto a1= v1->element(k);
    auto b1= v2->element(k);
    auto c1= result->element(k);
    for(int j=0; j<z; j++){
        k++;
       *c1 = (*a1) / (*b1);
        a1= v1->element(k);
        b1= v2->element(k);
        c1= result->element(k);
    }
    return result;
}

double dotProduct(vector* v1, vector* v2) {
    if (v1->dimension() != v2->dimension()) {
        return -1.0;
    }
    uint64_t dim = v1->dimension();
    double result = 0.0;
    auto r = vecElementMul(v1,v2);
    for(uint64_t j=0; j<dim; j++){
        result+= *(r->element(j));
    }

    
    return result;
}