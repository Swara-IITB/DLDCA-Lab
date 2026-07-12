#include <iostream>
#include <chrono>
#include <cmath>
#include "../common/matrix.hpp"

#define epsilon 0.00001

int main() {

    matrix* A = new matrix(1000, 1000);
    matrix* B = new matrix(1000, 1000);
    for (uint64_t i = 0; i < 1000; i++) {
        for (uint64_t j = 0; j < 1000; j++) {
            *(A->element(i, j)) = (rand() % 100)/100.0;
            *(B->element(i, j)) = (rand() % 100)/100.0;
        }
    }
    auto start = std::chrono::high_resolution_clock::now();
    matrix* At = transpose(A);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    for (uint64_t i = 0; i < 1000; i++) {
        for (uint64_t j = 0; j < 1000; j++) {
            if (*(At->element(i, j)) != *(A->element(j, i))) {
                std::cout << "Transpose Error at (" << i << ", " << j << ")\n";
                exit(1);
            }
        }
        // std::cout << "\n";
    }
    std::cout << "Transpose Time: " << duration.count() << " ms\n";
    start = std::chrono::high_resolution_clock::now();
    matrix* C = add(A, B);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    for (uint64_t i = 0; i < 1000; i++) {
        for (uint64_t j = 0; j < 1000; j++) {
            if ((fabs(*(C->element(i, j)) - ((*(A->element(i, j)) + *(B->element(i, j)))))) > epsilon) {
                std::cout << "Addition Error at (" << i << ", " << j << ")\n";
                exit(1);
            }
        }
        // std::cout << "\n";
    }
    std::cout << "Addition Time: " << duration.count() << " ms\n";
    start = std::chrono::high_resolution_clock::now();
    matrix* D = sub(A, B);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    for (uint64_t i = 0; i < 1000; i++) {
        for (uint64_t j = 0; j < 1000; j++) {
            if ((fabs(*(D->element(i, j)) - ((*(A->element(i, j)) - *(B->element(i, j)))))) > epsilon) {
                std::cout << "Subtraction Error at (" << i << ", " << j << ")\n";
                exit(1);
            }
        }
        // std::cout << "\n";
    }
    std::cout << "Subtraction Time: " << duration.count() << " ms\n";
    start = std::chrono::high_resolution_clock::now();
    matrix* E = matmul(A, B);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    for (uint64_t i = 0; i < 1000; i++) {
        for (uint64_t j = 0; j < 1000; j++) {
            double val = 0;
            for (uint64_t k = 0; k < 1000; k++) {
                val += (*(A->element(i, k))) * (*(B->element(k, j)));
            }
            if ((fabs(*(E->element(i, j)) - val) > epsilon)) {
                std::cout << "Multiplication Error at (" << i << ", " << j << ")\n";
                exit(1);
            }
        }
        // std::cout << "\n";
    }
    std::cout << "Multiplication Time: " << duration.count() << " ms\n";
    return 0;

}