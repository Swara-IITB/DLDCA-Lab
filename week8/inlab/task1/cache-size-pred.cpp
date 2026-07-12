#include <bits/stdc++.h>
#include <x86intrin.h>

//Demo function to show use of rdtsc
double measure_time_rdtsc(int trials, int KB) {

    int * dummy=(int*)malloc(sizeof(int));
    *dummy = 0;
    int s = (KB*1024)/64;
    int J;
    // Measure using rdtsc with serialization
    uint64_t total_cycles = 0;
    for (int t = 0; t < trials; t++) {
        uint32_t cycles_high, cycles_low;
        asm volatile (
            "cpuid\n"      
            "rdtsc\n"
            : "=a"(cycles_low), "=d"(cycles_high)
            :: "rbx","rcx"
        );
        uint64_t start = ((uint64_t)cycles_high << 32) | cycles_low;

        /*
        Put whatever code you want to measure execution time of here
        Dummy memory access given for reference
        */
        
        for(int i=0; i < s; i++){
            J = *dummy + 16;
        }
        

        asm volatile (
            "rdtscp\n"      
            "mov %%edx, %0\n"
            "mov %%eax, %1\n"
            "cpuid\n"
            : "=r"(cycles_high), "=r"(cycles_low)
            :: "rax","rbx","rcx","rdx"
        );
        uint64_t end = ((uint64_t)cycles_high << 32) | cycles_low;
        total_cycles += (end - start);
    }

    return double(total_cycles) / trials; // cycles per access
}

int main(){
    
    for(int i=5; i<=6192; i+=10){
        std::cout << i << ' ' << measure_time_rdtsc(100,i) << std::endl;
    }
    

}