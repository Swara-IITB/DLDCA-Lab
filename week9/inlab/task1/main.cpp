#include "vector.hpp"
#include <random>
#include <iostream>
#include <chrono>

#define epsilon 0.0001
#define SIZE 100000000

int main() {
    srand(42);
    vector* v1 = new vector(SIZE);
    vector* v2 = new vector(SIZE);

    for (uint64_t i = 0; i < SIZE; i++) {
        *(v1->element(i)) = rand()%SIZE;
        *(v2->element(i)) = rand()%SIZE;
    }

    std::cout << "Initialized vectors. Testing add" << std::endl;
    

    auto preAdd = std::chrono::high_resolution_clock::now();
    auto v3 = vecAdd(v1, v2);
    auto postAdd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(postAdd - preAdd).count();
    // correctness check
    for (uint64_t i = 0; i < SIZE; i++) {
        if (*(v3->element(i)) != (*(v1->element(i)) + *(v2->element(i)))) {
            std::cerr << "Addition incorrect!" << std::endl;
        }
    }
    std::cout << "Duration for add: " << duration << std::endl;
    std::cout << "Addition done, testing subtraction" << std::endl;
    delete v3;

    preAdd = std::chrono::high_resolution_clock::now();
    v3 = vecSub(v1, v2);
    postAdd = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(postAdd - preAdd).count();
    // correctness check
    for (uint64_t i = 0; i < SIZE; i++) {
        if (*(v3->element(i)) != (*(v1->element(i)) - *(v2->element(i)))) {
            std::cerr << "Subtraction incorrect!" << std::endl;
        }
    }
    std::cout << "Duration for subtraction: " << duration << std::endl;
    std::cout << "Subtraction done, testing multiplication" << std::endl;
    delete v3;

    preAdd = std::chrono::high_resolution_clock::now();
    v3 = vecElementMul(v1, v2);
    postAdd = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(postAdd - preAdd).count();
    // correctness check
    for (uint64_t i = 0; i < SIZE; i++) {
        if (*(v3->element(i)) != (*(v1->element(i)) * *(v2->element(i)))) {
            std::cerr << "Multiplication incorrect!" << std::endl;
        }
    }
    std::cout << "Duration for multiplication: " << duration << std::endl;
    std::cout << "Multiplication done, testing division" << std::endl;
    delete v3;

    preAdd = std::chrono::high_resolution_clock::now();
    v3 = vecElementDiv(v1, v2);
    postAdd = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(postAdd - preAdd).count();
    // correctness check
    for (uint64_t i = 0; i < SIZE; i++) {
        if (fabs(*(v3->element(i)) - (*(v1->element(i)) / *(v2->element(i)))) > epsilon) {
            std::cerr << "Division incorrect!" << std::endl;
        }
    }
    std::cout << "Duration for division: " << duration << std::endl;
    std::cout << "Division done, testing dot product" << std::endl;
    delete v3;

    preAdd = std::chrono::high_resolution_clock::now();
    double dot = dotProduct(v1, v2);
    postAdd = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(postAdd - preAdd).count();
    // correctness check
    double dotP = 0;
    for (uint64_t i = 0; i < SIZE; i++) {
        dotP += (*(v1->element(i)) * *(v2->element(i)));
    }
    if (fabs(dotP - dot) > epsilon) {
        std::cerr << "Dot Product incorrect! Actual = " << dotP << " got " << dot << " instead!" << std::endl;
    }
    std::cout << "Duration for dot product: " << duration << std::endl;
    std::cout << "Dot Product done" << std::endl;
    std::cout << "All tests done!" << std::endl;
    delete v1;
    delete v2;

}