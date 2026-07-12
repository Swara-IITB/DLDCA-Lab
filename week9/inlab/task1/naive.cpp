#include "vector.hpp"

vector* vecAdd(vector* v1, vector* v2) {
    if (v1->dimension() != v2->dimension()) {
        return nullptr;
    }
    vector* result = new vector(v1->dimension());
    for (uint64_t i = 0; i < v1->dimension(); i++) {
        *(result->element(i)) = *(v1->element(i)) + *(v2->element(i));
    }
    return result;
}

vector* vecSub(vector* v1, vector* v2) {
    if (v1->dimension() != v2->dimension()) {
        return nullptr;
    }
    vector* result = new vector(v1->dimension());
    for (uint64_t i = 0; i < v1->dimension(); i++) {
        *(result->element(i)) = *(v1->element(i)) - *(v2->element(i));
    }
    return result;
}

vector* vecElementMul(vector* v1, vector* v2) {
    if (v1->dimension() != v2->dimension()) {
        return nullptr;
    }
    vector* result = new vector(v1->dimension());
    for (uint64_t i = 0; i < v1->dimension(); i++) {
        *(result->element(i)) = *(v1->element(i)) * *(v2->element(i));
    }
    return result;
}

vector* vecElementDiv(vector* v1, vector* v2) {
    if (v1->dimension() != v2->dimension()) {
        return nullptr;
    }
    vector* result = new vector(v1->dimension());
    for (uint64_t i = 0; i < v1->dimension(); i++) {
        *(result->element(i)) = *(v1->element(i)) / *(v2->element(i));
    }
    return result;
}

double dotProduct(vector* v1, vector* v2) {
    if (v1->dimension() != v2->dimension()) {
        return -1.0;
    }
    double result = 0.0;
    for (uint64_t i = 0; i < v1->dimension(); i++) {
        result += *(v1->element(i)) * *(v2->element(i));
    }
    return result;
}