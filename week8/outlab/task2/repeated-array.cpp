#include <iostream>
#include <cstdint>
#include <chrono>

// No changes should be done anywhere except for the alotted spaces!

volatile int accum = 0;

volatile int arr[15000];
int main() {

    srand(42); // seeds the randomness
    // first initialize the arr with random elements
    for (int i=0; i < 15000; i++) {
        arr[i] = rand() % 15000;
    }

    for (int i=0; i < 15000; i++) {
        arr[i] = arr[i] + 1 - 1; 
    }

    // naive time check
    auto preAdd = std::chrono::high_resolution_clock::now();
    accum = 0;
    for (int i=0; i < 150000; i++) {
        for (int j=0; j < 15000; j++) {
            if (arr[j] > 7500) {
                accum += i * arr[j];
            }
            else {
                accum -= i * arr[j];
            }
        }
    }   
    auto postAdd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(postAdd - preAdd).count();
    std::cout << "accum = " << accum << " time taken = " << duration << std::endl;

    preAdd = std::chrono::high_resolution_clock::now();
    accum = 0;

    /* YOU MAY USE THE BELOW SPACE TO SETUP VARIABLES */
    // Note: You can expand this space and insert as many lines of code as you want
    // The only thing is you can't write above or below the comments, only in between!
    int tmpl, tmpi, reg=0;
    int tmp[15000];
    for (int j = 0; j < 15000; j++) {
        tmpl = arr[j];
        tmp[j] = (tmpl>7500)?tmpl:-tmpl;
    }
    const int I=150000,J=15000;
    /* YOU MAY USE THE ABOVE SPACE TO SETUP VARIABLES */

    for (int i = 0; i < 150000; i++) {
        for (int j = 0; j < 15000; j++) {
            /* YOUR COMPUTATIONS SHOULD BE DONE IN THE SPACE BELOW */
            int regi =0;
            if(j+7<15000){
                regi+=tmp[j];
                regi+=tmp[j+1];
                regi+=tmp[j+2];
                regi+=tmp[j+3];
                regi+=tmp[j+4];
                regi+=tmp[j+5];
                regi+=tmp[j+6];
                regi+=tmp[j+7];
                regi+=tmp[j+8];
                regi+=tmp[j+9];
                j+=9;
            } else{
                for(;j<15000;j++){
                    regi+=tmp[j];
                }
            }
            reg +=regi*i;
            if(i==I-1 && j==J-1) accum = reg;
            /* YOUR COMPUTATIONS SHOULD BE DONE IN THE SPACE ABOVE */
        }
    }
    postAdd = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(postAdd - preAdd).count();
    std::cout << "accum = " << accum << " time taken = " << duration << std::endl;

}
