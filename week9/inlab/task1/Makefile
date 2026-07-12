# Default target: build both
all: naive simd

# Build the naive version
naive: main.cpp naive.cpp
	$(CXX) -O0 -mavx -mfma main.cpp naive.cpp -o naive

# Build the simd version
simd: main.cpp simd.cpp
	$(CXX) -O0 -mavx -mfma main.cpp simd.cpp -o simd

# If user provides "make naive" → builds only naive
# If user provides "make simd"  → builds only simd
# If user provides just "make"  → builds both

# Clean binaries
clean:
	rm -f naive simd

