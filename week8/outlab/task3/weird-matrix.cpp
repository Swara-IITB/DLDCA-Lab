#include <iostream>
#include <cstdint>
#include <chrono>

volatile int accum = 0;

volatile int arr[1500];

volatile int m1[1500][1500];
volatile int m2[1500][1500];

int main() {

    srand(42); // seeds the randomness
    // first initialize the arr with random elements
    for (int i=0; i < 1500; i++) {
        arr[i] = rand() % 1500;
        for (int j=0; j < 1500; j++) {
            m1[i][j] = rand() % 100;
            m2[i][j] = rand() % 100;
        }
    }

    // naive time check
    auto preAdd = std::chrono::high_resolution_clock::now();
    accum = 0;
    for (int i=0; i < 1500; i++) {
        for (int j=0; j < 1500; j++) {
            if (arr[j] > 750) {
                // accum gets the dot product between ith column and jth column (say)
                int dotP = 0;
                for (int k=0; k < 1500; k++) {
                    dotP += m1[arr[k]][i] * m2[k][arr[j]];
                }
                accum += dotP;
            }
            else {
                // accum gets -dot product between jth column and ith column (say)
                int dotP = 0;
                for (int k=0; k < 1500; k++) {
                    dotP += m1[k][arr[j]] * m2[arr[k]][i];
                }
                accum -= dotP;
            }
        }
    }   
    auto postAdd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(postAdd - preAdd).count();
    std::cout << "accum = " << accum << " time taken = " << duration << std::endl;

    preAdd = std::chrono::high_resolution_clock::now();
    accum = 0;
    int reg=0, prem1[1500], prem2[1500];
    for(int k=0; k<1500; k++){
        int s1=0, s2=0,i=0;
        for(; i+9<1500; i+=10){
            s1+=m1[k][i];
            s2+=m2[k][i];
            s1+=m1[k][i+1];
            s2+=m2[k][i+1];
            s1+=m1[k][i+2];
            s2+=m2[k][i+2];
            s1+=m1[k][i+3];
            s2+=m2[k][i+3];
            s1+=m1[k][i+4];
            s2+=m2[k][i+4];
            s1+=m1[k][i+5];
            s2+=m2[k][i+5];
            s1+=m1[k][i+6];
            s2+=m2[k][i+6];
            s1+=m1[k][i+7];
            s2+=m2[k][i+7];
            s1+=m1[k][i+8];
            s2+=m2[k][i+8];
            s1+=m1[k][i+9];
            s2+=m2[k][i+9];
        }
        for(;i<1500;i++){
            s1+=m1[k][i];
            s2+=m2[k][i];
        }
        prem1[k]=s1;
        prem2[k]=s2;
    }
    for(int k=0; k<1500; k++){
        for(int j=0; j<1500; j++){
            if(arr[j]>750){
                reg+=prem1[arr[k]]*m2[k][arr[j]];
            }else{
                reg-=prem2[arr[k]]*m1[k][arr[j]];
            }
        }
    }
    accum = reg;
    postAdd = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(postAdd - preAdd).count();
    std::cout << "accum = " << accum << " time taken = " << duration << std::endl;

}
